#include <iostream>
#include <cstddef>
#include <string>
#include <iomanip>
#include <vector>

struct Student {
    std::string ime;
    std::string JMBAG;
    int godina_studija;
    int ECTS_bodovi;
    double prosjek_ocjena;
};

void filter_students(Student arr[], std::size_t size,
                     void (*akcija)(Student&),
                     bool (*filter)(Student&))
{
    for (std::size_t i = 0; i < size; ++i) {
        if (filter(arr[i])) {
            akcija(arr[i]);
        }
    }
}

void ispis_studenta(Student& s) {
    std::cout << "| " << std::setw(15) << std::left << s.ime
              << "| " << std::setw(8) << s.JMBAG
              << "| " << std::setw(7) << s.godina_studija
              << "| " << std::setw(4) << s.ECTS_bodovi
              << "| " << std::setw(6) << std::fixed << std::setprecision(2) << s.prosjek_ocjena
              << " |" << std::endl;
}

void povecaj_godinu_studija(Student& s) {
    s.godina_studija += 1;
    std::cout << "-> AKCIJA: " << s.ime << " promaknut/a u " << s.godina_studija << ". godinu." << std::endl;
}

void print_header(const std::string& title) {
    std::cout << "\n========================================================" << std::endl;
    std::cout << title << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "| " << std::setw(15) << std::left << "Ime"
              << "| " << std::setw(8) << "JMBAG"
              << "| " << std::setw(7) << "Godina"
              << "| " << std::setw(4) << "ECTS"
              << "| " << std::setw(6) << "Prosjek"
              << " |" << std::endl;
    std::cout << "========================================================" << std::endl;
}

int main() {
    Student studenti[] = {
        {"Ana Anic", "001", 1, 15, 3.20},
        {"Pero Peric", "002", 2, 60, 4.50},
        {"Iva Ivic", "003", 1, 0, 1.00},
        {"Marko Maric", "004", 3, 40, 3.80},
        {"Luka Lukic", "005", 2, 50, 2.90},
        {"Ena Enic", "006", 1, 30, 4.10}
    };
    const std::size_t size = sizeof(studenti) / sizeof(studenti[0]);

    auto uvjet_prva_godina_polozio = [](Student& s) -> bool {
        return s.godina_studija == 1 && s.ECTS_bodovi > 0;
    };

    print_header("1. Studenti 1. godine (ECTS > 0):");
    filter_students(studenti, size, ispis_studenta, uvjet_prva_godina_polozio);

    auto uvjet_prosjek_dobar = [](Student& s) -> bool {
        return s.prosjek_ocjena > 3.5;
    };

    print_header("2. Studenti s prosjekom vecim od 3.5:");
    filter_students(studenti, size, ispis_studenta, uvjet_prosjek_dobar);

    auto uvjet_dovoljno_ects = [](Student& s) -> bool {
        return s.ECTS_bodovi >= 45;
    };

    print_header("3. Povecanje godine studija za ECTS >= 45:");
    filter_students(studenti, size, povecaj_godinu_studija, uvjet_dovoljno_ects);

    std::cout << "\n-- Nakon promjene godine (provjera) --" << std::endl;
    filter_students(studenti, size, ispis_studenta, [](Student& s){ return true; });

    std::cout << "========================================================" << std::endl;

    return 0;
}