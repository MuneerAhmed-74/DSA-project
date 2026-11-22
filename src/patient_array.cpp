#include "patient_array.h"
#include <algorithm>
#include <fstream>

PatientArray::PatientArray()
{
    loadFromFile();
}

PatientArray::~PatientArray()
{
    saveToFile();
}

void PatientArray::bubbleSort()
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

int PatientArray::binarySearch(int id)
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

int PatientArray::getNextId()
{
    return patients.empty() ? 1 : patients.back().id + 1;
}

bool PatientArray::addPatient(const std::string &name, int age,
                              const std::string &gender, const std::string &contact,
                              const std::string &email)
{
    if (name.empty() || age <= 0 || age > 120 || contact.size() != 11)
        return false;

    if (contact.find_first_not_of("0123456789") != std::string::npos)
        return false;

    if (email.find('@') == std::string::npos)
        return false;

    int id = getNextId();
    patients.push_back(Patient(id, name, age, gender, contact, email));
    bubbleSort();
    saveToFile();
    return true;
}

Patient *PatientArray::searchById(int id)
{
    bubbleSort();
    int index = binarySearch(id);
    return index == -1 ? nullptr : &patients[index];
}

bool PatientArray::updateEmail(int id, const std::string &email)
{
    Patient *patient = searchById(id);
    if (!patient || email.find('@') == std::string::npos)
        return false;

    patient->email = email;
    saveToFile();
    return true;
}

bool PatientArray::updateName(int id, const std::string &name)
{
    Patient *patient = searchById(id);
    if (!patient || name.empty())
        return false;

    patient->name = name;
    saveToFile();
    return true;
}

bool PatientArray::updateAge(int id, int age)
{
    Patient *patient = searchById(id);
    if (!patient || age <= 0 || age > 120)
        return false;

    patient->age = age;
    saveToFile();
    return true;
}

bool PatientArray::updateGender(int id, const std::string &gender)
{
    Patient *patient = searchById(id);
    if (!patient || gender.empty())
        return false;

    patient->gender = gender;
    saveToFile();
    return true;
}

bool PatientArray::updateContact(int id, const std::string &contact)
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

bool PatientArray::deletePatient(int id)
{
    bubbleSort();
    int index = binarySearch(id);
    if (index == -1)
        return false;

    patients.erase(patients.begin() + index);
    saveToFile();
    return true;
}

void PatientArray::sortById()
{
    bubbleSort();
    saveToFile();
}

const std::vector<Patient> &PatientArray::getPatients() const
{
    return patients;
}

void PatientArray::saveToFile()
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
             << patient.contact << ','
             << patient.email << '\n';
    }
}

void PatientArray::loadFromFile()
{
    std::ifstream file("data/patients.txt");
    if (!file)
        return;

    std::string idText, name, ageText, gender, contact, email;
    while (std::getline(file, idText, ','))
    {
        if (idText.empty())
            continue;

        std::getline(file, name, ',');
        std::getline(file, ageText, ',');
        std::getline(file, gender, ',');
        std::getline(file, contact, ',');
        std::getline(file, email);

        try
        {
            int id = std::stoi(idText);
            int age = std::stoi(ageText);
            patients.push_back(Patient(id, name, age, gender, contact, email));
        }
        catch (const std::exception &)
        {
            continue;
        }
    }
    bubbleSort();
}
