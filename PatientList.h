#ifndef PATIENTLIST_H
#define PATIENTLIST_H

#include "Patient.h"
#include <string>
#include <vector>
using namespace std;

class PatientList {
private:
    vector<Patient> patients;
    int findIndex(int id);

public:
    PatientList();
    ~PatientList();

    bool patientExists(int id);
    int getNextId();
    string getGender();
    string formatName(string name);
    void addPatient(string name, int age, string gender, string contact);
    Patient* searchById(int id);
    void updatePatient(int id);
    void deletePatient(int id);
    void sortById();
    void displayAll();
    void saveToFile();
    void loadFromFile();
};

#endif
