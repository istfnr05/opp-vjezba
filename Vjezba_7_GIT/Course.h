#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <iostream>

using namespace std;

class Course {
    string name;
    string code;
    int ects;
public:
    Course(string n = "", string c = "", int e = 5);
    int get_ects() const;
    friend ostream& operator<<(ostream& os, const Course& c);
    friend istream& operator>>(istream& is, Course& c);
};
#endif