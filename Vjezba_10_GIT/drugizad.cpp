#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <iterator>
#include <cmath>
#include <numeric>
using namespace std;
//Kreirajte namespace math_utils koji sadrži :
//• Strukturu Point s koordinatama 𝑥 i 𝑦.
//• Funkciju distance() koja računa udaljenost između dvije točke.
//• Funkciju centroid() koja prima vektor točaka i vraća centroid(središnju točku 𝑥𝑐, 𝑦𝑐,
//gdje je 𝑥𝑐 prosjek svih 𝑥 koordinata, a 𝑦𝑐 prosjek svih 𝑦 koordinata točaka vektora).
//Za računanje centroida koristite accumulate, a za castanje static_cast<double>.

//U main funkciji, koristeći std::ifstream i std::istream_iterator, učitajte točke 
//iz datoteke points.txt.Pomoću STL algoritama i funkcija iz math_utils :
//◦ std::sort s lambda - sortirajte točke po udaljenosti od ishodišta
//◦ std::count_if - prebrojite točke u prvom kvadrantu(𝑥 > 0, 𝑦 > 0)
//◦ math_utils::centroid() - izračunajte centroid
//◦ std::transform - pomaknite sve točke za(5, 3)
//◦ std::remove_if + erase - uklonite točke s obje koordinate negativne
//◦ Ispišite rezultate koristeći std::ostream_iterator
namespace math_utils {
	struct Point {
		double x;
		double y;
	};

	double distance(const Point& p1, const Point& p2={0.0,0.0}) {
		return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
	}
	Point centroid(const vector<Point>& points) {
		if (points.empty())return { 0.0,0.0 };
		double sum_x = accumulate(points.begin(), points.end(), 0.0, [](double sum, const Point& p) {return sum + p.x; });
		double sum_y = accumulate(points.begin(), points.end(), 0.0, [](double sum,const Point& p) {return sum + p.y; });
		double n = static_cast<double>(points.size());
		return { sum_x / n,sum_y / n };
	}
	istream& operator>>(istream& is, math_utils::Point& p) {
		return is >> p.x >> p.y;
	}
	ostream& operator<<(ostream& os, const math_utils::Point& p) {
		os << p.x << " " << p.y;
		return os;
	}
}
int main() {
	ifstream file("points.txt");
	if (!file.is_open()) {
		cout << "ne mogu otvoriti" << endl;
		return 1;
	}
	vector <math_utils::Point>points;

	copy(istream_iterator<math_utils::Point>(file),
		istream_iterator<math_utils::Point>(),
		back_inserter(points));
	cout << "Ucitane tocke:" << endl;
	copy(points.begin(), points.end(), ostream_iterator<math_utils::Point>(cout, " "));
	cout << endl << endl;

	sort(points.begin(), points.end(),
		[](const math_utils::Point& a, const math_utils::Point& b) {
			return math_utils::distance(a) < math_utils::distance(b);
		});
	for (const auto& p : points) {
		cout << p << " ";
	}
	cout << endl;
	int broj_kvadrat = count_if(points.begin(), points.end(), [](const math_utils::Point& p) {
		return p.x > 0 && p.y > 0;
		});
	cout << "broj tocaka: " << broj_kvadrat << endl;

	math_utils::Point c = math_utils::centroid(points);
	cout << "Centroid: " << c << endl;

	vector<math_utils::Point> pomak(points.size());
	transform(points.begin(), points.end(), pomak.begin(), [](const math_utils::Point& p){
		return math_utils::Point{p.x + 5,p.y + 3};
		});
	for (const auto& p : pomak) {
		cout << p.x << " " << p.y;
	}
	cout << endl;
	auto kraj = remove_if(points.begin(), points.end(), [](const math_utils::Point& p) {return p.x < 0 && p.y < 0; });
	points.erase(kraj, points.end());
	copy(points.begin(), points.end(), ostream_iterator<math_utils::Point>(cout, " "));
	return 0;
}