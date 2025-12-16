#include "Student.h"
#include "UniversityConstants.h"
#include <algorithm>

int Student::total_students = 0;

Student::Student(int i, string n, string sp, int y) 
    : id(i), name(n), study_program(sp), year(y), enrolled_courses(nullptr), 
      enrolled_count(0), completed_courses(nullptr), completed_count(0) {
    total_students++;
}

Student::~Student() {
    delete[] enrolled_courses;
    delete[] completed_courses;
    total_students--;
}

Student::Student(const Student& other) : id(other.id), name(other.name), study_program(other.study_program), year(other.year) {
    enrolled_count = other.enrolled_count;
    enrolled_courses = new Course[enrolled_count];
    copy(other.enrolled_courses, other.enrolled_courses + enrolled_count, enrolled_courses);
    
    completed_count = other.completed_count;
    completed_courses = new Course[completed_count];
    copy(other.completed_courses, other.completed_courses + completed_count, completed_courses);
    total_students++;
}

Student& Student::operator=(const Student& other) {
    if(this == &other) return *this;
    delete[] enrolled_courses;
    delete[] completed_courses;
    
    id = other.id; name = other.name; study_program = other.study_program; year = other.year;
    enrolled_count = other.enrolled_count;
    enrolled_courses = new Course[enrolled_count];
    copy(other.enrolled_courses, other.enrolled_courses + enrolled_count, enrolled_courses);
    
    completed_count = other.completed_count;
    completed_courses = new Course[completed_count];
    copy(other.completed_courses, other.completed_courses + completed_count, completed_courses);
    return *this;
}

Student::Student(Student&& other) noexcept 
    : id(other.id), name(other.name), study_program(other.study_program), year(other.year),
      enrolled_courses(other.enrolled_courses), enrolled_count(other.enrolled_count),
      completed_courses(other.completed_courses), completed_count(other.completed_count) {
    other.enrolled_courses = nullptr;
    other.completed_courses = nullptr;
    other.enrolled_count = 0;
    other.completed_count = 0;
    total_students++;
}

Student& Student::operator=(Student&& other) noexcept {
    if(this == &other) return *this;
    delete[] enrolled_courses;
    delete[] completed_courses;
    
    id = other.id; name = other.name; study_program = other.study_program; year = other.year;
    enrolled_courses = other.enrolled_courses; enrolled_count = other.enrolled_count;
    completed_courses = other.completed_courses; completed_count = other.completed_count;
    
    other.enrolled_courses = nullptr; other.completed_courses = nullptr;
    return *this;
}

int Student::get_total_students() { return total_students; }

int Student::get_total_completed_ects() const {
    int sum = 0;
    for(size_t i = 0; i < completed_count; ++i) sum += completed_courses[i].get_ects();
    return sum;
}

int Student::get_total_enrolled_ects() const {
    int sum = 0;
    for(size_t i = 0; i < enrolled_count; ++i) sum += enrolled_courses[i].get_ects();
    return sum;
}

Student& Student::operator+=(const Course& c) {
    Course* temp = new Course[enrolled_count + 1];
    copy(enrolled_courses, enrolled_courses + enrolled_count, temp);
    temp[enrolled_count] = c;
    delete[] enrolled_courses;
    enrolled_courses = temp;
    enrolled_count++;
    return *this;
}

void Student::complete_course(const Course& c) {
    Course* temp = new Course[completed_count + 1];
    copy(completed_courses, completed_courses + completed_count, temp);
    temp[completed_count] = c;
    delete[] completed_courses;
    completed_courses = temp;
    completed_count++;
}

Student& Student::operator++() {
    if(get_total_completed_ects() >= UniversityConstants::REQUIRED_ECTS_PER_YEAR) year++;
    return *this;
}

Student Student::operator++(int) {
    Student temp(*this);
    ++(*this);
    return temp;
}

ostream& operator<<(ostream& os, const Student& s) {
    os << "ID: " << s.id << ", Ime: " << s.name << ", Program: " << s.study_program << ", Godina: " << s.year;
    return os;
}

istream& operator>>(istream& is, Student& s) {
    is >> s.id >> s.name >> s.study_program >> s.year;
    return is;
}