#include <iostream>
#include<cstdlib>
#include<ctime>
#include<stdexcept>
#include<string>
#include<vector>
using namespace std;
enum State
{
    Emergency, Normal
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
class Patient;
class PatientVisitDetails
{
private:
    time_t _date;
    string _doctor;
    string _diagnosis;
    double _fee;
    State _state;
    Patient* _patient = nullptr;
public:
    PatientVisitDetails(string doctor, string diagnosis, double fee, State state, Patient* p)
    {
        if (doctor.empty()) throw exception();
        if (diagnosis.empty()) throw exception();
        if (fee < 0) throw exception();
        if (p == nullptr) throw exception();
        _doctor = doctor;
        _diagnosis = diagnosis;
        _fee = fee;
        _state = state;
        this->_patient = p;
        _date = time(nullptr);
    }
    time_t GetDate()
    {
        return _date;
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
    int GetPatientID()
    {
        return _patient->GetID();
    }

};
class History
{
private:
    vector<PatientVisitDetails>_visits;
public:
    vector<PatientVisitDetails>GetVisits()
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
        for (int i = 0; i < _visits.size(); i++)
        {
            cout << _visits[i].GetPatient() << "      " << _visits[i].GetDiagnosis() << "     " << _visits[i].GetDoctor() << "    " << _visits[i].GetState() << "     " << _visits[i].GetFee() << "       " << _visits[i].GetDate() << "\n";
        }
    }

};
class Patient :public Person
{
private:
    int _age;
    string _phone;
    History _history;
public:
    Patient(int age, string phone, string name) :Person(name)
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
    vector <PatientVisitDetails> GetVisits()
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
string PatientVisitDetails::GetPatient()
{
    return _patient->GetName();
}
class Doctor :public Person
{
private:
    string _specialization;
    double _consultationFee;
public:
    Doctor(string specialization, string name, double fee) :Person(name)
    {
        if (specialization.empty())
            throw exception();

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
class DoctorSystem
{
private:
    vector<Doctor>_doctors;
public:
    void AddDoctor(Doctor doctor)
    {
        _doctors.push_back(doctor);
        cout << "[OK] Doctor " << doctor.GetID() << " added.\n";
    }
    void ViewDoctors()
    {
        if (_doctors.size() == 0)
        {
            cout << "No doctors.\n";
            return;
        }
        
        for (int i = 0; i < _doctors.size(); i++)
        {
            cout << i + 1 << ". " << _doctors[i].GetName() << "         " << _doctors[i].GetSpecialization() << "       " << _doctors[i].GetFee() << "\n";
        }
    }
    void DeleteDoctor(int id)
    {
        if (_doctors.size() == 0)
        {
            cout << "No doctors.\n";
            return;
        }
        for (int i = 0; i < _doctors.size(); i++)
        {
            if (id == _doctors[i].GetID())
            {
                _doctors.erase(_doctors.begin() + i);
                cout << "[OK] Doctor has been deleted.\n";
                return;
            }
        }
        cout << "[ERROR] Doctor not found.\n";
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
            cout << "No doctors.\n";
            return;
        }


        while (beg <= end)
        {
            mid = (beg + end) / 2;
            counter++;
            if (id == _doctors[mid].GetID())
            {
                cout << "Found in " << counter << " comparisons   [binary search]\n";
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
        cout << "[ERROR] Doctor was not found\n";
    }



};

class PatientSystem
{
private:
    static vector<Patient>_patients;
public:
    static vector<Patient>& GetPatients()
    {
        return _patients;
    }

    void AddPatient(Patient patient)
    {
        _patients.push_back(patient);
        cout << "[OK] Patient" << patient.GetID() << " was added.\n";
    }
    void DeletePatient(int id)
    {
        for (int i = 0; i < _patients.size();i++)
        {
            if (id == _patients[i].GetID())
            {
                _patients.erase(_patients.begin() + i);
                cout << "[OK] Patient was deleted.\n";
                return;
            }
        }
        cout << "[ERROR] Patient was not found\n";
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
        for (int i = 0; i < _patients.size(); i++)
        {
            cout<<"ID: " << _patients[i].GetID() << "   " << "  Name: " << _patients[i].GetName() << " Age" << _patients[i].GetAge() << " Phone: " << _patients[i].GetPhone() << "\n";
        }

    }
    void Search(int id)
    {
        Sort();
        int beg = 0;
        int end = _patients.size() - 1;
        int mid = 0;
        int counter = 0;
        while (beg <= end)
        {
            mid = (beg + end) / 2;
            counter++;
            if (id == _patients[mid].GetID())
            {
                cout << "Found in " << counter << " comparisons   [binary search]\n";
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
        cout << "[ERROR] Patient was not found\n";

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
class Fee
{
private:
    double _fee;
public:
    void Calculatefee(State s)
    {
        if (s == Normal)
        {
            _fee = 200;

        }
        else if (s == Emergency)
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

class WaitingRoom
{
private:
    static vector<PatientVisitDetails>_waitingPatients;
    vector<Patient>& _patients;
public:
    WaitingRoom()
        :_patients(PatientSystem::GetPatients())
    {

    }


    void  AddToWaitingRoom(int id)
    {
        if (_patients.size() == 0)
        {
            cout << "No appointments\n";
            return;
        }
        string doctor, diagnosis;
        State state;
        int Choose;

        for (int i = 0; i < _patients.size(); i++)
        {
            if (id == _patients[i].GetID())
            {

                cout << "Case type : (1) Emergency (2) Normal\n Choose: ";
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
                    cout << "Invalid input\n";
                    return;

                }
                cout << "Doctor : \n Choose: ";
                cin >> doctor;
                cout << "Diagnosis: \n Choose: ";
                cin >> diagnosis;
                Fee f;
                f.Calculatefee(state);
                PatientVisitDetails pd(doctor, diagnosis, f.GetFee(), state, &_patients[i]);
                _waitingPatients.push_back(pd);
                cout << "[OK] Patient " << _patients[i].GetID() << " added to waiting room\n date: " << pd.GetDate() << "\n";
                return;

            }
        }

        cout << "[ERROR] Patient was not found\n";
    }
    void SortByPriority()
    {
        for (int i = 0; i < _waitingPatients.size() - 1; i++)
        {
            for (int j = 0; j < _waitingPatients.size() - i - 1; j++)
            {
                if ((_waitingPatients[j].GetState() == Normal && _waitingPatients[j + 1].GetState() == Emergency) || (_waitingPatients[j].GetState() == _waitingPatients[j + 1].GetState() && _waitingPatients[j].GetDate() > _waitingPatients[j + 1].GetDate()))
                {
                    swap(_waitingPatients[j], _waitingPatients[j + 1]);
                }
            }
        }
    }
    void ViewWaitingPatients()
    {
        if (_waitingPatients.empty())
        {
            cout << "No waiting patients.\n";
            return;
        }
        SortByPriority();
        for (int i = 0; i < _waitingPatients.size(); i++)
        {
            cout << i + 1 << "    " << _waitingPatients[i].GetPatient() << "      " << _waitingPatients[i].GetState() << "      " << _waitingPatients[i].GetDate() << "\n";
        }
    }
    void CallPatient()
    {
        SortByPriority();
        if (_waitingPatients.empty())
        {
            cout << "No waiting patients.\n";
            return;
        }
        cout << ">>> NOW CALLING: " << _waitingPatients[0].GetPatient() << "   (" << _waitingPatients[0].GetState() << ")\n\n Doctor    : Dr." << _waitingPatients[0].GetDoctor() << "\n Diagnosis : " << _waitingPatients[0].GetDiagnosis() << "\n" << _waitingPatients[0].GetFee() << "\n";
        PatientSystem ps;
        ps.AddHistory(
            _waitingPatients[0].GetPatientID(),
            _waitingPatients[0]
        );
        _waitingPatients.erase(_waitingPatients.begin());

        cout << "[OK] Visit added to history. " << _waitingPatients.size() << " still waiting.";



    }
};
vector<Patient> PatientSystem::_patients;
vector<PatientVisitDetails> WaitingRoom::_waitingPatients;
void PatientMenu()
{
    cout << "-----------------PATIENTS------------------\n";
    cout << "1. Add Patient\n2. View all patients\n3. Search by ID\n4. Delete patient\n5. View patient history\n6. Sort patients\n0. Back\n";
    cout << "--------------------------------------------------\n";
    PatientSystem ps;

    int Choice;

    while (true)
    {
        cout << "Choose: ";
        cin >> Choice;
        cout << "\n\n";
        switch (Choice)
        {
        case 1:
        {
            cout << "Age: ";
            int age;
            cin >> age;
            string name, phone;
            cout << "Name: ";
            cin >> name;
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
                cout << "[ERROR] Patient was not found.\n";
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
    cout << "--------------------------DOCTORS----------------------\n";
    cout << "1. Add doctor\n2. View all doctors\n3. Delete doctor\n0. Back\n";
    cout << "--------------------------------------------------------------\n";
    int Choice;
    DoctorSystem ds;
    while (true)
    {
        cout << "Choose: ";
        cin >> Choice;
        cout << "\n\n";
        switch (Choice)
        {
        case 1:
        {
            cout << "Name: ";
            string specialization, name;
            double consultationFee;
            cin >> name;
            cout << "Specialization: ";
            cin >> specialization;
            cout << "Consultation fee: ";
            cin >> consultationFee;
            Doctor doctor(specialization, name, consultationFee);
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
    cout << "-----------------WAITING ROOM------------------\n";
    cout << "1. Add to waiting room\n2. View who is waiting\n3. Call next patient\n0. Back\n";
    cout << "--------------------------------------------------\n";
    int Choice;
    WaitingRoom w;
    while (true)
    {
        cout << "Choose: ";
        cin >> Choice;
        cout << "\n\n";

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

        cout << "=======================================\n" << "      CLINIC MANAGEMENT SYSTEM\n" << "=======================================\n";
        cout << "1. Patients\n" << "2. Doctors\n" << "3. Waiting Room\n" << "0. Exit\n --------------------------------------------\n";
        cout << "Choose: ";
        cin >> Choice;
        cout << "\n\n";
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

