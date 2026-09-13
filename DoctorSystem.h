#pragma once

#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "Doctor.h"

using namespace std;

class DoctorSystem
{
private:
    vector<Doctor> _doctors;

public:
    void AddDoctor(Doctor doctor)
    {
        _doctors.push_back(doctor);

        cout << "[OK] Doctor "
            << doctor.GetID()
            << " added.\n\n";
    }

    void ViewDoctors()
    {
        if (_doctors.size() == 0)
        {
            cout << "No doctors.\n\n";
            return;
        }

        cout << "\n"
            << left << setw(8) << "ID"
            << left << setw(20) << "NAME"
            << left << setw(20) << "SPECIALIZATION"
            << "FEE\n";

        cout << "---------------------------------------------------------\n";

        for (int i = 0; i < _doctors.size(); i++)
        {
            cout << left << setw(8) << _doctors[i].GetID()
                << left << setw(20) << _doctors[i].GetName()
                << left << setw(20) << _doctors[i].GetSpecialization()
                << _doctors[i].GetFee()
                << "\n";
        }

        cout << "\n";
    }

    void DeleteDoctor(int id)
    {
        if (_doctors.size() == 0)
        {
            cout << "No doctors.\n\n";
            return;
        }

        for (int i = 0; i < _doctors.size(); i++)
        {
            if (id == _doctors[i].GetID())
            {
                _doctors.erase(_doctors.begin() + i);

                cout << "[OK] Doctor has been deleted.\n\n";
                return;
            }
        }

        cout << "[ERROR] Doctor not found.\n\n";
    }

    void Sort()
    {
        for (int i = 0; i < _doctors.size() - 1; i++)
        {
            for (int j = 0; j < _doctors.size() - i - 1; j++)
            {
                if (_doctors[j].GetID() > _doctors[j + 1].GetID())
                {
                    swap(_doctors[j], _doctors[j + 1]);
                }
            }
        }
    }

    void Search(int id)
    {
        Sort();

        int beg = 0;
        int end = _doctors.size() - 1;
        int mid = 0;
        int counter = 0;

        if (_doctors.size() == 0)
        {
            cout << "No doctors.\n\n";
            return;
        }

        while (beg <= end)
        {
            mid = (beg + end) / 2;
            counter++;

            if (id == _doctors[mid].GetID())
            {
                cout << "Found in "
                    << counter
                    << " comparisons   [binary search]\n\n";

                return;
            }

            if (id > _doctors[mid].GetID())
            {
                beg = mid + 1;
            }
            else
            {
                end = mid - 1;
            }
        }

        cout << "[ERROR] Doctor was not found\n\n";
    }
};