#ifndef STUDENTAPI_H_INCLUDED
#define STUDENTAPI_H_INCLUDED
#include <fstream>
#include "../dto/dto.h"
#include "../globals.h"
using namespace std;

class Student;

class StudentApi
{
private:
    const char* fileName;
    fstream file;
    string header;
    string _error;
    vector<Student> studentList;
    unsigned lastId;

    void setError(string err);
    Student parseObject (string row);

    bool readAllStudents();
    bool writeAllStudents();

public:
    StudentApi();
    string error();
    string getHeader();
    string parseOutput (Student s);
    bool save(string firstName, string lastName, string birthdate, string email, char gender, string jmbg, string departmentName);
    bool deleteById(unsigned id);
    vector<Student> selectById(unsigned id);
    bool updateById(unsigned id, string firstName, string lastName, string birthdate, string email, char gender, string jmbg, string departmentName);
};

#endif // STUDENTAPI_H_INCLUDED
