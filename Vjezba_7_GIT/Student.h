#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <vector>
#include "Course.h"

using namespace std;

class Student {
    int id;
    string name;
    string study_program;
    int year;
    static int total_students;

    Course* enrolled_courses;
    size_t enrolled_count;
    Course* completed_courses;
    size_t completed_count;

public:
    Student(int i = 0, string n = "", string sp = "", int y = 1);
    ~Student();
    Student(const Student& other);
    Student& operator=(const Student& other);
    Student(Student&& other) noexcept;
    Student& operator=(Student&& other) noexcept;

    static int get_total_students();
    int get_total_completed_ects() const;
    int get_total_enrolled_ects() const;

    Student& operator+=(const Course& c);
    Student& operator++();    
    Student operator++(int); 

    void complete_course(const Course& c);

    friend class StudentOffice;
    friend ostream& operator<<(ostream& os, const Student& s);
    friend istream& operator>>(istream& is, Student& s);
};
#endif