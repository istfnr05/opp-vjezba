#include <iostream>
#include <vector>
#include "Student.h"
#include "Course.h"
#include "StudentOffice.h"
#include "UniversityConstants.h"

using namespace std;

int main() {
    UniversityConstants::print_university_rules();
    cout << "-----------------------------------" << endl;

    vector<Student> studenti;
    studenti.push_back(Student(1, "Marko_Marulic", "Racunarstvo", 1));
    studenti.push_back(Student(2, "Ana_Anic", "Matematika", 1));

    cout << "Trenutno studenata: " << Student::get_total_students() << endl;

    Course c1("Programiranje_1", "PROG1", 7);
    Course c2("Matematika_1", "MAT1", 8);
    Course c3("Strukture_Podataka", "SPA", 35); // Ukupno 50 ECTS

    StudentOffice referada;

    cout << "\n--- Upis kolegija ---" << endl;
    referada.enroll_student(studenti[0], c1);
    referada.enroll_student(studenti[0], c2);
    referada.enroll_student(studenti[0], c3); // Ovo bi trebalo proći (50 < 60)

    Course c4("Prevelik_Kolegij", "BIG", 15);
    referada.enroll_student(studenti[0], c4); // Ovo NE bi trebalo proći (50 + 15 > 60)

    cout << "\n--- Polaganje ispita ---" << endl;
    referada.process_exam_results(studenti[0], c1);
    referada.process_exam_results(studenti[0], c2);
    referada.process_exam_results(studenti[0], c3);

    cout << "Student 1 polozeno ECTS: " << studenti[0].get_total_completed_ects() << endl;

    cout << "\n--- Promjena godine (Referada) ---" << endl;
    cout << "Prije upisa: " << studenti[0] << endl;
    referada.update_student_years(studenti);
    cout << "Nakon upisa: " << studenti[0] << endl;

    cout << "\n--- Move Semantika (Referada) ---" << endl;
    referada.moveStudent(studenti[1], "Fizika");
    cout << "Student 2 nakon premjestaja: " << studenti[1] << endl;

    cout << "\n--- Kraj programa ---" << endl;
    return 0;
}