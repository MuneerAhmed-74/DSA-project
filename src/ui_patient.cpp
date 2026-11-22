#include "ui_patient.h"
#include "cli_ui.h"
#include "patient_array.h"
#include "patient.h"
#include <iostream>
#include <limits>
#include <string>
#include <cctype>

using namespace std;

static void displayMenuOptions()
{
    cout << "\n\tSelect an action to perform:\n"
         << "\n\t |1. Display" << "\t\t |3. Sort" << "\t\t|5. Search By ID"
         << "\n\t |" << "\t\t\t |" << "\t\t\t|"
         << "\n\t |2. Exit"
         << "\t\t |4. Update" << "\t\t|6. Search By Name"
         << "\n\n\t\tEnter choice: ";
}

static int getChoice()
{
    int choice;
    if (!(cin >> choice))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input!\n";
        return -1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice;
}

static string getValidName()
{
    string name;
    getline(cin, name);

    bool inWord = false;
    for (char &c : name)
    {
        if (c == ' ')
        {
            inWord = false;
        }
        else
        {
            c = inWord ? static_cast<char>(tolower(static_cast<unsigned char>(c)))
                       : static_cast<char>(toupper(static_cast<unsigned char>(c)));
            inWord = true;
        }
    }
    return name;
}

static string getGender()
{
    int choice;
    while (true)
    {
        cout << "Select Gender:\n1. Male\n2. Female\n3. Other\nChoice: ";
        if (cin >> choice && choice >= 1 && choice <= 3)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice!\n";
    }

    if (choice == 1)
        return "Male";
    if (choice == 2)
        return "Female";
    return "Other";
}

static int getPatientId(const string &prompt)
{
    int id;
    cout << prompt;
    while (!(cin >> id) || id <= 0)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ID! Enter again: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return id;
}

static void displayPatients(const PatientList &list)
{
    const vector<Patient> &patients = list.getPatients();
    if (patients.empty())
    {
        cout << "No patients registered yet.\n";
        return;
    }

    cout << "\n--- Patient Records ---\n";
    for (const Patient &patient : patients)
    {
        cout << "ID: " << formatId(patient.id)
             << " | Name: " << patient.name
             << " | Age: " << patient.age
             << " | Gender: " << patient.gender
             << " | Contact: " << patient.contact << '\n';
    }
    cout << "-----------------------\n";
}

void displayPatientMenu()
{
    PatientList list;
    int choice;

    do
    {
        displayHeading("\t\t\tManage Patients\n");
        displayMenuOptions();
        choice = getChoice();

        if (choice == 1)
        {
            cout << "Enter Name: ";
            string name = getValidName();

            int age;
            cout << "Enter Age: ";
            while (!(cin >> age) || age <= 0 || age > 120)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid age! Enter again: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            string gender = getGender();

            string contact;
            cout << "Enter Contact: ";
            getline(cin, contact);
            while (contact.size() != 11 || contact.find_first_not_of("0123456789") != string::npos)
            {
                cout << "Invalid! 11 digits required: ";
                getline(cin, contact);
            }

            if (list.addPatient(name, age, gender, contact))
                cout << "Patient registered successfully.\n";
            else
                cout << "Unable to register patient.\n";
        }
        else if (choice == 2)
        {
            displayPatients(list);
            int id = getPatientId("Enter ID to update (e.g. 1 for P-001): ");
            if (!list.searchById(id))
            {
                cout << "Patient not found!\n";
                continue;
            }

            cout << "1. Name\n2. Age\n3. Gender\n4. Contact\n0. Done\nWhat to update: ";
            int field;
            while (cin >> field)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (field == 0)
                    break;

                if (field == 1)
                {
                    cout << "Enter New Name: ";
                    list.updateName(id, getValidName());
                }
                else if (field == 2)
                {
                    int age;
                    cout << "Enter New Age: ";
                    if (cin >> age)
                        list.updateAge(id, age);
                    else
                        cout << "Invalid Age!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else if (field == 3)
                {
                    list.updateGender(id, getGender());
                }
                else if (field == 4)
                {
                    string contact;
                    cout << "Enter New Contact: ";
                    getline(cin, contact);
                    if (!list.updateContact(id, contact))
                        cout << "Invalid Contact!\n";
                }
                else
                {
                    cout << "Invalid choice!\n";
                }
                cout << "What to update: ";
            }
            cout << "Patient record updated.\n";
        }
        else if (choice == 3)
        {
            displayPatients(list);
            int id = getPatientId("Enter ID to delete (e.g. 1 for P-001): ");
            cout << (list.deletePatient(id) ? "Patient deleted.\n" : "Patient not found!\n");
        }
        else if (choice == 4)
        {
            int id = getPatientId("Enter ID to search (e.g. 1 for P-001): ");
            Patient *patient = list.searchById(id);
            if (patient)
            {
                cout << "Found -> ID: " << formatId(patient->id)
                     << " | Name: " << patient->name
                     << " | Age: " << patient->age
                     << " | Gender: " << patient->gender
                     << " | Contact: " << patient->contact << '\n';
            }
            else
            {
                cout << "Patient not found!\n";
            }
        }
        else if (choice == 5)
        {
            list.sortById();
            displayPatients(list);
        }
        else if (choice == 6)
        {
            displayPatients(list);
        }
        else if (choice == 0)
        {
            cout << "Exiting...\n";
        }
        else if (choice != -1)
        {
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}
