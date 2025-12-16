#ifndef UNIVERSITY_CONSTANTS_H
#define UNIVERSITY_CONSTANTS_H
#include <iostream>

using namespace std;

struct UniversityConstants {
    static const int MAX_ECTS_PER_YEAR = 60;
    static const int REQUIRED_ECTS_PER_YEAR = 45;

    static void print_university_rules() {
        cout << "Sveucilisna pravila:" << endl;
        cout << "Maksimalno ECTS po godini: " << MAX_ECTS_PER_YEAR << endl;
        cout << "Potrebno ECTS za prolaz: " << REQUIRED_ECTS_PER_YEAR << endl;
    }
};

#endif