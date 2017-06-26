#ifndef DEPARTMENTAPI_H_INCLUDED
#define DEPARTMENTAPI_H_INCLUDED
#include <fstream>
#include "../dto/dto.h"
#include "../globals.h"
using namespace std;

class DepartmentApi
{
private:
    const char* fileName;
    fstream file;
    string header;
    string _error;
    vector<Department> departmentList;
    unsigned lastId;

    void setError(string err);
    Department parseObject (string row);

    bool readAllDepartments();
    bool writeAllDepartments();
public:
    DepartmentApi();
    string error();
    string getHeader();
    string parseOutput (Department s);
    bool save(string name);
    bool deleteById(unsigned id);
    vector<Department> selectById(unsigned id);
    bool updateById(unsigned id, string name);
    unsigned findByName(string name);
};

#endif // DEPARTMENTAPI_H_INCLUDED
