#pragma once

#include <iostream>
#include <vector>
#include "PatientVisitDetails.h"

using namespace std;

class History
{
private:
    vector<PatientVisitDetails> _visits;

public:
    vector<PatientVisitDetails> GetVisits()
    {
        return _visits;
    }

    void AddVisit(PatientVisitDetails visit)
    {
        _visits.push_back(visit);
    }

    void ViewHistory()
    {
        if (_visits.size() == 0)
        {
            cout << "No visits.\n";
            return;
        }

        cout << "\n** VISIT HISTORY **\n";
        cout << "----------------------------------------------\n";

        for (int i = 0; i < _visits.size(); i++)
        {
            cout << _visits[i].GetPatient()
                << "      "
                << _visits[i].GetDiagnosis()
                << "     "
                << _visits[i].GetDoctor()
                << "    "
                << _visits[i].GetState()
                << "     "
                << _visits[i].GetFee()
                << "       "
                << _visits[i].GetDate()
                << "\n";
        }

        cout << "----------------------------------------------\n\n";
    }
};