#ifndef TEACHERAPI_H_INCLUDED
#define TEACHERAPI_H_INCLUDED
#include "../dto/dto.h"
#include "../globals.h"
#include <fstream>
#include <stdlib.h>
using namespace std;

class Teacher;

class TeacherApi
{
private:
    const char* fileName;
    fstream file;
    string header;
    string _error;
    vector<Teacher> teacherList;
    unsigned lastId;

    void setError(string err);
    Teacher parseObject (string row);

    bool readAllTeachers();
    bool writeAllTeachers();

public:
    TeacherApi();
    string error();
    string getHeader();
    string parseOutput (Teacher s);
    bool save(string firstName, string lastName, string birthdate, string email, char gender, string jmbg, string title, string departmentName);
    bool deleteById(unsigned id);
    vector<Teacher> selectById(unsigned id);
    bool updateById(unsigned id, string firstName, string lastName, string birthdate, string email, char gender, string jmbg, string title, string departmentName);
    bool idExists(unsigned id);
};

#endif // TEACHERAPI_H_INCLUDED

