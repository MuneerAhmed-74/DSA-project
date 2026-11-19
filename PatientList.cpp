#include "PatientList.h"
#include <iostream>
#include <fstream>
#include <utility>

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

void PatientList::addPatient(int id, string name, int age, string gender, string contact) {
    if (id <= 0 || age <= 0) {
        cout << "Invalid ID or Age!" << endl;
        return;
    }
    if (patientExists(id)) {
        cout << "Patient ID " << id << " already exists!" << endl;
        return;
    }

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
    saveToFile();
    cout << "Patient registered successfully." << endl;
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

    string newName, newGender, newContact;
    int newAge;

    cin.ignore();
    cout << "Enter New Name: ";
    getline(cin, newName);
    cout << "Enter New Age: ";
    cin >> newAge;
    if (newAge <= 0) {
        cout << "Invalid Age! Update cancelled." << endl;
        return;
    }
    cin.ignore();
    cout << "Enter New Gender: ";
    getline(cin, newGender);
    cout << "Enter New Contact: ";
    getline(cin, newContact);

    target->name = newName;
    target->age = newAge;
    target->gender = newGender;
    target->contact = newContact;

    saveToFile();
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
        saveToFile();
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
    saveToFile();
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
        cout << "ID: " << temp->id
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