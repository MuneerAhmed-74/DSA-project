#ifndef PATIENT_H
#define PATIENT_H

#include <string>
using namespace std;

class Patient {
public:
    int id;
    string name;
    int age;
    string gender;
    string contact;
    Patient* next;

    Patient(int pId, string pName, int pAge, string pGender, string pContact) {
        id = pId;
        name = pName;
        age = pAge;
        gender = pGender;
        contact = pContact;
        next = NULL;
    }
};

#endif