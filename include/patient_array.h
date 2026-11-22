#ifndef PATIENTARRAY_H
#define PATIENTARRAY_H

#include "patient.h"
#include <string>
#include <vector>

class PatientArray
{
private:
    std::vector<Patient> patients;

    void bubbleSort();
    int binarySearch(int id);
    int getNextId();
    void saveToFile();
    void loadFromFile();

public:
    PatientArray();
    ~PatientArray();

    bool addPatient(const std::string &name, int age,
                    const std::string &gender, const std::string &contact,
                    const std::string &email);
    Patient *searchById(int id);
    bool updateName(int id, const std::string &name);
    bool updateAge(int id, int age);
    bool updateGender(int id, const std::string &gender);
    bool updateContact(int id, const std::string &contact);
    bool updateEmail(int id, const std::string &email);
    bool deletePatient(int id);
    void sortById();
    const std::vector<Patient> &getPatients() const;
};

#endif
