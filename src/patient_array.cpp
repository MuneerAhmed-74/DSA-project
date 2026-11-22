#include "patient_array.h"
#include <algorithm>
#include <fstream>

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
    for (size_t i = 0; i < patients.size(); ++i)
    {
        for (size_t j = 0; j + 1 < patients.size() - i; ++j)
        {
            if (patients[j].id > patients[j + 1].id)
            {
                std::swap(patients[j], patients[j + 1]);
            }
        }
    }
}

int PatientList::binarySearch(int id)
{
    int low = 0;
    int high = static_cast<int>(patients.size()) - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (patients[mid].id == id)
            return mid;
        if (patients[mid].id < id)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int PatientList::getNextId()
{
    return patients.empty() ? 1 : patients.back().id + 1;
}

bool PatientList::addPatient(const std::string &name, int age,
                             const std::string &gender, const std::string &contact)
{
    if (name.empty() || age <= 0 || age > 120 || contact.size() != 11)
        return false;

    if (contact.find_first_not_of("0123456789") != std::string::npos)
        return false;

    int id = getNextId();
    patients.push_back(Patient(id, name, age, gender, contact));
    bubbleSort();
    saveToFile();
    return true;
}

Patient *PatientList::searchById(int id)
{
    bubbleSort();
    int index = binarySearch(id);
    return index == -1 ? nullptr : &patients[index];
}

bool PatientList::updateId(int oldId, int newId)
{
    if (newId <= 0 || oldId == newId)
        return false;

    for (const Patient &patient : patients)
    {
        if (patient.id == newId)
            return false;
    }

    Patient *patient = searchById(oldId);
    if (!patient)
        return false;

    patient->id = newId;
    bubbleSort();
    saveToFile();
    return true;
}

bool PatientList::updateName(int id, const std::string &name)
{
    Patient *patient = searchById(id);
    if (!patient || name.empty())
        return false;

    patient->name = name;
    saveToFile();
    return true;
}

bool PatientList::updateAge(int id, int age)
{
    Patient *patient = searchById(id);
    if (!patient || age <= 0 || age > 120)
        return false;

    patient->age = age;
    saveToFile();
    return true;
}

bool PatientList::updateGender(int id, const std::string &gender)
{
    Patient *patient = searchById(id);
    if (!patient || gender.empty())
        return false;

    patient->gender = gender;
    saveToFile();
    return true;
}

bool PatientList::updateContact(int id, const std::string &contact)
{
    Patient *patient = searchById(id);
    if (!patient || contact.size() != 11)
        return false;

    if (contact.find_first_not_of("0123456789") != std::string::npos)
        return false;

    patient->contact = contact;
    saveToFile();
    return true;
}

bool PatientList::deletePatient(int id)
{
    bubbleSort();
    int index = binarySearch(id);
    if (index == -1)
        return false;

    patients.erase(patients.begin() + index);
    saveToFile();
    return true;
}

void PatientList::sortById()
{
    bubbleSort();
    saveToFile();
}

const std::vector<Patient> &PatientList::getPatients() const
{
    return patients;
}

void PatientList::saveToFile()
{
    std::ofstream file("data/patients.txt");
    if (!file)
        return;

    for (const Patient &patient : patients)
    {
        file << patient.id << ','
             << patient.name << ','
             << patient.age << ','
             << patient.gender << ','
             << patient.contact << '\n';
    }
}

void PatientList::loadFromFile()
{
    std::ifstream file("data/patients.txt");
    if (!file)
        return;

    std::string idText, name, ageText, gender, contact;
    while (std::getline(file, idText, ','))
    {
        if (idText.empty())
            continue;

        std::getline(file, name, ',');
        std::getline(file, ageText, ',');
        std::getline(file, gender, ',');
        std::getline(file, contact);

        try
        {
            int id = std::stoi(idText);
            int age = std::stoi(ageText);
            patients.push_back(Patient(id, name, age, gender, contact));
        }
        catch (const std::exception &)
        {
            continue;
        }
    }
    bubbleSort();
}
