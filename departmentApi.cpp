#include "departmentApi.h"
#include "../globals.h"
#include <stdlib.h>
#include <sstream>

template<typename T>
std::string toString(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

DepartmentApi::DepartmentApi(){
    fileName = "./db/departments.txt";
    header = "";
    _error = "";
}

void DepartmentApi::setError(string err){
    _error = err;
}
Department DepartmentApi::parseObject (string row){
    Department DepartmentOut;
    vector<string> tokens = split(row, ',');

    DepartmentOut.id = atoi(tokens.at(0).c_str());
    DepartmentOut.name = tokens.at(1);

    return DepartmentOut;
}

bool DepartmentApi::readAllDepartments(){
    string row;
    departmentList.clear();

    file.open(fileName);
    getline(file, header);
    while (getline(file, row)) {
        departmentList.push_back(parseObject(row));
    }

    if (!departmentList.empty()){
        lastId = departmentList.back().id;
    } else {
        lastId = 0;
    }
    file.close();

    return true;
}
bool DepartmentApi::writeAllDepartments(){
    file.open(fileName, std::fstream::out | std::fstream::trunc);
    file << header << endl;
    for(vector<Department>::iterator it = departmentList.begin(); it != departmentList.end(); ++it) {
        Department tempDept = *it;
        file << parseOutput(tempDept) << endl;
    }
    file.close();
    return true;
}

string DepartmentApi::error(){
    string tmpErr = _error;
    _error = "";
    return tmpErr;
}
string DepartmentApi::getHeader(){
    file.open(fileName);
    getline(file, header);
    file.close();
    return header;
}
string DepartmentApi::parseOutput (Department s){
    string out = "";
    out = toString(s.id) + "," + s.name;
    return out;
}
bool DepartmentApi::save(string name){
    Department departmentIn;

    if((departmentIn.name = name) == ""){
        setError("Name not entered.");
        return false;
    }

    readAllDepartments();
    departmentIn.id = lastId + 1;
    //add student
    departmentList.push_back(departmentIn);

    writeAllDepartments();

    return true;
}
bool DepartmentApi::deleteById(unsigned id){
    bool deleted = false;
    readAllDepartments();
    for(vector<Department>::iterator it = departmentList.begin(); it != departmentList.end(); ++it) {
        Department tempDept = *it;
        if(tempDept.id == id){
            departmentList.erase(it);
            deleted = true;
            break;
        }
    }
    writeAllDepartments();

    if(!deleted) setError("ID doesn't exist.");
    return deleted;
}
vector<Department> DepartmentApi::selectById(unsigned id) {
    vector<Department> DepartmentsOut;
    readAllDepartments();

    if(id == 0){
        return departmentList;
    } else {
        for(vector<Department>::iterator it = departmentList.begin(); it != departmentList.end(); ++it) {
            Department tempDept = *it;
            if(tempDept.id == id){
                DepartmentsOut.push_back(tempDept);
                break;
            }
        }
    }
    return DepartmentsOut;
}
bool DepartmentApi::updateById(unsigned id, string name){
    bool found = false;
    vector<Department>::iterator it;
    Department departmentIn;

    readAllDepartments();

    for(it = departmentList.begin(); it != departmentList.end(); ++it) {
        departmentIn = *it;
        if(departmentIn.id == id){
            found = true;
            break;
        }
    }
    if(!found){
        setError("ID doesn't exist.");
        return false;
    }

    if((departmentIn.name = name) == ""){
        setError("Name not entered.");
        return false;
    }

    *it = departmentIn;

    writeAllDepartments();

    return true;
}

unsigned DepartmentApi::findByName(string name){
    unsigned targetId = 0;
    vector<Department>::iterator it;
    Department departmentIn;

    readAllDepartments();

    for(it = departmentList.begin(); it != departmentList.end(); ++it) {
        departmentIn = *it;
        if(departmentIn.name == name){
            targetId = departmentIn.id;
            break;
        }
    }

    return targetId;
}
