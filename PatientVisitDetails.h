#pragma once

#include <iostream>
#include <ctime>
#include <string>
#include "Person.h"
using namespace std;

class Patient;

class PatientVisitDetails
{
private:
    time_t _date;
    string _doctor;
    string _diagnosis;
    double _fee;
    State _state;
    Patient* _patient;

public:
    PatientVisitDetails(
        string doctor,
        string diagnosis,
        double fee,
        State state,
        Patient* patient
    )
    {
        _date = time(0);
        _doctor = doctor;
        _diagnosis = diagnosis;
        _fee = fee;
        _state = state;
        _patient = patient;
    }

    string GetDate()
    {
        char buffer[80];
        tm timeInfo;

        localtime_s(&timeInfo, &_date);

        strftime(
            buffer,
            sizeof(buffer),
            "%d/%m/%Y %H:%M:%S",
            &timeInfo
        );

        return string(buffer);
    }

    string GetDoctor()
    {
        return _doctor;
    }

    string GetDiagnosis()
    {
        return _diagnosis;
    }

    double GetFee()
    {
        return _fee;
    }

    State GetState()
    {
        return _state;
    }
    string GetPatient();

    int GetPatientID();
};
