#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <string>
#include <vector>
#include <iomanip>
#include "Person.h"
#include "PatientVisitDetails.h"
#include "History.h"
#include "Patient.h"
#include "Doctor.h"
#include "DoctorSystem.h"
#include "PatientSystem.h"
#include "Fee.h"
#include "WaitingRoom.h"
using namespace std;
vector<Patient> PatientSystem::_patients;
vector<PatientVisitDetails> WaitingRoom::_waitingPatients;

void PatientMenu()
{
    cout << "*** PATIENTS MENU ***\n";
    cout << "----------------------------------------------\n";
    cout << "1. Add Patient\n"
        << "2. View all patients\n"
        << "3. Search by ID\n"
        << "4. Delete patient\n"
        << "5. View patient history\n"
        << "6. Sort patients\n"
        << "0. Back\n";
    cout << "----------------------------------------------\n";

    PatientSystem ps;

    int Choice;

    while (true)
    {
        cout << "Choose: ";
        cin >> Choice;

        cout << "\n";

        switch (Choice)
        {
        case 1:
        {
            cout << "Age: ";

            int age;
            cin >> age;

            string name, phone;
            cin.ignore();
            cout << "Name: ";
            getline(cin, name);

            cout << "Phone: ";
            cin >> phone;

            Patient p(age, phone, name);

            ps.AddPatient(p);

            break;
        }

        case 2:
        {
            ps.ViewPatients();
            break;
        }

        case 3:
        {
            cout << "ID: ";

            int id;
            cin >> id;

            ps.Search(id);

            break;
        }

        case 4:
        {
            cout << "ID: ";

            int id;
            cin >> id;

            ps.DeletePatient(id);

            break;
        }

        case 5:
        {
            int id;

            cout << "Enter patient ID: ";
            cin >> id;

            Patient* patient = ps.GetPatientByID(id);

            if (patient == nullptr)
            {
                cout << "[ERROR] Patient was not found.\n\n";
                break;
            }

            patient->GetHistory().ViewHistory();

            break;
        }

        case 6:
            ps.Sort();
            break;

        case 0:
            return;

        default:
            cout << "Invalid input\n\n";
        }
    }
}

void DoctorMenu()
{
    cout << "*** DOCTORS MENU ***\n";
    cout << "----------------------------------------------\n";
    cout << "1. Add doctor\n"
        << "2. View all doctors\n"
        << "3. Delete doctor\n"
        <<"4. Search for a doctor\n"
        << "0. Back\n";
    cout << "----------------------------------------------\n";

    int Choice;
    DoctorSystem ds;

    while (true)
    {
        cout << "Choose: ";
        cin >> Choice;

        cout << "\n";

        switch (Choice)
        {
        case 1:
        {
            cin.ignore();
            cout << "Name: ";

            string specialization, name;
            double consultationFee;

            getline(cin, name);
            cin.ignore();

            cout << "Specialization: ";
            getline(cin, specialization);
            cin.ignore();
            cout << "Consultation fee: ";
            cin >> consultationFee;

            Doctor doctor(
                specialization,
                name,
                consultationFee
            );

            ds.AddDoctor(doctor);

            break;
        }

        case 2:
            ds.ViewDoctors();
            break;

        case 3:
        {
            cout << "ID: ";

            int id;
            cin >> id;

            ds.DeleteDoctor(id);

            break;
        }

        case 4:
        {
            cout << "ID: ";
            int id;
            cin >> id;
            ds.Search(id);
            break;
        }
        case 0:
            return;

        default:
            cout << "Invalid input\n\n";
            break;
        }
    }
}

void WaitingRoomMenu()
{
    cout << "*** WAITING ROOM - THE CORE FEATURE ***\n";
    cout << "----------------------------------------------\n";
    cout << "1. Add to waiting room\n"
        << "2. View who is waiting\n"
        << "3. Call next patient\n"
        << "0. Back\n";
    cout << "----------------------------------------------\n";

    int Choice;
    DoctorSystem ds;
    WaitingRoom w(ds);

    while (true)
    {
        cout << "Choose: ";
        cin >> Choice;

        cout << "\n";

        switch (Choice)
        {
        case 1:
        {
            cout << "ID: ";

            int id;
            cin >> id;

            w.AddToWaitingRoom(id);

            break;
        }

        case 2:
        {
            w.ViewWaitingPatients();
            break;
        }

        case 3:
        {
            w.CallPatient();
            break;
        }

        case 0:
            return;

        default:
            cout << "Invalid input\n\n";
        }
    }
}

int main()
{
    int Choice;

    srand(time(0));

    while (true)
    {
        cout << "*** CLINIC MANAGEMENT SYSTEM ***\n";
        cout << "----------------------------------------------\n";
        cout << "1. Patients\n"
            << "2. Doctors\n"
            << "3. Waiting Room\n"
            << "0. Exit\n";
        cout << "----------------------------------------------\n";

        cout << "Choose: ";
        cin >> Choice;

        cout << "\n";

        switch (Choice)
        {
        case 1:
            PatientMenu();
            break;

        case 2:
            DoctorMenu();
            break;

        case 3:
            WaitingRoomMenu();
            break;

        case 0:
            return 0;

        default:
            cout << "Invalid input\n\n";
        }
    }
}