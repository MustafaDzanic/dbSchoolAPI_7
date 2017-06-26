#include "teacherApi.h"
#include "departmentApi.h"

TeacherApi::TeacherApi () {
    fileName = "./db/teachers.txt";
    header = "";
    _error = "";
}

void TeacherApi::setError(string err){
    _error = err;
}
Teacher TeacherApi::parseObject (string row){
    Teacher teacherOut;
    vector<string> tokens = split(row, ',');

    teacherOut.id = atoi(tokens.at(0).c_str());
    teacherOut.firstName = tokens.at(1);
    teacherOut.lastName = tokens.at(2);
    teacherOut.birthdate = tokens.at(3);
    teacherOut.email = tokens.at(4);
    teacherOut.gender = tokens.at(5)[0];
    teacherOut.jmbg = tokens.at(6);
    teacherOut.title = tokens.at(7);
    teacherOut.departmentId = atoi(tokens.at(8).c_str());

    return teacherOut;
}

bool TeacherApi::readAllTeachers(){
    string row;
    teacherList.clear();

    file.open(fileName);
    getline(file, header);
    while (getline(file, row)) {
        teacherList.push_back(parseObject(row));
    }

    if (!teacherList.empty()){
        lastId = teacherList.back().id;
    } else {
        lastId = 0;
    }
    file.close();

    return true;
}
bool TeacherApi::writeAllTeachers(){
    file.open(fileName, std::fstream::out | std::fstream::trunc);
    file << header << endl;
    for(vector<Teacher>::iterator it = teacherList.begin(); it != teacherList.end(); ++it) {
        Teacher tempTeac = *it;
        file << parseOutput(tempTeac) << endl;
    }
    file.close();
    return true;
}

string TeacherApi::error(){
    string tmpErr = _error;
    _error = "";
    return tmpErr;
}
string TeacherApi::getHeader(){
    file.open(fileName);
    getline(file, header);
    file.close();
    return header;
}
string TeacherApi::parseOutput (Teacher s){
    string out = "";
    out = toString(s.id) + "," + s.firstName + "," + s.lastName + "," + s.birthdate + "," + s.email + "," + s.gender + "," + s.jmbg + "," + s.title + "," + toString(s.departmentId);
    return out;
}
bool TeacherApi::save(string firstName, string lastName, string birthdate, string email, char gender, string jmbg, string title, string departmentName){
    Teacher teacherIn;

    if((teacherIn.firstName = firstName) == ""){
        setError("First name not entered.");
        return false;
    }
    if((teacherIn.lastName = lastName) == ""){
        setError("Last name not entered.");
        return false;
    }
    if((teacherIn.birthdate = birthdate) == ""){
        setError("Birth date not entered.");
        return false;
    }
    if((teacherIn.email = email) == "" || !is_email_valid(email)){
        setError("Invalid email.");
        return false;
    }
    if((teacherIn.gender = gender) == '\0' || (gender != 'M' && gender != 'F')){
        setError("Invalid gender.");
        return false;
    }
    if((teacherIn.jmbg = jmbg) == "" || jmbg.size() != 13 || !is_digits(jmbg)){
        setError("Invalid JMBG.");
        return false;
    }
    if((teacherIn.title = title) == ""){
        setError("Title not entered.");
        return false;
    }
    if(departmentName == ""){
        setError("Department name not entered.");
        return false;
    }

    DepartmentApi deptApi;
    if(!(teacherIn.departmentId = deptApi.findByName(departmentName))){
        if(!deptApi.save(departmentName)){
            setError("Couldn't create Department.");
            return false;
        }
        teacherIn.departmentId = deptApi.findByName(departmentName);
    }

    readAllTeachers();
    teacherIn.id = lastId + 1;
    //add student
    teacherList.push_back(teacherIn);

    writeAllTeachers();

    return true;
}
bool TeacherApi::deleteById(unsigned id){
    bool deleted = false;
    readAllTeachers();
    for(vector<Teacher>::iterator it = teacherList.begin(); it != teacherList.end(); ++it) {
        Teacher tempTeac = *it;
        if(tempTeac.id == id){
            teacherList.erase(it);
            deleted = true;
            break;
        }
    }
    writeAllTeachers();

    if(!deleted) setError("ID doesn't exist.");
    return deleted;
}
vector<Teacher> TeacherApi::selectById(unsigned id) {
    vector<Teacher> TeachersOut;
    readAllTeachers();

    if(id == 0){
        return teacherList;
    } else {
        for(vector<Teacher>::iterator it = teacherList.begin(); it != teacherList.end(); ++it) {
            Teacher tempTeac = *it;
            if(tempTeac.id == id){
                TeachersOut.push_back(tempTeac);
                break;
            }
        }
    }
    return TeachersOut;
}
bool TeacherApi::updateById(unsigned id, string firstName, string lastName, string birthdate, string email, char gender, string jmbg, string title, string departmentName){
    bool found = false;
    vector<Teacher>::iterator it;
    Teacher teacherIn;

    readAllTeachers();

    for(it = teacherList.begin(); it != teacherList.end(); ++it) {
        teacherIn = *it;
        if(teacherIn.id == id){
            found = true;
            break;
        }
    }
    if(!found){
        setError("Id doesn't exist.");
        return false;
    }

    if((teacherIn.firstName = firstName) == ""){
        setError("First name not entered.");
        return false;
    }
    if((teacherIn.lastName = lastName) == ""){
        setError("Last name not entered.");
        return false;
    }
    if((teacherIn.birthdate = birthdate) == ""){
        setError("Birth date not entered.");
        return false;
    }
    if((teacherIn.email = email) == "" || !is_email_valid(email)){
        setError("Invalid email.");
        return false;
    }
    if((teacherIn.gender = gender) == '\0' || (gender != 'M' && gender != 'F')){
        setError("Invalid gender.");
        return false;
    }
    if((teacherIn.jmbg = jmbg) == "" || jmbg.size() != 13 || !is_digits(jmbg)){
        setError("Invalid JMBG.");
        return false;
    }
    if((teacherIn.title = title) == ""){
        setError("Title not entered.");
        return false;
    }
    if(departmentName == ""){
        setError("Department name not entered.");
        return false;
    }

    DepartmentApi deptApi;
    if(!(teacherIn.departmentId = deptApi.findByName(departmentName))){
        if(!deptApi.save(departmentName)){
            setError("Couldn't create Department.");
            return false;
        }
        teacherIn.departmentId = deptApi.findByName(departmentName);
    }

    *it = teacherIn;

    writeAllTeachers();

    return true;
}
bool TeacherApi::idExists(unsigned id) {
    bool found = false;
    vector<Teacher>::iterator it;
    Teacher teacherIn;

    readAllTeachers();

    for(it = teacherList.begin(); it != teacherList.end(); ++it) {
        teacherIn = *it;
        if(teacherIn.id == id){
            found = true;
            break;
        }
    }
    return found;
}
