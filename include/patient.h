#ifndef PATIENT_H
#define PATIENT_H

#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

inline string formatId(int id)
{
    ostringstream oss;
    oss << "P-" << setw(3) << setfill('0') << id;
    return oss.str();
}

struct Patient
{
    int id;
    string name;
    int age;
    string gender;
    string contact;
    string email;

    Patient(int pId, string pName, int pAge, string pGender,
            string pContact, string pEmail)
    {
        id = pId;
        name = pName;
        age = pAge;
        gender = pGender;
        contact = pContact;
        email = pEmail;
    }
};

#endif
