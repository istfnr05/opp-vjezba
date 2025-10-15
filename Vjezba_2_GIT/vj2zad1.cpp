#include <iostream>

using namespace std;

int* funkcija(int arr) {
	int* niz = new int(arr);
	niz[0] = 1;
	niz[1] = 1;

	for (int i = 2; i < arr; i++) {
		niz[i] = niz[i - 1] + niz[i - 2];
	}
	return niz;



}

int main() {
	int n;
	cout << "Unesite velicinu niza" << endl;
	cin >> n;
	int* niz = funkcija(n);
	cout << "Niz: " << endl;
	for (int i = 0; i < n; i++) {
		cout << niz[i] << endl;
	}

	cout << endl;

	delete(niz);

	return 0;

}