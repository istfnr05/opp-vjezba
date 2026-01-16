#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;
//U vektoru prirodnih brojeva koristeæi standardne algoritme :
//• pronaðite prvi neparni broj ako postoji
//pronaðite ukupan broj neparnih brojeva,
//pronaðite prosjek neparnih brojeva(koristite static_cast<double>)
//zamijenite sve brojeve koji su potencije broja 2 (npr. 1, 2, 4, 8, 16) sa 2,
//ispišite prvo sve parne brojeve od manjeg ka veæem, zatim sve neparne od manjeg ka veæem.
int prvi_nep(vector<int> vekt) {
	auto it = find_if(vekt.begin(), vekt.end(), [](int x) {return x % 2 != 0; });
	if (it != vekt.end()) {
		return *it;
	}
	return -1;
}int ukupan_nep(vector<int> vekt) {	return count_if(vekt.begin(), vekt.end(), [](int x) {return x%2 !=0; });} double prosjek(vector <int> vekt) {	int vel= count_if(vekt.begin(), vekt.end(), [](int x) {return x % 2 != 0; });	int zbroj = accumulate(vekt.begin(), vekt.end(), 0, [](int sum, int x) {		if (x % 2 != 0) {			return sum + x;		}		else {			return sum;		}		});	return static_cast<double>(zbroj)/vel;}bool je_potencija(int n) {	if (n <= 0)return false;	while (n > 1) {		if (n % 2 != 0)return false;		n = n / 2;	}	return true;}void zamjeni_potencije(vector<int>& vekt) {	replace_if(vekt.begin(), vekt.end(), [](int x) {return je_potencija(x); }, 2);}void parni_od_manjeg(vector<int> vekt) {	sort(vekt.begin(), vekt.end(), [](int a, int b) {return a < b; });	for (const auto& c : vekt) {		if (c % 2 == 0) {			cout << c << " ";		}	}	cout << endl;}void neparni_od_manjeg(vector <int> vekt) {	sort(vekt.begin(), vekt.end(), [](int a, int b) {return a < b; });	for (const auto& c : vekt) {		if (c % 2 != 0) {			cout << c << " ";		}	}	cout << endl;}int main() {	vector<int> vekt = { 2,4,5,6,2,3,8 };	int rez = prvi_nep(vekt);	cout << "prvi nep: "<< rez << endl;	int rez2 = ukupan_nep(vekt);	cout << "ukupan nep: "<< rez2 << endl;	double rez3 = prosjek(vekt);	cout << "prosje: " << rez3 << endl;	vector <int> kopija = vekt;	zamjeni_potencije(kopija);	for (const auto& c : kopija) {		cout << c << " ";	}	cout << endl;	cout << "parni: ";	parni_od_manjeg(vekt);	cout << "neparni: ";	neparni_od_manjeg(vekt);	return 0;}