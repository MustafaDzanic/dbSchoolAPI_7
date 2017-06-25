#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
#include <string>
#include <vector>

using namespace std;

#define INSERT 1
#define SELECT 2
#define UPDATE 3
#define DELETE 4
#define STUDENTS 1
#define TEACHERS 2
#define SUBJECTS 3
#define DEPARTMENTS 4
#define NUM_OF_TABLES 4
#define EXIT 5

template<typename T>
std::string toString(const T& value);
bool is_email_valid(std::string const& address);
bool is_digits(const std::string &str);
std::vector<std::string> split(const std::string &text, char sep);

#endif // GLOBALS_H_INCLUDED
