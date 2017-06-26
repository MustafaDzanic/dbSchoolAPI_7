#include "subjectApi.h"
#include <stdlib.h>
#include <sstream>

template<typename T>
std::string toString(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

SubjectApi::SubjectApi() {
    fileName = "./db/subjects.txt";
    header = "";
    _error = "";
}

void SubjectApi::setError(string err){
    _error = err;
}
Subject SubjectApi::parseObject (string row){
    Subject subjectOut;
    vector<string> tokens = split(row, ',');

    subjectOut.id = atoi(tokens.at(0).c_str());
    subjectOut.name = tokens.at(1);
    subjectOut.ects = atoi(tokens.at(2).c_str());
    subjectOut.abbreviation = tokens.at(3);

    return subjectOut;
}

bool SubjectApi::readAllSubjects(){
    string row;
    subjectList.clear();

    file.open(fileName);
    getline(file, header);
    while (getline(file, row)) {
        subjectList.push_back(parseObject(row));
    }

    if (!subjectList.empty()){
        lastId = subjectList.back().id;
    } else {
        lastId = 0;
    }
    file.close();

    return true;
}
bool SubjectApi::writeAllSubjects(){
    file.open(fileName, std::fstream::out | std::fstream::trunc);
    file << header << endl;
    for(vector<Subject>::iterator it = subjectList.begin(); it != subjectList.end(); ++it) {
        Subject tempSubj = *it;
        file << parseOutput(tempSubj) << endl;
    }
    file.close();
    return true;
}

string SubjectApi::error(){
    string tmpErr = _error;
    _error = "";
    return tmpErr;
}
string SubjectApi::getHeader(){
    file.open(fileName);
    getline(file, header);
    file.close();
    return header;
}
string SubjectApi::parseOutput (Subject s){
    string out = "";
    out = toString(s.id) + "," + s.name + "," + toString(s.ects) + "," + s.abbreviation;
    return out;
}
bool SubjectApi::save(string name, int ects, string abbreviation, string teacherId){
    Subject subjectIn;

    if((subjectIn.name = name) == ""){
        setError("Name not entered.");
        return false;
    }
    subjectIn.ects = ects;
    if((subjectIn.abbreviation = abbreviation) == ""){
        setError("Abbreviation not entered.");
        return false;
    }

    unsigned teachId = 0;
    if(teacherId != "" && is_digits(teacherId)) {
        teachId = atoi(teacherId.c_str());
    }

    readAllSubjects();
    subjectIn.id = lastId + 1;
    //add student
    subjectList.push_back(subjectIn);

    writeAllSubjects();

    if(teachId){
        saveSubjectTeacher(subjectIn.id, teachId);
    }

    return true;
}
bool SubjectApi::deleteById(unsigned id){
    bool deleted = false;
    readAllSubjects();
    for(vector<Subject>::iterator it = subjectList.begin(); it != subjectList.end(); ++it) {
        Subject tempSubj = *it;
        if(tempSubj.id == id){
            subjectList.erase(it);
            deleted = true;
            break;
        }
    }
    writeAllSubjects();

    if(!deleted) setError("ID doesn't exist.");
    return deleted;
}
vector<Subject> SubjectApi::selectById(unsigned id) {
    vector<Subject> SubjectsOut;
    readAllSubjects();

    if(id == 0){
        return subjectList;
    } else {
        for(vector<Subject>::iterator it = subjectList.begin(); it != subjectList.end(); ++it) {
            Subject tempSubj = *it;
            if(tempSubj.id == id){
                SubjectsOut.push_back(tempSubj);
                break;
            }
        }
    }
    return SubjectsOut;
}
bool SubjectApi::updateById(unsigned id, string name, int ects, string abbreviation){
    bool found = false;
    vector<Subject>::iterator it;
    Subject subjectIn;

    readAllSubjects();

    for(it = subjectList.begin(); it != subjectList.end(); ++it) {
        subjectIn = *it;
        if(subjectIn.id == id){
            found = true;
            break;
        }
    }
    if(!found){
        setError("ID doesn't exist.");
        return false;
    }

    if((subjectIn.name = name) == ""){
        setError("Name not entered.");
        return false;
    }
    subjectIn.ects = ects;
    if((subjectIn.abbreviation = abbreviation) == ""){
        setError("Abbreviation not entered.");
        return false;
    }

    *it = subjectIn;

    writeAllSubjects();

    return true;
}
bool SubjectApi::saveSubjectTeacher(unsigned subjectId, unsigned teacherId) {
    ofstream tmpFile("./db/subjects-teachers.txt", std::ios_base::app | std::ios_base::out);
    tmpFile << subjectId << "," << teacherId << endl;
    tmpFile.close();
    return true;
}
