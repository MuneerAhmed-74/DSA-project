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

    bool requestApp(int appID, int patientID, string time, string date);
    bool hasScheduledSlot(const string &time, const string &date) const;
    bool processNextApp();

    bool cancelApp(int appID);
    const AppNode *getQueue() const;
    const AppNode *getHistory() const;
    int getNextAppID() const;

    void saveToFile();
    void loadFromFile();
};

#endif
