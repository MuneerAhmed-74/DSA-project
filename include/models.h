#ifndef MODELS_H
#define MODELS_H

#include <iomanip>
#include <sstream>
#include <string>
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
        : id(pId), name(pName), age(pAge), gender(pGender),
          contact(pContact), email(pEmail)
    {
    }
};

enum AppStatus
{
    SCHEDULED,
    COMPLETED,
    CANCELLED
};

struct AppNode
{
    int appID;
    int patientID;
    string timeSlot;
    AppStatus status;
    AppNode *next;
};

#endif
