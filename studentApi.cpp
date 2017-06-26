#include "studentApi.h"
#include "departmentApi.h"
#include <stdlib.h>
#include <sstream>

template<typename T>
std::string toString(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

StudentApi::StudentApi(){
    fileName = "./db/students.txt";
    header = "";
    _error = "";
}

void StudentApi::setError(string err){
    _error = err;
}
Student StudentApi::parseObject (string row){
    Student studentOut;
    vector<string> tokens = split(row, ',');

    studentOut.id = atoi(tokens.at(0).c_str());
    studentOut.firstName = tokens.at(1);
    studentOut.lastName = tokens.at(2);
    studentOut.birthdate = tokens.at(3);
    studentOut.email = tokens.at(4);
    studentOut.gender = tokens.at(5)[0];
    studentOut.jmbg = tokens.at(6);
    studentOut.departmentId = atoi(tokens.at(7).c_str());

    return studentOut;
}

bool StudentApi::readAllStudents(){
    string row;
    studentList.clear();

    file.open(fileName);
    getline(file, header);
    while (getline(file, row)) {
        studentList.push_back(parseObject(row));
    }

    if (!studentList.empty()){
        lastId = studentList.back().id;
    } else {
        lastId = 0;
    }
    file.close();

    return true;
}
bool StudentApi::writeAllStudents(){
    file.open(fileName, std::fstream::out | std::fstream::trunc);
    file << header << endl;
    for(vector<Student>::iterator it = studentList.begin(); it != studentList.end(); ++it) {
        Student tempStud = *it;
        file << parseOutput(tempStud) << endl;
    }
    file.close();
    return true;
}

string StudentApi::error(){
    string tmpErr = _error;
    _error = "";
    return tmpErr;
}
string StudentApi::getHeader(){
    file.open(fileName);
    getline(file, header);
    file.close();
    return header;
}
string StudentApi::parseOutput (Student s){
    string out = "";
    out = toString(s.id) + "," + s.firstName + "," + s.lastName + "," + s.birthdate + "," + s.email + "," + s.gender + "," + s.jmbg + "," + toString(s.departmentId);
    return out;
}
bool StudentApi::save(string firstName, string lastName, string birthdate, string email, char gender, string jmbg, string departmentName){
    Student studentIn;

    if((studentIn.firstName = firstName) == ""){
        setError("First name not entered.");
        return false;
    }
    if((studentIn.lastName = lastName) == ""){
        setError("Last name not entered.");
        return false;
    }
    if((studentIn.birthdate = birthdate) == ""){
        setError("Birth date not entered.");
        return false;
    }
    if((studentIn.email = email) == "" || !is_email_valid(email)){
        setError("Invalid email.");
        return false;
    }
    if((studentIn.gender = gender) == '\0' || (gender != 'M' && gender != 'F')){
        setError("Invalid gender.");
        return false;
    }
    if((studentIn.jmbg = jmbg) == "" || jmbg.size() != 13 || !is_digits(jmbg)){
        setError("Invalid JMBG.");
        return false;
    }
    if(departmentName == ""){
        setError("Department name not entered.");
        return false;
    }

    DepartmentApi deptApi;
    if(!(studentIn.departmentId = deptApi.findByName(departmentName))){
        if(!deptApi.save(departmentName)){
            setError("Couldn't create Department.");
            return false;
        }
        studentIn.departmentId = deptApi.findByName(departmentName);
    }

    readAllStudents();
    studentIn.id = lastId + 1;
    //add student
    studentList.push_back(studentIn);

    writeAllStudents();

    return true;
}
bool StudentApi::deleteById(unsigned id){
    bool deleted = false;
    readAllStudents();
    for(vector<Student>::iterator it = studentList.begin(); it != studentList.end(); ++it) {
        Student tempStud = *it;
        if(tempStud.id == id){
            studentList.erase(it);
            deleted = true;
            break;
        }
    }
    writeAllStudents();

    if(!deleted) setError("ID doesn't exist.");
    return deleted;
}
vector<Student> StudentApi::selectById(unsigned id) {
    vector<Student> StudentsOut;
    readAllStudents();

    if(id == 0){
        return studentList;
    } else {
        for(vector<Student>::iterator it = studentList.begin(); it != studentList.end(); ++it) {
            Student tempStud = *it;
            if(tempStud.id == id){
                StudentsOut.push_back(tempStud);
                break;
            }
        }
    }
    return StudentsOut;
}
bool StudentApi::updateById(unsigned id, string firstName, string lastName, string birthdate, string email, char gender, string jmbg, string departmentName){
    bool found = false;
    vector<Student>::iterator it;
    Student studentIn;

    readAllStudents();

    for(it = studentList.begin(); it != studentList.end(); ++it) {
        studentIn = *it;
        if(studentIn.id == id){
            found = true;
            break;
        }
    }
    if(!found){
        setError("ID doesn't exist.");
        return false;
    }

    if((studentIn.firstName = firstName) == ""){
        setError("First name not entered.");
        return false;
    }
    if((studentIn.lastName = lastName) == ""){
        setError("Last name not entered.");
        return false;
    }
    if((studentIn.birthdate = birthdate) == ""){
        setError("Birth date not entered.");
        return false;
    }
    if((studentIn.email = email) == "" || !is_email_valid(email)){
        setError("Invalid email.");
        return false;
    }
    if((studentIn.gender = gender) == '\0' || (gender != 'M' && gender != 'F')){
        setError("Invalid gender.");
        return false;
    }
    if((studentIn.jmbg = jmbg) == "" || jmbg.size() != 13 || !is_digits(jmbg)){
        setError("Invalid JMBG.");
        return false;
    }
    if(departmentName == ""){
        setError("Department name not entered.");
        return false;
    }

    DepartmentApi deptApi;
    if(!(studentIn.departmentId = deptApi.findByName(departmentName))){
        if(!deptApi.save(departmentName)){
            setError("Couldn't create Department.");
            return false;
        }
        studentIn.departmentId = deptApi.findByName(departmentName);
    }

    *it = studentIn;

    writeAllStudents();

    return true;
}
