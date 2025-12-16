#include "Course.h"

Course::Course(string n, string c, int e) : name(n), code(c), ects(e) {}

int Course::get_ects() const { return ects; }

ostream& operator<<(ostream& os, const Course& c) {
    os << c.name << " [" << c.code << "] (" << c.ects << " ECTS)";
    return os;
}

istream& operator>>(istream& is, Course& c) {
    is >> c.name >> c.code >> c.ects;
    return is;
}