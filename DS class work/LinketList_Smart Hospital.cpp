
#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

struct Patient
{
    int id;
    string name;
    int age;
    string disease;
    Patient* next;
    Patient* hashNext;
};

Patient* head = nullptr;
Patient* hashTable[SIZE] = {nullptr};

// Hash Function
int hashFunction(int id)
{
    return id % SIZE;
}

// Register Patient
void registerPatient()
{
    Patient* p = new Patient;

    cout << "Enter Patient ID: ";
    if (!(cin >> p->id) || p->id < 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid ID!\n";
        delete p;
        return;
    }

    int index = hashFunction(p->id);
    Patient* temp = hashTable[index];

    while (temp != nullptr)
    {
        if (temp->id == p->id)
        {
            cout << "Patient ID already exists!\n";
            delete p;
            return;
        }
        temp = temp->hashNext;
    }

    cout << "Enter Name: ";
    getline(cin >> ws, p->name);

    cout << "Enter Age: ";
    if (!(cin >> p->age) || p->age < 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid age!\n";
        delete p;
        return;
    }

    cout << "Enter Disease: ";
    getline(cin >> ws, p->disease);

    // Insert into Linked List
    p->next = head;
    head = p;

    // Insert into Hash Table using Chaining
    p->hashNext = hashTable[index];
    hashTable[index] = p;

    cout << "Patient registered successfully!\n";
}

// Search Patient
void searchPatient()
{
    int id;

    cout << "Enter Patient ID to search: ";
    if (!(cin >> id) || id < 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid ID!\n";
        return;
    }

    int index = hashFunction(id);
    Patient* temp = hashTable[index];

    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            cout << "\nPatient Found!\n";
            cout << "ID: " << temp->id << endl;
            cout << "Name: " << temp->name << endl;
            cout << "Age: " << temp->age << endl;
            cout << "Disease: " << temp->disease << endl;
            return;
        }

        temp = temp->hashNext;
    }

    cout << "Patient not found!\n";
}

// Display All Patients
void displayPatients()
{
    Patient* temp = head;

    if (temp == nullptr)
    {
        cout << "No patient records available.\n";
        return;
    }

    while (temp != nullptr)
    {
        cout << "\nPatient ID: " << temp->id << endl;
        cout << "Name: " << temp->name << endl;
        cout << "Age: " << temp->age << endl;
        cout << "Disease: " << temp->disease << endl;

        temp = temp->next;
    }
}

// Main Function
int main()
{
    int choice;

    do
    {
        cout << "\n--- Hospital Management System ---\n";
        cout << "1. Register Patient\n";
        cout << "2. Search Patient\n";
        cout << "3. Display All Patients\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input. Exiting program.\n";
            break;
        }

        switch (choice)
        {
            case 1:
                registerPatient();
                break;

            case 2:
                searchPatient();
                break;

            case 3:
                displayPatients();
                break;

            case 4:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    // Free allocated memory
    Patient* temp = head;

    while (temp != nullptr)
    {
        Patient* toDelete = temp;
        temp = temp->next;
        delete toDelete;
    }

    return 0;
}
