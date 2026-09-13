#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "PatientVisitDetails.h"
#include "PatientSystem.h"
#include "Fee.h"

using namespace std;

class WaitingRoom
{
private:
    static vector<PatientVisitDetails> _waitingPatients;
    vector<Patient>& _patients;

public:
    WaitingRoom()
        : _patients(PatientSystem::GetPatients())
    {
    }

    void AddToWaitingRoom(int id)
    {
        if (_patients.size() == 0)
        {
            cout << "No appointments\n\n";
            return;
        }

        string doctor, diagnosis;
        State state;
        int Choose;

        for (int i = 0; i < _patients.size(); i++)
        {
            if (id == _patients[i].GetID())
            {
                cout << "Case type : (1) Emergency (2) Normal\n"
                    << "Choose: ";

                cin >> Choose;

                switch (Choose)
                {
                case 1:
                    state = Emergency;
                    break;

                case 2:
                    state = Normal;
                    break;

                default:
                    cout << "Invalid input\n\n";
                    return;
                }

                cout << "Doctor: ";
                cin >> doctor;

                cout << "Diagnosis: ";
                cin >> diagnosis;

                Fee f;
                f.Calculatefee(state);

                PatientVisitDetails pd(
                    doctor,
                    diagnosis,
                    f.GetFee(),
                    state,
                    &_patients[i]
                );

                _waitingPatients.push_back(pd);

                cout << "[OK] Patient "
                    << _patients[i].GetID()
                    << " added to waiting room\n"
                    << "date: "
                    << pd.GetDate()
                    << "\n\n";

                return;
            }
        }

        cout << "[ERROR] Patient was not found\n\n";
    }

    void SortByPriority()
    {
        for (int i = 0; i < _waitingPatients.size() - 1; i++)
        {
            for (int j = 0; j < _waitingPatients.size() - i - 1; j++)
            {
                if (
                    (_waitingPatients[j].GetState() == Normal &&
                        _waitingPatients[j + 1].GetState() == Emergency)
                    ||
                    (_waitingPatients[j].GetState() ==
                        _waitingPatients[j + 1].GetState() &&
                        _waitingPatients[j].GetDate() >
                        _waitingPatients[j + 1].GetDate())
                    )
                {
                    swap(
                        _waitingPatients[j],
                        _waitingPatients[j + 1]
                    );
                }
            }
        }
    }

    void ViewWaitingPatients()
    {
        if (_waitingPatients.empty())
        {
            cout << "No waiting patients.\n\n";
            return;
        }

        SortByPriority();

        cout << "\n*** WAITING PATIENTS ***\n";
        cout << "----------------------------------------------\n";

        for (int i = 0; i < _waitingPatients.size(); i++)
        {
            cout << i + 1
                << "    "
                << _waitingPatients[i].GetPatient()
                << "      "
                << _waitingPatients[i].GetState()
                << "      "
                << _waitingPatients[i].GetDate()
                << "\n";
        }

        cout << "----------------------------------------------\n\n";
    }

    void CallPatient()
    {
        SortByPriority();

        if (_waitingPatients.empty())
        {
            cout << "No waiting patients.\n\n";
            return;
        }

        cout << "\n>>> NOW CALLING: "
            << _waitingPatients[0].GetPatient()
            << "   ("
            << _waitingPatients[0].GetState()
            << ")\n\n";

        cout << "Doctor    : Dr."
            << _waitingPatients[0].GetDoctor()
            << "\n";

        cout << "Diagnosis : "
            << _waitingPatients[0].GetDiagnosis()
            << "\n";

        cout << _waitingPatients[0].GetFee()
            << "\n\n";

        PatientSystem ps;

        ps.AddHistory(
            _waitingPatients[0].GetPatientID(),
            _waitingPatients[0]
        );

        _waitingPatients.erase(_waitingPatients.begin());

        cout << "[OK] Visit added to history. "
            << _waitingPatients.size()
            << " still waiting.\n\n";
    }
};