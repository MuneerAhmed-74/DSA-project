#include "PatientList.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <cctype>

PatientList::PatientList() {
    head = NULL;
    loadFromFile();
}

PatientList::~PatientList() {
    saveToFile();
    Patient* curr = head;
    while (curr != NULL) {
        Patient* temp = curr;
        curr = curr->next;
        delete temp;
    }
}

bool PatientList::patientExists(int id) {
    Patient* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

int PatientList::getNextId() {
    int maxId = 0;
    Patient* temp = head;
    while (temp != NULL) {
        if (temp->id > maxId) {
            maxId = temp->id;
        }
        temp = temp->next;
    }
    return maxId + 1;
}

string PatientList::getGender() {
    cout << "Select Gender:\n1. Male\n2. Female\n3. Other" << endl;
    int c;
    while (true) {
        cout << "Choice: ";
        if (cin >> c && c >= 1 && c <= 3) break;
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice!" << endl;
    }
    cin.ignore(1000, '\n');
    if (c == 1) return "Male";
    if (c == 2) return "Female";
    return "Other";
}

string PatientList::formatName(string name) {
    for (size_t i = 0; i < name.size(); i++) {
        if (i == 0 || name[i - 1] == ' ') {
            name[i] = toupper(name[i]);
        } else {
            name[i] = tolower(name[i]);
        }
    }
    return name;
}

void PatientList::addPatient(string name, int age, string gender, string contact) {
    if (age <= 0) {
        cout << "Invalid Age!" << endl;
        return;
    }
    int id = getNextId();

    Patient* newNode = new Patient(id, name, age, gender, contact);
    if (head == NULL) {
        head = newNode;
    } else {
        Patient* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    cout << "Patient registered successfully. ID: " << formatId(id) << endl;
}

Patient* PatientList::searchById(int id) {
    Patient* temp = head;
    while (temp != NULL) {
        if (temp->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void PatientList::updatePatient(int id) {
    Patient* target = searchById(id);
    if (target == NULL) {
        cout << "Patient not found!" << endl;
        return;
    }

    int choice;
    do {
        cout << "\n1. Name\n2. Age\n3. Gender\n4. Contact\n0. Done\nWhat to update: ";
        if (!(cin >> choice)) {
            cin.clear();
            choice = -1;
        }
        cin.ignore(1000, '\n');

        if (choice == 1) {
            cout << "Enter New Name: ";
            getline(cin, target->name);
            target->name = formatName(target->name);
        } else if (choice == 2) {
            int newAge = 0;
            cout << "Enter New Age: ";
            cin >> newAge;
            cin.clear();
            cin.ignore(1000, '\n');
            if (newAge <= 0 || newAge > 120) {
                cout << "Invalid Age!" << endl;
            } else {
                target->age = newAge;
            }
        } else if (choice == 3) {
            target->gender = getGender();
        } else if (choice == 4) {
            string newContact;
            cout << "Enter New Contact: ";
            getline(cin, newContact);
            if (newContact.size() != 11 || newContact.find_first_not_of("0123456789") != string::npos) {
                cout << "Invalid Contact!" << endl;
            } else {
                target->contact = newContact;
            }
        } else if (choice != 0) {
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 0);

    cout << "Patient record updated." << endl;
}

void PatientList::deletePatient(int id) {
    if (head == NULL) {
        cout << "List is empty." << endl;
        return;
    }

    if (head->id == id) {
        Patient* temp = head;
        head = head->next;
        delete temp;
        cout << "Patient deleted." << endl;
        return;
    }

    Patient* prev = head;
    Patient* curr = head->next;
    while (curr != NULL && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) {
        cout << "Patient not found!" << endl;
        return;
    }

    prev->next = curr->next;
    delete curr;
    cout << "Patient deleted." << endl;
}

void PatientList::sortById() {
    if (head == NULL || head->next == NULL) {
        cout << "Nothing to sort." << endl;
        return;
    }

    bool swapped;
    do {
        swapped = false;
        Patient* curr = head;
        while (curr->next != NULL) {
            if (curr->id > curr->next->id) {
                swap(curr->id, curr->next->id);
                swap(curr->name, curr->next->name);
                swap(curr->age, curr->next->age);
                swap(curr->gender, curr->next->gender);
                swap(curr->contact, curr->next->contact);
                swapped = true;
            }
            curr = curr->next;
        }
    } while (swapped);

    cout << "Records sorted by ID." << endl;
}

void PatientList::displayAll() {
    if (head == NULL) {
        cout << "No patients registered yet." << endl;
        return;
    }

    cout << "\n--- Patient Records ---" << endl;
    Patient* temp = head;
    while (temp != NULL) {
        cout << "ID: " << formatId(temp->id)
             << " | Name: " << temp->name
             << " | Age: " << temp->age
             << " | Gender: " << temp->gender
             << " | Contact: " << temp->contact << endl;
        temp = temp->next;
    }
    cout << "-----------------------" << endl;
}

void PatientList::saveToFile() {
    ofstream file("patients.txt");
    if (!file) return;

    Patient* temp = head;
    while (temp != NULL) {
        file << temp->id << ","
             << temp->name << ","
             << temp->age << ","
             << temp->gender << ","
             << temp->contact << endl;
        temp = temp->next;
    }
    file.close();
}

void PatientList::loadFromFile() {
    ifstream file("patients.txt");
    if (!file) return;

    string idStr, name, ageStr, gender, contact;
    while (getline(file, idStr, ',')) {
        if (idStr.empty()) continue;
        getline(file, name, ',');
        getline(file, ageStr, ',');
        getline(file, gender, ',');
        getline(file, contact);

        int id = stoi(idStr);
        int age = stoi(ageStr);

        Patient* newNode = new Patient(id, name, age, gender, contact);
        if (head == NULL) {
            head = newNode;
        } else {
            Patient* temp = head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    file.close();
}
