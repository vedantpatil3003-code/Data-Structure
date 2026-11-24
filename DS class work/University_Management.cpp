#include <iostream>
#include <string>
using namespace std;

const int SIZE = 10;

struct Student {
    int roll;
    string name;
    string course;
    Student* next;
};

Student* table[SIZE] = {NULL};

int hashFunction(int roll) {
    return roll % SIZE;
}

void registerStudent() {
    int roll;
    string name, course;

    cout << "Enter Roll Number: ";
    cin >> roll;

    int index = hashFunction(roll);
    Student* temp = table[index];

    while (temp != NULL) {
        if (temp->roll == roll) {
            cout << "Roll Number already exists!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Enter Student Name: ";
    cin >> name;
    cout << "Enter Course: ";
    cin >> course;

    Student* newStudent = new Student;
    newStudent->roll = roll;
    newStudent->name = name;
    newStudent->course = course;

    newStudent->next = table[index];
    table[index] = newStudent;

    cout << "Student registered successfully!\n";
}

void updateStudent() {
    int roll;
    cout << "Enter Roll Number: ";
    cin >> roll;

    int index = hashFunction(roll);
    Student* temp = table[index];

    while (temp != NULL) {
        if (temp->roll == roll) {
            cout << "Enter New Name: ";
            cin >> temp->name;
            cout << "Enter New Course: ";
            cin >> temp->course;

            cout << "Student updated!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Student not found!\n";
}

void enrollCourse() {
    int roll;
    string course;

    cout << "Enter Roll Number: ";
    cin >> roll;

    int index = hashFunction(roll);
    Student* temp = table[index];

    while (temp != NULL) {
        if (temp->roll == roll) {
            cout << "Enter Course Name: ";
            cin >> course;

            temp->course = course;

            cout << "Course enrolled successfully!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Student not found!\n";
}

void withdrawCourse() {
    int roll;
    cout << "Enter Roll Number: ";
    cin >> roll;

    int index = hashFunction(roll);
    Student* temp = table[index];

    while (temp != NULL) {
        if (temp->roll == roll) {
            temp->course = "None";
            cout << "Course withdrawn successfully!\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Student not found!\n";
}

void removeStudent() {
    int roll;
    cout << "Enter Roll Number: ";
    cin >> roll;

    int index = hashFunction(roll);
    Student* temp = table[index];
    Student* prev = NULL;

    while (temp != NULL) {
        if (temp->roll == roll) {
            if (prev == NULL)
                table[index] = temp->next;
            else
                prev->next = temp->next;

            delete temp;
            cout << "Student removed!\n";
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    cout << "Student not found!\n";
}

void displayStudents() {
    cout << "\nStudent Records:\n";

    for (int i = 0; i < SIZE; i++) {
        Student* temp = table[i];

        while (temp != NULL) {
            cout << "Roll Number: " << temp->roll
                 << " Name: " << temp->name
                 << " Course: " << temp->course << endl;

            temp = temp->next;
        }
    }
}

void searchStudent() {
    int roll;
    cout << "Enter Roll Number: ";
    cin >> roll;

    int index = hashFunction(roll);
    Student* temp = table[index];

    while (temp != NULL) {
        if (temp->roll == roll) {
            cout << "Student Found!\n";
            cout << "Name: " << temp->name << endl;
            cout << "Course: " << temp->course << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "Student not found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n--- University Student System ---\n";
        cout << "1. Register Student\n";
        cout << "2. Update Student\n";
        cout << "3. Enroll Course\n";
        cout << "4. Withdraw Course\n";
        cout << "5. Remove Student\n";
        cout << "6. Display Students\n";
        cout << "7. Search Student\n";
        cout << "8. Exit\n";

        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerStudent(); break;
            case 2: updateStudent(); break;
            case 3: enrollCourse(); break;
            case 4: withdrawCourse(); break;
            case 5: removeStudent(); break;
            case 6: displayStudents(); break;
            case 7: searchStudent(); break;
            case 8: cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice!\n";
        }

    } while (choice != 8);

    return 0;
}
