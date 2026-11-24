#ifndef APP_LIST_H
#define APP_LIST_H
#include "models.h"
#include <string>
using namespace std;

class AppList
{
private:
    AppNode *head;
    AppNode *tail;

    string getStatusString(AppStatus Status);

public:
    AppList();
    ~AppList();

    void requestApp(int appID, int patientID, string time, string date);
    void processNextApp();

    void cancelApp();
    void displayAllApp();

    void saveToFile();
    void loadFromFile();
};

#endif
