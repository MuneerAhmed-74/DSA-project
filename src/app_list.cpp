#include "app_list.h"
#include "models.h"

AppList::AppList()
{
    front = nullptr;
    rear = nullptr;
    historyHead = nullptr;
}

AppList::~AppList()
{
    AppNode *curr = front;
    while (curr->next != nullptr)
    {
        AppNode *temp = curr;
        curr = curr->next;
        delete temp;
    }

    curr = historyHead;
    while (curr->next != nullptr)
    {
        AppNode *temp = curr;
        curr = curr->next;
        delete temp;
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

void AppList::requestApp(int appID, int patientID, string time, string date)
{
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
