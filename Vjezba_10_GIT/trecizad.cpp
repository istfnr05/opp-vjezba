#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <string>
#include <fstream>
using namespace std;
//Definirajte klasu Student sa članovima : ime, prezime, bodovi.Kreirajte namespace
//student_records.U main funkciji :
//• Učitajte podatke iz datoteke studenti.txt u vector<Student>.
//• Definirajte funkciju(ili lambda izraz) za konverziju bodova u ocjenu prema sljedećoj
//skali : 0 - 39 → 1, 40 - 54 → 2, 55 - 69 → 3, 70 - 84 → 4, 85 - 100 → 5
//• Implementirajte Map - Filter - Reduce koristeći STL :
//◦ FILTER : remove_if + erase - iz vektora izbacite studente s manje od 40 bodova,
//◦ MAP : transform - zamijenite bodove svakog studenta u vektoru s odgovarajućom
//ocjenom(koristeći funkciju bodovi_u_ocjenu),
//◦ REDUCE : accumulate - izračunajte prosjek ocjena iz vektora studenata.
//• std::sort - sortirajte po prezimenu
//• Ispišite izvještaj
namespace student_records {
	class Student {
	private:
		string ime;
		string prezime;
		int bodovi;
	public:
		Student(const string& i="",const string& p="",int b=0): ime(i),prezime(p),bodovi(b){}
		string get_ime()const { return ime; }
		string get_prezime()const { return prezime; }
		int get_bodovi()const { return bodovi; }
		void setBodovi(int b) { bodovi = b; }

		friend ostream& operator<<(ostream& os, const Student& s) {
			os << s.ime << " " << s.prezime << " " << s.bodovi << endl;
			return os;
		}
		friend istream& operator>>(istream& is,Student& s) {
			return is >> s.ime >> s.prezime >> s.bodovi;
		}
	};
}
int bodovi_ocjena(int bodovi) {
	if (bodovi < 40)return 1;
	else if (bodovi < 55) return 2;
	else if (bodovi < 70) return 3;
	else if (bodovi < 85) return 4;
	else return 5;
}
int main() {
	ifstream file("studenti.txt");
	if (!file.is_open()) {
		cout << "nmg otvorit";
		return 1;
	}
	vector <student_records::Student> studenti;
	student_records::Student s;
	while (file >> s) {
		studenti.push_back(s);
	}
	cout << studenti.size() << endl;
	auto kraj = remove_if(studenti.begin(), studenti.end(), [](const student_records::Student& s) {return s.get_bodovi() < 40; });
	studenti.erase(kraj, studenti.end());
	transform(studenti.begin(), studenti.end(), studenti.begin(), [](student_records::Student s) {
		s.setBodovi(bodovi_ocjena(s.get_bodovi()));
		return s;
		});
	double suma_ocjena = accumulate(studenti.begin(), studenti.end(), 0.0,
		[](double sum, const student_records::Student& s) {
			return sum + s.get_bodovi();
		});
	double prosjek = 0;
	if (!studenti.empty()) {
		prosjek = suma_ocjena / studenti.size();
	}
	sort(studenti.begin(), studenti.end(),
		[](const student_records::Student& a, const student_records::Student& b) {
			return a.get_prezime() < b.get_prezime();
		});
	cout << "Prosjek ocjena: " << prosjek << endl;
	cout << "sortirano po prezimenu: ";

	for (const auto& student : studenti) {
		cout << student << endl;
	}
	return 0;
}