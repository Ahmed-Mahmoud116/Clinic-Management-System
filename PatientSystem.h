#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "Patient.h"

using namespace std;

class PatientSystem
{
private:
    static vector<Patient> _patients;

public:
    static vector<Patient>& GetPatients()
    {
        return _patients;
    }

    void AddPatient(Patient patient)
    {
        _patients.push_back(patient);

        cout << "[OK] Patient "
            << patient.GetID()
            << " was added.\n\n";
    }

    void DeletePatient(int id)
    {
        for (int i = 0; i < _patients.size(); i++)
        {
            if (id == _patients[i].GetID())
            {
                _patients.erase(_patients.begin() + i);

                cout << "[OK] Patient was deleted.\n\n";
                return;
            }
        }

        cout << "[ERROR] Patient was not found\n\n";
    }

    void Sort()
    {
        for (int i = 0; i < _patients.size() - 1; i++)
        {
            for (int j = 0; j < _patients.size() - i - 1; j++)
            {
                if (_patients[j].GetID() > _patients[j + 1].GetID())
                {
                    swap(_patients[j], _patients[j + 1]);
                }
            }
        }
    }

    void ViewPatients()
    {
        if (_patients.empty())
        {
            cout << "No patients found.\n\n";
            return;
        }

        cout << "\n"
            << left << setw(8) << "ID"
            << left << setw(20) << "NAME"
            << left << setw(8) << "AGE"
            << "PHONE\n";

        cout << "---------------------------------------------------------\n";

        for (int i = 0; i < _patients.size(); i++)
        {
            cout << left << setw(8) << _patients[i].GetID()
                << left << setw(20) << _patients[i].GetName()
                << left << setw(8) << _patients[i].GetAge()
                << _patients[i].GetPhone()
                << "\n";
        }

        cout << "\n";
    }
    void Search(int id)
    {
        Sort();

        int beg = 0;
        int end = _patients.size() - 1;
        int mid = 0;
        int counter = 0;

        if (_patients.size() == 0)
        {
            cout << "No patients found.\n\n";
            return;
        }

        while (beg <= end)
        {
            mid = (beg + end) / 2;
            counter++;

            if (id == _patients[mid].GetID())
            {
                cout << "\nPatient found!\n";
                cout << "---------------------------------\n";
                cout << "ID    : " << _patients[mid].GetID() << "\n";
                cout << "Name  : " << _patients[mid].GetName() << "\n";
                cout << "Age   : " << _patients[mid].GetAge() << "\n";
                cout << "Phone : " << _patients[mid].GetPhone() << "\n";
                cout << "---------------------------------\n";

                cout << "Found in "
                    << counter
                    << " comparisons [binary search]\n\n";

                return;
            }

            if (id > _patients[mid].GetID())
            {
                beg = mid + 1;
            }
            else
            {
                end = mid - 1;
            }
        }

        cout << "[ERROR] Patient was not found\n\n";
    }

    void AddHistory(int patientID, PatientVisitDetails visit)
    {
        for (int i = 0; i < _patients.size(); i++)
        {
            if (_patients[i].GetID() == patientID)
            {
                _patients[i].GetHistory().AddVisit(visit);
                return;
            }
        }
    }

    Patient* GetPatientByID(int id)
    {
        for (int i = 0; i < _patients.size(); i++)
        {
            if (_patients[i].GetID() == id)
            {
                return &_patients[i];
            }
        }

        return nullptr;
    }
};