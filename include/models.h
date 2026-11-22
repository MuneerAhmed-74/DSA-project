#ifndef MODELS_H
#define MODELS_H

#include <string>
using namespace std;

struct Patient
{
    int id;
    string name;
    int age;
    string gender;
    string contact;
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
