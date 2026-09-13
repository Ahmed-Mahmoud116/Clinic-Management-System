#include "PatientVisitDetails.h"
#include "Patient.h"

string PatientVisitDetails::GetPatient()
{
    return _patient ? _patient->GetName() : "Unknown";
}

int PatientVisitDetails::GetPatientID()
{
    return _patient ? _patient->GetID() : -1;
}