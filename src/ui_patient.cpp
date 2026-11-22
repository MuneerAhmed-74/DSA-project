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
         << "\n\t |1. Display" << "\t\t |3. Register" << "\t\t|5. Search By ID"
         << "\n\t |" << "\t\t\t |" << "\t\t\t|"
         << "\n\t |2. Exit"
         << "\t\t |4. Update" << "\t\t|6. Sort"
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

static void displayPatient(const Patient &patient)
{
    string table = R"(
	+--------------------+--------------------------------------+
	| Field              | Details                              |
	+--------------------+--------------------------------------+
	| ID                 | {{ID}}                                |
	|                    |                                      |
	| Name               | {{NAME}}                                 |
	|                    |                                      |
	| Age                | {{AGE}}                                   |
	|                    |                                      |
	| Gender             | {{GENDER}}                                 |
	|                    |                                      |
	| Contact            | {{CONTACT}}                          |
	+--------------------+--------------------------------------+)";

    size_t position;

    position = table.find("{{ID}}");
    table.replace(position, 6, formatId(patient.id));

    position = table.find("{{NAME}}");
    table.replace(position, 8, patient.name);

    position = table.find("{{AGE}}");
    table.replace(position, 7, to_string(patient.age));

    position = table.find("{{GENDER}}");
    table.replace(position, 10, patient.gender);

    position = table.find("{{CONTACT}}");
    table.replace(position, 11, patient.contact);

    cout << table << '\n';
}

static void displayPatients(const PatientList &list)
{
    const vector<Patient> &patients = list.getPatients();
    if (patients.empty())
    {
        cout << "No patients registered yet.\n";
        return;
    }

    cout << "\n\t+--------+----------------------+-----+----------+-------------+\n"
         << "\t| ID     | Name                 | Age | Gender   | Contact     |\n"
         << "\t+--------+----------------------+-----+----------+-------------+\n";

    for (const Patient &patient : patients)
    {
        cout << "\t| " << formatId(patient.id);
        cout << string(7 - formatId(patient.id).length(), ' ') << "| " << patient.name;
        cout << string(21 - patient.name.length(), ' ') << "| " << patient.age;
        cout << string(4 - to_string(patient.age).length(), ' ') << "| " << patient.gender;
        cout << string(9 - patient.gender.length(), ' ') << "| " << patient.contact;
        cout << string(12 - patient.contact.length(), ' ') << "|\n";
    }

    cout << "\t+--------+----------------------+-----+----------+-------------+\n";
}

static void displayUpdateMenu()
{
    displayHeading("\t\t\tUpdate Patient\n");

    cout << "\n\t |1. ID" << "\t\t |5. Contact"
         << "\n\t |" << "\t\t\t |"
         << "\n\t |2. Name" << "\t\t |6. Back"
         << "\n\t |" << "\t\t\t |"
         << "\n\t |3. Age" << "\t\t |"
         << "\n\t |" << "\t\t\t |"
         << "\n\t |4. Gender"
         << "\n\n\tSelect a field to update: ";
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

        switch (choice)
        {
        case 1:
            displayHeading("\t\t\tDisplay Patients\n");
            displayPatients(list);
            waitForEnter();
            break;

        case 2:
            return;

        case 3:
        {
            displayHeading("\t\t\tRegister Patient\n");

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

            waitForEnter();
            break;
        }

        case 4:
        {
            displayHeading("\t\t\tUpdate Patient\n");
            displayPatients(list);
            int id = getPatientId("\n\tEnter ID to update (e.g. 1 for P-001): ");
            if (!list.searchById(id))
            {
                cout << "Patient not found!\n";
                waitForEnter();
                break;
            }

            displayUpdateMenu();

            int field;
            while (cin >> field)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (field == 0)
                    break;

                if (field == 6)
                    break;

                if (field == 1)
                {
                    int newId;
                    cout << "\n\tEnter New ID: ";
                    while (!(cin >> newId) || newId <= 0)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid ID! Enter again: ";
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (list.updateId(id, newId))
                    {
                        id = newId;
                        cout << "\n\tPatient ID updated successfully.\n";
                    }
                    else
                    {
                        cout << "\n\tInvalid ID or ID already exists.\n";
                    }
                }
                else if (field == 2)
                {
                    cout << "\n\tEnter New Name: ";
                    list.updateName(id, getValidName());
                }
                else if (field == 3)
                {
                    int age;
                    cout << "\n\tEnter New Age: ";
                    if (cin >> age)
                        list.updateAge(id, age);
                    else
                        cout << "\n\tInvalid Age!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                else if (field == 4)
                {
                    cout << "\n";
                    list.updateGender(id, getGender());
                }
                else if (field == 5)
                {
                    string contact;
                    cout << "\n\tEnter New Contact: ";
                    getline(cin, contact);
                    if (!list.updateContact(id, contact))
                        cout << "\n\tInvalid Contact!\n";
                }
                else
                {
                    cout << "\n\tInvalid choice!\n";
                }
                displayUpdateMenu();
            }
            cout << "\n\tPatient record updated.\n";
            waitForEnter();
            break;
        }

        case 5:
        {
            displayHeading("\t\t\tSearch Patient by ID\n");
            int id = getPatientId("\n\tEnter ID to search (e.g. 1 for P-001): ");
            Patient *patient = list.searchById(id);
            if (patient)
            {
                displayPatient(*patient);
            }
            else
            {
                cout << "Patient not found!\n";
            }
            waitForEnter();
            break;
        }

        case 6:
            displayHeading("\t\t\tSort Patients\n");
            list.sortById();
            displayPatients(list);
            waitForEnter();
            break;

        case -1:
            displayHeading("\t\t\tInvalid Input\n");
            cout << "Invalid input!\n";
            waitForEnter();
            break;

        default:
            displayHeading("\t\t\tInvalid Choice\n");
            cout << "Invalid choice!\n";
            waitForEnter();
            break;
        }
    } while (choice != 2);
}
