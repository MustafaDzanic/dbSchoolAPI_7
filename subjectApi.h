#ifndef SUBJECTAPI_H_INCLUDED
#define SUBJECTAPI_H_INCLUDED
#include <fstream>
#include "../dto/dto.h"
#include "../globals.h"
using namespace std;

class Subject;

class SubjectApi
{
private:
    const char* fileName;
    fstream file;
    string header;
    string _error;
    vector<Subject> subjectList;
    unsigned lastId;

    void setError(string err);
    Subject parseObject (string row);

    bool readAllSubjects();
    bool writeAllSubjects();
public:
    SubjectApi();
    string error();
    string getHeader();
    string parseOutput (Subject s);
    bool save(string name, int ects, string abbreviation, string teacherId);
    bool deleteById(unsigned id);
    vector<Subject> selectById(unsigned id);
    bool updateById(unsigned id, string name, int ects, string abbreviation);
    bool saveSubjectTeacher(unsigned subjectId, unsigned teacherId);
};

#endif // SUBJECTAPI_H_INCLUDED
