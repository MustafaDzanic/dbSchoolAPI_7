#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <limits>

#include "./dto/dto.h"
#include "globals.h"
#include "globals.cpp"

#include "./api/studentApi.h"
#include "./api/teacherApi.h"
#include "./api/subjectApi.h"
#include "./api/departmentApi.h"

using namespace std;

void printMenu (){
    cout << "-------------------------" << endl;
    cout << "1. INSERT data" << endl;
    cout << "2. SELECT data" << endl;
    cout << "3. UPDATE data" << endl;
    cout << "4. DELETE data" << endl;
    cout << "5. QUIT" << endl;
}
void printTableMenu() {
    cout << "Choose table:" << endl;
    cout << "1. Students" << endl;
    cout << "2. Teachers" << endl;
    cout << "3. Subjects" << endl;
    cout << "4. Departments" << endl;
}

int main()
{
    int choice;
    StudentApi studentApi;
    TeacherApi teacherApi;
    SubjectApi subjectApi;
    DepartmentApi departmentApi;

    cout << "Student API interface" << endl;
    printMenu();

    while(1){
        cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if(choice < 1 || choice > 5){
            cout << "Bad input, try again." << endl;
            continue;
        }
        else if(EXIT == choice) {
            break;
        }
        else if(INSERT == choice)
        {
            do {
                printTableMenu();
                cin >> choice;
            } while(choice < 1 || choice > NUM_OF_TABLES);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(STUDENTS == choice) {
                string firstName, lastName, birthdate, email, jmbg, department;
                string tmpStr;
                char gender;

                cout << "First Name: ";
                getline(cin, firstName);
                cout << "Last Name: ";
                getline(cin, lastName);
                cout << "Birth Date(YYYY-MM-DD): ";
                getline(cin, birthdate);
                cout << "Email: ";
                getline(cin, email);
                cout << "JMBG: ";
                getline(cin, jmbg);
                cout << "Gender(M/F): ";
                getline(cin, tmpStr);
                gender = tmpStr[0];
                cout << "Department name: ";
                getline(cin, department);

                if(studentApi.save(firstName, lastName, birthdate, email, gender, jmbg, department)){
                    cout << "Insert successful!" << endl;
                } else {
                    cout << "Insert failed.\nError: " << studentApi.error() << endl;
                }
            } else if(TEACHERS == choice) {
                string firstName, lastName, birthdate, email, jmbg, title, department;
                string tmpStr;
                char gender;

                cout << "First Name: ";
                getline(cin, firstName);
                cout << "Last Name: ";
                getline(cin, lastName);
                cout << "Birth Date(YYYY-MM-DD): ";
                getline(cin, birthdate);
                cout << "Email: ";
                getline(cin, email);
                cout << "JMBG: ";
                getline(cin, jmbg);
                cout << "Title: ";
                getline(cin, title);
                cout << "Gender(M/F): ";
                getline(cin, tmpStr);
                gender = tmpStr[0];
                cout << "Department name: ";
                getline(cin, department);

                if(teacherApi.save(firstName, lastName, birthdate, email, gender, jmbg, title, department)){
                    cout << "Insert successful!" << endl;
                } else {
                    cout << "Insert failed.\nError: " << teacherApi.error() << endl;
                }
            } else if(SUBJECTS == choice) {
                string name, abbreviation, teacherId, tmpStr;
                int ects;

                cout << "Name: ";
                getline(cin, name);
                cout << "Ects: ";
                getline(cin, tmpStr);
                ects = atoi(tmpStr.c_str());
                cout << "Abbreaviation: ";
                getline(cin, abbreviation);
                cout << "Teacher Id: ";
                getline(cin, teacherId);

                if(subjectApi.save(name, ects, abbreviation, teacherId)){
                    cout << "Insert successful!" << endl;
                } else {
                    cout << "Insert failed.\nError: " << subjectApi.error() << endl;
                }
            } else if(DEPARTMENTS == choice) {
                string name;

                cout << "Name: ";
                getline(cin, name);

                if(departmentApi.save(name)){
                    cout << "Insert successful!" << endl;
                } else {
                    cout << "Insert failed.\nError: " << departmentApi.error() << endl;
                }
            }
        }
        else if(SELECT == choice)
        {
            do {
                printTableMenu();
                cin >> choice;
            } while(choice < 1 || choice > NUM_OF_TABLES);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(STUDENTS == choice) {
                vector<Student> students;
                cout << "Enter ID to select (0 for all entries): ";
                cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                students = studentApi.selectById(choice);
                if(students.size() == 0){
                    cout << "No entries found." << endl;
                }else{
                    cout << "Selected " << students.size() << " entry/ies: " << endl;
                    cout << studentApi.getHeader() << endl;
                    for(vector<Student>::iterator it = students.begin(); it != students.end(); ++it) {
                        Student tempStud = *it;
                        cout << studentApi.parseOutput(tempStud) << endl;
                    }
                }
            } else if(TEACHERS == choice) {
                vector<Teacher> teachers;
                cout << "Enter ID to select (0 for all entries): ";
                cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                teachers = teacherApi.selectById(choice);
                if(teachers.size() == 0){
                    cout << "No entries found." << endl;
                }else{
                    cout << "Selected " << teachers.size() << " entry/ies: " << endl;
                    cout << teacherApi.getHeader() << endl;
                    for(vector<Teacher>::iterator it = teachers.begin(); it != teachers.end(); ++it) {
                        Teacher tempStud = *it;
                        cout << teacherApi.parseOutput(tempStud) << endl;
                    }
                }
            } else if(SUBJECTS == choice) {
                vector<Subject> subjects;
                cout << "Enter ID to select (0 for all entries): ";
                cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                subjects = subjectApi.selectById(choice);
                if(subjects.size() == 0){
                    cout << "No entries found." << endl;
                }else{
                    cout << "Selected " << subjects.size() << " entry/ies: " << endl;
                    cout << subjectApi.getHeader() << endl;
                    for(vector<Subject>::iterator it = subjects.begin(); it != subjects.end(); ++it) {
                        Subject tempSubj = *it;
                        cout << subjectApi.parseOutput(tempSubj) << endl;
                    }
                }
            } else if(DEPARTMENTS == choice) {
                vector<Department> departments;
                cout << "Enter ID to select (0 for all entries): ";
                cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                departments = departmentApi.selectById(choice);
                if(departments.size() == 0){
                    cout << "No entries found." << endl;
                }else{
                    cout << "Selected " << departments.size() << " entry/ies: " << endl;
                    cout << departmentApi.getHeader() << endl;
                    for(vector<Department>::iterator it = departments.begin(); it != departments.end(); ++it) {
                        Department tempDept = *it;
                        cout << departmentApi.parseOutput(tempDept) << endl;
                    }
                }
            }
        }
        else if(UPDATE == choice)
        {
            do {
                printTableMenu();
                cin >> choice;
            } while(choice < 1 || choice > NUM_OF_TABLES);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(STUDENTS == choice) {
                string firstName, lastName, birthdate, email, jmbg, department;
                string tmpStr;
                char gender;

                cout << "Enter ID to update: ";
                cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                cout << "First Name: ";
                getline(cin, firstName);
                cout << "Last Name: ";
                getline(cin, lastName);
                cout << "Birth Date(YYYY-MM-DD): ";
                getline(cin, birthdate);
                cout << "Email: ";
                getline(cin, email);
                cout << "JMBG: ";
                getline(cin, jmbg);
                cout << "Gender(M/F): ";
                getline(cin, tmpStr);
                gender = tmpStr[0];
                cout << "Department name: ";
                getline(cin, department);

                if(studentApi.updateById(choice, firstName, lastName, birthdate, email, gender, jmbg, department)){
                    cout << "Update successful." << endl;
                }else{
                    cout << "Update failed.\nError: " << studentApi.error() << endl;
                }
            } else if(TEACHERS == choice) {
                string firstName, lastName, birthdate, email, jmbg, title, department;
                string tmpStr;
                char gender;

                cout << "Enter ID to update: ";
                cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                cout << "First Name: ";
                getline(cin, firstName);
                cout << "Last Name: ";
                getline(cin, lastName);
                cout << "Birth Date(YYYY-MM-DD): ";
                getline(cin, birthdate);
                cout << "Email: ";
                getline(cin, email);
                cout << "JMBG: ";
                getline(cin, jmbg);
                cout << "Title: ";
                getline(cin, title);
                cout << "Gender(M/F): ";
                getline(cin, tmpStr);
                gender = tmpStr[0];
                cout << "Department name: ";
                getline(cin, department);

                if(teacherApi.updateById(choice, firstName, lastName, birthdate, email, gender, jmbg, title, department)){
                    cout << "Update successful." << endl;
                }else{
                    cout << "Update failed.\nError: " << teacherApi.error() << endl;
                }
            } else if(SUBJECTS == choice) {
                string name, abbreviation, tmpStr;
                int ects;

                cout << "Enter ID to update: ";
                cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


                cout << "Name: ";
                getline(cin, name);
                cout << "Ects: ";
                getline(cin, tmpStr);
                ects = atoi(tmpStr.c_str());
                cout << "Abbreaviation: ";
                getline(cin, abbreviation);

                if(subjectApi.updateById(choice, name, ects, abbreviation)){
                    cout << "Update successful!" << endl;
                } else {
                    cout << "Update failed.\nError: " << subjectApi.error() << endl;
                }
            } else if(DEPARTMENTS == choice) {
                string name;

                cout << "Enter ID to update: ";
                cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                cout << "Name: ";
                getline(cin, name);

                if(departmentApi.updateById(choice, name)){
                    cout << "Update successful!" << endl;
                } else {
                    cout << "Update failed.\nError: " << departmentApi.error() << endl;
                }
            }
        }
        else if(DELETE == choice)
        {
            do {
                printTableMenu();
                cin >> choice;
            } while(choice < 1 || choice > NUM_OF_TABLES);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if(STUDENTS == choice) {
                cout << "Enter ID to delete: ";
                cin >> choice;
                if(studentApi.deleteById(choice)){
                    cout << "Entry successfully deleted!" << endl;
                } else {
                    cout << "Delete failed.\nError: " << studentApi.error() << endl;
                }
            } else if(TEACHERS == choice) {
                cout << "Enter ID to delete: ";
                cin >> choice;
                if(teacherApi.deleteById(choice)){
                    cout << "Entry successfully deleted!" << endl;
                } else {
                    cout << "Delete failed.\nError: " << teacherApi.error() << endl;
                }
            } else if(SUBJECTS == choice) {
                cout << "Enter ID to delete: ";
                cin >> choice;
                if(subjectApi.deleteById(choice)){
                    cout << "Entry successfully deleted!" << endl;
                } else {
                    cout << "Delete failed.\nError: " << subjectApi.error() << endl;
                }
            } else if(DEPARTMENTS == choice) {
                cout << "Enter ID to delete: ";
                cin >> choice;
                if(departmentApi.deleteById(choice)){
                    cout << "Entry successfully deleted!" << endl;
                } else {
                    cout << "Delete failed.\nError: " << departmentApi.error() << endl;
                }
            }
        }

        printMenu();
    }

    cout << "Bye." << endl;
    return 0;
}
