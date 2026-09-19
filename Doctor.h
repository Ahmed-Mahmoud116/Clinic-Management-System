#pragma once

#include "Person.h"

class Doctor : public Person
{
private:
    string _specialization;
    double _consultationFee;

public:
    Doctor(string specialization, string name, double fee) : Person(name)
    {
        if (specialization.empty())
            throw exception();
        if (fee <= 0) throw exception();
        _specialization = specialization;
        _consultationFee = fee;
    }

    string GetSpecialization()
    {
        return _specialization;
    }

    double GetFee()
    {
        return _consultationFee;
    }
};