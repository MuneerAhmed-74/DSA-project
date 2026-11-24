#include "app_list.h"
#include "models.h"
#include <fstream>
#include <iostream>

using namespace std;

AppList::AppList()
{
    front = nullptr;
    rear = nullptr;
    historyHead = nullptr;
    loadFromFile();
}

AppList::~AppList()
{
    saveToFile();
    AppNode *curr = front;
    while (curr != nullptr)
    {
        AppNode *next = curr->next;
        delete curr;
        curr = next;
    }

    curr = historyHead;
    while (curr != nullptr)
    {
        AppNode *next = curr->next;
        delete curr;
        curr = next;
    }
}

string AppList::getStatusString(AppStatus status)
{
    if (status == SCHEDULED)
        return "Scheduled";
    if (status == COMPLETED)
        return "Completed";
    return "Cancelled";
}

bool AppList::requestApp(int appID, int patientID, string time, string date)
{
    if (hasScheduledSlot(time, date))
        return false;

    AppNode *newNode = new AppNode();
    newNode->appID = appID;
    newNode->patientID = patientID;
    newNode->time = time;
    newNode->date = date;
    newNode->status = SCHEDULED;
    newNode->next = nullptr;

    if (front == nullptr)
        front = rear = newNode;
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
    return true;
}

bool AppList::hasScheduledSlot(const string &time, const string &date) const
{
    const AppNode *curr = front;
    while (curr != nullptr)
    {
        if (curr->date == date && curr->time == time)
            return true;
        curr = curr->next;
    }
    return false;
}

bool AppList::processNextApp()
{
    if (front == nullptr)
    {
        return false;
    }

    AppNode *processed = front;
    front = front->next;

    if (front == nullptr)
        rear = nullptr;

    processed->status = COMPLETED;
    processed->next = historyHead;
    historyHead = processed;

    return true;
}

bool AppList::cancelApp(int appID)
{
    if (front == nullptr)
    {
        return false;
    }

    AppNode *currNode = front;
    AppNode *prevNode = nullptr;

    while (
        currNode != nullptr &&
        currNode->appID != appID)
    {

        prevNode = currNode;
        currNode = currNode->next;
    }

    if (currNode == nullptr)
        return false;

    if (prevNode == nullptr)
    {
        front = currNode->next;
        if (front == nullptr)
            rear = nullptr;
    }
    else
    {
        prevNode->next = currNode->next;
        if (currNode == rear)
            rear = prevNode;
    }

    currNode->status = CANCELLED;
    currNode->next = historyHead;
    historyHead = currNode;

    return true;
}

const AppNode *AppList::getQueue() const
{
    return front;
}

const AppNode *AppList::getHistory() const
{
    return historyHead;
}

int AppList::getNextAppID() const
{
    int nextID = 1;
    const AppNode *curr = front;
    while (curr != nullptr)
    {
        if (curr->appID >= nextID)
            nextID = curr->appID + 1;
        curr = curr->next;
    }

    curr = historyHead;
    while (curr != nullptr)
    {
        if (curr->appID >= nextID)
            nextID = curr->appID + 1;
        curr = curr->next;
    }
    return nextID;
}

void AppList::saveToFile()
{
    ofstream file("data/appointments.txt");
    if (!file.is_open())
    {
        cout << "Error opening file for saving.\n";
        return;
    }

    AppNode *curr = front;
    while (curr != nullptr)
    {
        file << curr->appID << " " << curr->patientID << " "
             << curr->date << " " << curr->time << " " << curr->status << "\n";
        curr = curr->next;
    }

    curr = historyHead;
    while (curr != nullptr)
    {
        file << curr->appID << " " << curr->patientID << " "
             << curr->date << " " << curr->time << " " << curr->status << "\n";
        curr = curr->next;
    }

    file.close();
}

void AppList::loadFromFile()
{
    ifstream file("data/appointments.txt");
    if (!file.is_open())
    {
        return;
    }

    int appID, patientID, statusInt;
    string date, time;

    while (file >> appID >> patientID >> date >> time >> statusInt)
    {
        AppNode *newNode = new AppNode();
        newNode->appID = appID;
        newNode->patientID = patientID;
        newNode->date = date;
        newNode->time = time;
        newNode->status = static_cast<AppStatus>(statusInt);
        newNode->next = nullptr;

        if (newNode->status == SCHEDULED)
        {
            if (front == nullptr)
            {
                front = rear = newNode;
            }
            else
            {
                rear->next = newNode;
                rear = newNode;
            }
        }
        else if (historyHead == nullptr)
        {
            historyHead = newNode;
        }
        else
        {
            AppNode *tail = historyHead;
            while (tail->next != nullptr)
                tail = tail->next;
            tail->next = newNode;
        }
    }
    file.close();
}
