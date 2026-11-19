#include "PatientList.h"
#include <iostream>
#include <string>
using namespace std;

void showMenu() {
    cout << "\n1. Register Patient" << endl;
    cout << "2. Update Patient" << endl;
    cout << "3. Delete Patient" << endl;
    cout << "4. Search Patient by ID" << endl;
    cout << "5. Sort Patients by ID" << endl;
    cout << "6. Display All Patients" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter choice: ";
}

int getChoice() {
    int choice;
    if (!(cin >> choice)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input!" << endl;
        return -1;
    }
    return choice;
}

void registerPatient(PatientList& list) {
    int id, age;
    string name, gender, contact;

    cout << "Enter ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Age: ";
    cin >> age;
    cin.ignore();
    cout << "Enter Gender: ";
    getline(cin, gender);
    cout << "Enter Contact: ";
    getline(cin, contact);

    list.addPatient(id, name, age, gender, contact);
}

void updatePatient(PatientList& list) {
    int id;
    cout << "Enter ID to update: ";
    cin >> id;
    list.updatePatient(id);
}

void deletePatient(PatientList& list) {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;
    list.deletePatient(id);
}

void searchPatient(PatientList& list) {
    int id;
    cout << "Enter ID to search: ";
    cin >> id;

    Patient* p = list.searchById(id);
    if (p != NULL) {
        cout << "Found -> ID: " << p->id
             << " | Name: " << p->name
             << " | Age: " << p->age
             << " | Gender: " << p->gender
             << " | Contact: " << p->contact << endl;
    } else {
        cout << "Patient not found!" << endl;
    }
}

void sortPatients(PatientList& list) {
    list.sortById();
    list.displayAll();
}

void displayPatients(PatientList& list) {
    list.displayAll();
}

void exitProgram() {
    cout << "Exiting..." << endl;
}

void invalidChoice() {
    cout << "Invalid choice!" << endl;
}

int main() {
    PatientList list;
    int choice;

    do {
        showMenu();
        choice = getChoice();

        switch (choice) {
            case 1:
                registerPatient(list);
                break;
            case 2:
                updatePatient(list);
                break;
            case 3:
                deletePatient(list);
                break;
            case 4:
                searchPatient(list);
                break;
            case 5:
                sortPatients(list);
                break;
            case 6:
                displayPatients(list);
                break;
            case 0:
                exitProgram();
                break;
            case -1:
                break;
            default:
                invalidChoice();
                break;
        }
    } while (choice != 0);

    return 0;
}