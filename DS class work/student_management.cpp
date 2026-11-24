#include <iostream>
#include <string>
using namespace std;

#define SIZE 10

struct Student {
    int roll;
    string name, department;
    string courses[10];
    int count;
    Student *next;
    Student *hashNext;
};

class StudentSystem {
    Student *head;
    Student *hashTable[SIZE];

    int hashFunction(int roll) {
        return roll % SIZE;
    }

    Student* search(int roll) {
        int index = hashFunction(roll);
        Student *temp = hashTable[index];

        while (temp != NULL) {
            if (temp->roll == roll)
                return temp;

            temp = temp->hashNext;
        }
        return NULL;
    }

public:
    StudentSystem() {
        head = NULL;

        for (int i = 0; i < SIZE; i++)
            hashTable[i] = NULL;
    }

    // Register Student
    void registerStudent() {
        Student *s = new Student;

        cout << "Enter Roll Number: ";
        cin >> s->roll;

        if (s->roll <= 0 || search(s->roll) != NULL) {
            cout << "Invalid or Duplicate Roll Number!\n";
            delete s;
            return;
        }

        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, s->name);

        cout << "Enter Department: ";
        getline(cin, s->department);

        s->count = 0;

        // Insert into Linked List
        s->next = head;
        head = s;

        // Insert into Hash Table using Chaining
        int index = hashFunction(s->roll);
        s->hashNext = hashTable[index];
        hashTable[index] = s;

        cout << "Student Registered Successfully!\n";
    }

    // Update Student
    void updateStudent() {
        int roll;

        cout << "Enter Roll Number: ";
        cin >> roll;

        Student *s = search(roll);

        if (s == NULL) {
            cout << "Student Not Found!\n";
            return;
        }

        cout << "Enter New Name: ";
        cin.ignore();
        getline(cin, s->name);

        cout << "Enter New Department: ";
        getline(cin, s->department);

        cout << "Student Updated Successfully!\n";
    }

    // Enroll Course
    void enrollCourse() {
        int roll;
        string course;

        cout << "Enter Roll Number: ";
        cin >> roll;

        Student *s = search(roll);

        if (s == NULL) {
            cout << "Student Not Found!\n";
            return;
        }

        if (s->count == 10) {
            cout << "Course Limit Reached!\n";
            return;
        }

        cout << "Enter Course Name: ";
        cin.ignore();
        getline(cin, course);

        for (int i = 0; i < s->count; i++) {
            if (s->courses[i] == course) {
                cout << "Already Enrolled!\n";
                return;
            }
        }

        s->courses[s->count] = course;
        s->count++;

        cout << "Course Enrolled Successfully!\n";
    }

    // Withdraw Course
    void withdrawCourse() {
        int roll;
        string course;

        cout << "Enter Roll Number: ";
        cin >> roll;

        Student *s = search(roll);

        if (s == NULL) {
            cout << "Student Not Found!\n";
            return;
        }

        cout << "Enter Course Name: ";
        cin.ignore();
        getline(cin, course);

        for (int i = 0; i < s->count; i++) {
            if (s->courses[i] == course) {

                for (int j = i; j < s->count - 1; j++) {
                    s->courses[j] = s->courses[j + 1];
                }

                s->count--;

                cout << "Course Withdrawn Successfully!\n";
                return;
            }
        }

        cout << "Course Not Found!\n";
    }

    // Remove Student
    void removeStudent() {
        int roll;

        cout << "Enter Roll Number: ";
        cin >> roll;

        Student *s = search(roll);

        if (s == NULL) {
            cout << "Student Not Found!\n";
            return;
        }

        // Remove from Linked List
        if (head == s) {
            head = s->next;
        }
        else {
            Student *temp = head;

            while (temp->next != s)
                temp = temp->next;

            temp->next = s->next;
        }

        // Remove from Hash Table
        int index = hashFunction(roll);
        Student *temp = hashTable[index];
        Student *prev = NULL;

        while (temp != s) {
            prev = temp;
            temp = temp->hashNext;
        }

        if (prev == NULL)
            hashTable[index] = temp->hashNext;
        else
            prev->hashNext = temp->hashNext;

        delete s;

        cout << "Student Removed Successfully!\n";
    }

    // Display Students
    void displayStudents() {
        Student *temp = head;

        if (head == NULL) {
            cout << "No Student Records!\n";
            return;
        }

        while (temp != NULL) {
            cout << "\nRoll Number: " << temp->roll;
            cout << "\nName: " << temp->name;
            cout << "\nDepartment: " << temp->department;

            cout << "\nCourses: ";

            if (temp->count == 0)
                cout << "No Courses";

            for (int i = 0; i < temp->count; i++)
                cout << temp->courses[i] << " ";

            cout << "\n------------------------\n";

            temp = temp->next;
        }
    }

    // Search Student
    void searchStudent() {
        int roll;

        cout << "Enter Roll Number: ";
        cin >> roll;

        Student *s = search(roll);

        if (s == NULL) {
            cout << "Student Not Found!\n";
        }
        else {
            cout << "\nStudent Found!";
            cout << "\nRoll Number: " << s->roll;
            cout << "\nName: " << s->name;
            cout << "\nDepartment: " << s->department;

            cout << "\nCourses: ";

            for (int i = 0; i < s->count; i++)
                cout << s->courses[i] << " ";

            cout << endl;
        }
    }

    ~StudentSystem() {
        Student *temp = head;

        while (temp != NULL) {
            Student *next = temp->next;
            delete temp;
            temp = next;
        }
    }
};

int main() {
    StudentSystem system;
    int choice;

    do {
        cout << "\n===== UNIVERSITY STUDENT SYSTEM =====\n";
        cout << "1. Register Student\n";
        cout << "2. Update Student\n";
        cout << "3. Enroll Course\n";
        cout << "4. Withdraw Course\n";
        cout << "5. Remove Student\n";
        cout << "6. Display Students\n";
        cout << "7. Search Student\n";
        cout << "8. Exit\n";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: system.registerStudent(); break;
            case 2: system.updateStudent(); break;
            case 3: system.enrollCourse(); break;
            case 4: system.withdrawCourse(); break;
            case 5: system.removeStudent(); break;
            case 6: system.displayStudents(); break;
            case 7: system.searchStudent(); break;
            case 8: cout << "Exiting System...\n"; break;
            default: cout << "Invalid Choice!\n";
        }

    } while (choice != 8);

    return 0;
}
