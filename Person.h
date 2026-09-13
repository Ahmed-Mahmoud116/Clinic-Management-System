#pragma once

#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

enum State
{
    Emergency,
    Normal
};

class Person
{
protected:
    string _name;
    int _id;

    Person(string name)
    {
        if (name.empty())
            throw exception();

        _name = name;
        _id = rand() % 10000 + 1;
    }

public:
    string GetName()
    {
        return _name;
    }

    int GetID()
    {
        return _id;
    }
};