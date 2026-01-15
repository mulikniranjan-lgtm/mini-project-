#include <iostream>
#include <fstream>
using namespace std;

class Student {
public:
    int roll;
    char name[30];
    int m1, m2, m3;
    int total;
    float percentage;
    char grade;

    void calculate() {
        total = m1 + m2 + m3;
        percentage = total / 3.0;

        if (percentage >= 75)
            grade = 'A';
        else if (percentage >= 60)
            grade = 'B';
        else if (percentage >= 50)
            grade = 'C';
        else
            grade = 'F';
    }

    void input() {
        cout << "Enter Roll No: ";
        cin >> roll;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter marks of 3 subjects: ";
        cin >> m1 >> m2 >> m3;
        calculate();
    }

    void display() {
        cout << roll << "\t" << name << "\t"
             << total << "\t" << percentage << "%\t"
             << grade << endl;
    }
};

void addStudent() {
    Student s;
    ofstream file("student.dat", ios::app | ios::binary);
    s.input();
    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "✅ Student record added successfully!\n";
}

void displayAll() {
    Student s;
    ifstream file("student.dat", ios::binary);

    cout << "\nRoll\tName\tTotal\tPercent\tGrade\n";
    cout << "----------------------------------------\n";

    while (file.read((char*)&s, sizeof(s))) {
        s.display();
    }
    file.close();
}

void searchStudent() {
    int r;
    bool found = false;
    Student s;
    ifstream file("student.dat", ios::binary);

    cout << "Enter Roll No to search: ";
    cin >> r;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.roll == r) {
            cout << "\nRecord Found:\n";
            s.display();
            found = true;
            break;
        }
    }
    file.close();

    if (!found)
        cout << "❌ Student record not found.\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== STUDENT RESULT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Results\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "❌ Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
