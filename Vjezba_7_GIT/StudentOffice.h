#ifndef STUDENT_OFFICE_H
#define STUDENT_OFFICE_H
#include "Student.h"
#include "UniversityConstants.h"

class StudentOffice {
public:
    void moveStudent(Student& s, string new_program) {
        s.study_program = move(new_program);
    }

    void enroll_student(Student& s, const Course& c) {
        if (s.get_total_enrolled_ects() + c.get_ects() <= UniversityConstants::MAX_ECTS_PER_YEAR) {
            s += c;
        } else {
            cout << "Student " << s.name << " premasuje limit ECTS-a!" << endl;
        }
    }

    void process_exam_results(Student& s, const Course& c) {
        s.complete_course(c);
    }

    void update_student_years(vector<Student>& students) {
        for(auto& s : students) ++s;
    }
};
#endif