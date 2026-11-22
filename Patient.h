#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <sstream>
#include <iomanip>
#include <cstddef>
using namespace std;

inline string formatId(int id) {
    ostringstream oss;
    oss << "P-" << setw(3) << setfill('0') << id;
    return oss.str();
}

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
