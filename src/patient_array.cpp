#include "patient_array.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <cctype>

PatientList::PatientList()
{
    loadFromFile();
}

PatientList::~PatientList()
{
    saveToFile();
}

void PatientList::bubbleSort()
{
    bool swapped;
    do
    {
        swapped = false;
        for (size_t i = 0; i + 1 < patients.size(); i++)
        {
            if (patients[i].id > patients[i + 1].id)
            {
                swap(patients[i], patients[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

int PatientList::binarySearch(int id)
{
    bubbleSort();
    int low = 0;
    int high = (int)patients.size() - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (patients[mid].id == id)
        {
            return mid;
        }
        if (patients[mid].id < id)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1;
}

bool PatientList::patientExists(int id)
{
    return binarySearch(id) != -1;
}

int PatientList::getNextId()
{
    if (patients.empty())
    {
        return 1;
    }
    return patients.back().id + 1;
}

string PatientList::getGender()
{
    cout << "Select Gender:\n1. Male\n2. Female\n3. Other" << endl;
    int c;
    while (true)
    {
        cout << "Choice: ";
        if (cin >> c && c >= 1 && c <= 3)
            break;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice!" << endl;
    }
    cin.ignore(1000, '\n');
    if (c == 1)
        return "Male";
    if (c == 2)
        return "Female";
    return "Other";
}

string PatientList::formatName(string name)
{
    for (size_t i = 0; i < name.size(); i++)
    {
        if (i == 0 || name[i - 1] == ' ')
        {
            name[i] = toupper(name[i]);
        }
        else
        {
            name[i] = tolower(name[i]);
        }
    }
    return name;
}

void PatientList::addPatient(string name, int age, string gender, string contact)
{
    if (age <= 0)
    {
        cout << "Invalid Age!" << endl;
        return;
    }
    int id = getNextId();

    patients.push_back(Patient(id, name, age, gender, contact));
    size_t i = patients.size() - 1;
    while (i > 0 && patients[i - 1].id > patients[i].id)
    {
        swap(patients[i - 1], patients[i]);
        i--;
    }
    cout << "Patient registered successfully. ID: " << formatId(id) << endl;
}

Patient *PatientList::searchById(int id)
{
    int index = binarySearch(id);
    if (index == -1)
    {
        return NULL;
    }
    return &patients[index];
}

void PatientList::updatePatient(int id)
{
    Patient *target = searchById(id);
    if (target == NULL)
    {
        cout << "Patient not found!" << endl;
        return;
    }

    int choice;
    do
    {
        cout << "\n1. Name\n2. Age\n3. Gender\n4. Contact\n0. Done\nWhat to update: ";
        if (!(cin >> choice))
        {
            cin.clear();
            choice = -1;
        }
        cin.ignore(1000, '\n');

        if (choice == 1)
        {
            cout << "Enter New Name: ";
            getline(cin, target->name);
            target->name = formatName(target->name);
        }
        else if (choice == 2)
        {
            int newAge = 0;
            cout << "Enter New Age: ";
            cin >> newAge;
            cin.clear();
            cin.ignore(1000, '\n');
            if (newAge <= 0 || newAge > 120)
            {
                cout << "Invalid Age!" << endl;
            }
            else
            {
                target->age = newAge;
            }
        }
        else if (choice == 3)
        {
            target->gender = getGender();
        }
        else if (choice == 4)
        {
            string newContact;
            cout << "Enter New Contact: ";
            getline(cin, newContact);
            if (newContact.size() != 11 || newContact.find_first_not_of("0123456789") != string::npos)
            {
                cout << "Invalid Contact!" << endl;
            }
            else
            {
                target->contact = newContact;
            }
        }
        else if (choice != 0)
        {
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    cout << "Patient record updated." << endl;
}

void PatientList::deletePatient(int id)
{
    if (patients.empty())
    {
        cout << "List is empty." << endl;
        return;
    }

    int index = binarySearch(id);
    if (index == -1)
    {
        cout << "Patient not found!" << endl;
        return;
    }

    patients.erase(patients.begin() + index);
    cout << "Patient deleted." << endl;
}

void PatientList::sortById()
{
    if (patients.size() < 2)
    {
        cout << "Nothing to sort." << endl;
        return;
    }

    bubbleSort();
    cout << "Records sorted by ID." << endl;
}

void PatientList::displayAll()
{
    if (patients.empty())
    {
        cout << "No patients registered yet." << endl;
        return;
    }

    cout << "\n--- Patient Records ---" << endl;
    for (size_t i = 0; i < patients.size(); i++)
    {
        cout << "ID: " << formatId(patients[i].id)
             << " | Name: " << patients[i].name
             << " | Age: " << patients[i].age
             << " | Gender: " << patients[i].gender
             << " | Contact: " << patients[i].contact << endl;
    }
    cout << "-----------------------" << endl;
}

void PatientList::saveToFile()
{
    ofstream file("patients.txt");
    if (!file)
        return;

    for (size_t i = 0; i < patients.size(); i++)
    {
        file << patients[i].id << ","
             << patients[i].name << ","
             << patients[i].age << ","
             << patients[i].gender << ","
             << patients[i].contact << endl;
    }
    file.close();
}

void PatientList::loadFromFile()
{
    ifstream file("patients.txt");
    if (!file)
        return;

    string idStr, name, ageStr, gender, contact;
    while (getline(file, idStr, ','))
    {
        if (idStr.empty())
            continue;
        getline(file, name, ',');
        getline(file, ageStr, ',');
        getline(file, gender, ',');
        getline(file, contact);

        int id = stoi(idStr);
        int age = stoi(ageStr);

        patients.push_back(Patient(id, name, age, gender, contact));
    }
    file.close();
    bubbleSort();
}
