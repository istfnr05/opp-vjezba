#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

class Karta {
public:
    int broj;
    string zog;

    Karta(int b, string z) : broj(b), zog(z) {}
    void ispisi() const { cout << broj << " " << zog; }
};

class Mac {
public:
    vector<Karta> karte;

    Mac() {
        vector<string> zoge = {"kupa", "spada", "dinar", "batun"};
        for (string z : zoge)
            for (int b = 1; b <= 10; b++)
                karte.emplace_back(b, z);
    }

    void promijesaj() {
        static std::mt19937 gen(time(nullptr));
        shuffle(karte.begin(), karte.end(), gen);
    }

    vector<vector<Karta>> podijeli(int brojIgraca) {
        vector<vector<Karta>> ruka(brojIgraca);
        int index = 0;
        for (int i = 0; i < brojIgraca; i++)
            for (int j = 0; j < 10; j++)
                ruka[i].push_back(karte[index++]);
        return ruka;
    }
};

class Igrac {
public:
    string ime;
    vector<Karta> ruka;
    int bodovi = 0;

    Igrac(string i) : ime(i) {}

    void izracunajAkuzu() {
        bodovi = 0;
        vector<string> zoge = {"kupa", "spada", "dinar", "batun"};

        for (string z : zoge) {
            bool ima1 = false, ima2 = false, ima3 = false;
            for (auto &k : ruka) {
                if (k.zog == z) {
                    if (k.broj == 1) ima1 = true;
                    if (k.broj == 2) ima2 = true;
                    if (k.broj == 3) ima3 = true;
                }
            }
            if (ima1 && ima2 && ima3)
                bodovi += 3;
        }

        for (int b : {1, 2, 3}) {
            int count = 0;
            for (auto &k : ruka)
                if (k.broj == b) count++;
            if (count == 3) bodovi += 3;
            if (count == 4) bodovi += 4;
        }
    }

    void ispisiRuku() {
        cout << "Ruka igraca " << ime << ":\n";
        for (auto &k : ruka) {
            cout << "  ";
            k.ispisi();
            cout << "\n";
        }
        cout << endl;
    }
};

int main() {
    int n;
    cout << "Unesite broj igraca (2 ili 4): ";
    cin >> n;
    if (n != 2 && n != 4) {
        cout << "Dozvoljeno je samo 2 ili 4 igraca.\n";
        return 0;
    }

    vector<Igrac> igraci;
    for (int i = 0; i < n; i++) {
        string ime;
        cout << "Unesite ime igraca " << i + 1 << ": ";
        cin >> ime;
        igraci.emplace_back(ime);
    }

    Mac mac;
    mac.promijesaj();
    vector<vector<Karta>> podjela = mac.podijeli(n);

    for (int i = 0; i < n; i++) {
        igraci[i].ruka = podjela[i];
        igraci[i].izracunajAkuzu();
    }

    cout << "\n------ REZULTATI ------\n\n";
    for (auto &ig : igraci) {
        ig.ispisiRuku();
        cout << ig.ime << " ima " << ig.bodovi << " bodova iz akuze.\n\n";
    }

    return 0;
}
