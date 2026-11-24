#include "ui_app.h"
#include "app_list.h"
#include "cli_ui.h"
#include "models.h"
#include "patient_array.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

namespace
{
    void displayMenuOptions()
    {
        cout << "\n\tSelect an action to perform:\n"
             << "\n\t |1. Display Queue" << "\t |3. Request" << "\t\t |5. Display History"
             << "\n\t |" << "\t\t\t |" << "\t\t\t |"
             << "\n\t |2. Back" << "\t\t |4. Process Next" << "\t |6. Cancel"
             << "\n\n\t\tEnter choice: ";
    }

    int getChoice()
    {
        int choice;
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            return -1;
        }
        cin.ignore(1000, '\n');
        return choice;
    }

    int getPositiveInt(const string &prompt)
    {
        int value;
        cout << prompt;
        while (!(cin >> value) || value <= 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\tEnter a positive number: ";
        }
        cin.ignore(1000, '\n');
        return value;
    }

    bool isValidDate(const string &date)
    {
        if (date.size() != 10 || date[4] != '-' || date[7] != '-')
            return false;
        for (size_t i = 0; i < date.size(); ++i)
        {
            if (i != 4 && i != 7 && !isdigit(date[i]))
                return false;
        }
        return true;
    }

    bool isValidTime(const string &time)
    {
        if (time.size() != 5 || time[2] != ':')
            return false;
        if (!isdigit(time[0]) ||
            !isdigit(time[1]) ||
            !isdigit(time[3]) ||
            !isdigit(time[4]))
            return false;
        int hour = stoi(time.substr(0, 2));
        int minute = stoi(time.substr(3, 2));
        return hour < 24 && minute < 60;
    }

    string getDate()
    {
        string date;
        cout << "\n\tEnter Date (YYYY-MM-DD): ";
        getline(cin, date);
        while (!isValidDate(date))
        {
            cout << "\tInvalid date format. Use YYYY-MM-DD: ";
            getline(cin, date);
        }
        return date;
    }

    string getTime()
    {
        string time;
        cout << "\tEnter Time (HH:MM, 24-hour): ";
        getline(cin, time);
        while (!isValidTime(time))
        {
            cout << "\tInvalid time. Use HH:MM (24-hour): ";
            getline(cin, time);
        }
        return time;
    }

    string appIdText(int id)
    {
        ostringstream result;
        result << "A-" << setw(3) << setfill('0') << id;
        return result.str();
    }

    string statusText(AppStatus status)
    {
        switch (status)
        {
        case SCHEDULED:
            return "Scheduled";
        case COMPLETED:
            return "Completed";
        case CANCELLED:
            return "Cancelled";
        }
        return "Unknown";
    }

    string cell(const string &value, size_t width)
    {
        string result = value.substr(0, width);
        if (result.size() < width)
            result.append(width - result.size(), ' ');
        return result;
    }

    void displayAppointments(const AppNode *appointments, const string &emptyMessage)
    {
        if (appointments == nullptr)
        {
            cout << emptyMessage << '\n';
            return;
        }

        cout << "\n\t+----------+------------+------------+----------+--------------+\n"
             << "\t| ID       | Patient ID | Date       | Time     | Status       |\n"
             << "\t+----------+------------+------------+----------+--------------+\n";
        for (const AppNode *appointment = appointments; appointment != nullptr;
             appointment = appointment->next)
        {
            cout << "\t| " << cell(appIdText(appointment->appID), 8)
                 << " | " << cell(formatId(appointment->patientID), 10)
                 << " | " << cell(appointment->date, 10)
                 << " | " << cell(appointment->time, 8)
                 << " | " << cell(statusText(appointment->status), 12) << " |\n";
        }
        cout << "\t+----------+------------+------------+----------+--------------+\n";
    }
} // namespace

void displayAppointmentMenu()
{
    AppList appointments;
    PatientArray patients;

    while (true)
    {
        displayHeading("\t\t\tManage Appointments\n");
        displayMenuOptions();
        int choice = getChoice();

        switch (choice)
        {
        case 1:
            displayHeading("\t\t\tAppointment Queue\n");
            displayAppointments(appointments.getQueue(), "\n\tNo appointments in the queue.");
            waitForEnter();
            break;

        case 2:
            return;

        case 3:
        {
            displayHeading("\t\t\tRequest Appointment\n");
            int patientID = getPositiveInt("\n\tEnter Patient ID (e.g. 1 for P-001): ");
            if (patients.searchById(patientID) == nullptr)
            {
                cout << "\n\tPatient not found. Register the patient first.\n";
                waitForEnter();
                break;
            }

            string date = getDate();
            string time = getTime();
            if (appointments.hasScheduledSlot(time, date))
            {
                cout << "\n\tThat date and time is already booked. Choose another slot.\n";
                waitForEnter();
                break;
            }

            int appID = appointments.getNextAppID();
            if (appointments.requestApp(appID, patientID, time, date))
                cout << "\n\tAppointment " << appIdText(appID) << " added to the queue.\n";
            else
                cout << "\n\tThat date and time is already booked. Choose another slot.\n";
            waitForEnter();
            break;
        }

        case 4:
            displayHeading("\t\t\tProcess Next Appointment\n");
            if (appointments.processNextApp())
                cout << "\n\tThe next appointment has been completed.\n";
            else
                cout << "\n\tThere are no appointments to process.\n";
            waitForEnter();
            break;

        case 5:
            displayHeading("\t\t\tAppointment History\n");
            displayAppointments(appointments.getHistory(), "\n\tNo appointment history yet.");
            waitForEnter();
            break;

        case 6:
        {
            displayHeading("\t\t\tCancel Appointment\n");
            if (appointments.getQueue() == nullptr)
            {
                cout << "\n\tNo appointments in the queue to cancel.\n";
                waitForEnter();
                break;
            }

            displayAppointments(appointments.getQueue(), "\n\tNo appointments in the queue.");
            int appID = getPositiveInt("\n\tEnter Appointment ID to cancel (e.g. 1 for A-001): ");
            if (appointments.cancelApp(appID))
                cout << "\n\tAppointment " << appIdText(appID) << " cancelled.\n";
            else
                cout << "\n\tAppointment not found in the queue.\n";
            waitForEnter();
            break;
        }

        case -1:
            cout << "\n\tInvalid input. Enter a number from 1 to 6.\n";
            waitForEnter();
            break;

        default:
            cout << "\n\tInvalid choice. Enter a number from 1 to 6.\n";
            waitForEnter();
            break;
        }
    }
}
