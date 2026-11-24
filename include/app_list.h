#ifndef APP_LIST_H
#define APP_LIST_H
#include "models.h"
#include <string>
using namespace std;

class AppList
{
private:
    AppNode *front;
    AppNode *rear;

    AppNode *historyHead;

    string getStatusString(AppStatus Status);

public:
    AppList();
    ~AppList();

    void requestApp(int appID, int patientID, string time, string date);
    void processNextApp();

    void cancelApp(int appID);
    void displayQueue();
    void displayHistory();

    void saveToFile();
    void loadFromFile();
};

#endif
