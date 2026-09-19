#pragma once

#include <iostream>
#include "Person.h"

using namespace std;

class Fee
{
private:
    double _fee;

public:
    void Calculatefee(string s)
    {
        if (s == "Normal")
        {
            _fee = 200;
        }
        else if (s == "Emergency")
        {
            _fee = 400;
        }
        else
        {
            cout << "Invalid input\n";
            return;
        }
    }

    double GetFee()
    {
        return _fee;
    }
};