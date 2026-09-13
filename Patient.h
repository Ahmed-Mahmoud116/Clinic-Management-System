#pragma once

#include "Person.h"
#include "History.h"

class Patient : public Person
{
private:
    int _age;
    string _phone;
    History _history;

public:
    Patient(int age, string phone, string name) : Person(name)
    {
        if (age <= 4)
            throw exception();

        if (phone.length() != 11)
            throw exception();

        _age = age;
        _phone = phone;
    }

    int GetAge()
    {
        return _age;
    }

    string GetPhone()
    {
        return _phone;
    }

    vector<PatientVisitDetails> GetVisits()
    {
        return _history.GetVisits();
    }

    void SetPhone(string value)
    {
        if (value.length() != 11)
            throw exception();

        _phone = value;
    }

    History& GetHistory()
    {
        return _history;
    }
};
