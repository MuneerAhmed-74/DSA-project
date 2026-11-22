#ifndef PATIENTLIST_H
#define PATIENTLIST_H

#include "Patient.h"
#include <string>
using namespace std;

class PatientList {
private:
    Patient* head;

public:
    PatientList();
    ~PatientList();

    bool patientExists(int id);
    int getNextId();
    string getGender();
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
