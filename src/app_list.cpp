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
