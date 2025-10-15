#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

// Struktura za opisivanje matrice
struct Matrica {
    float** elementi;
    int redaka;
    int stupaca;
};

// Funkcija za dinamičku alokaciju memorije za matricu
Matrica alociraj_matricu(int m, int n) {
    if (m <= 0 || n <= 0) {
        throw std::invalid_argument("Broj redaka i stupaca mora biti veci od 0.");
    }
    
    Matrica mat;
    mat.redaka = m;
    mat.stupaca = n;
    
    // Alociranje niza pokazivača (redaka)
    mat.elementi = new float*[m];
    
    // Alociranje memorije za svaki redak (stupce)
    for (int i = 0; i < m; ++i) {
        mat.elementi[i] = new float[n];
    }
    
    return mat;
}

// Funkcija za oslobađanje memorije matrice
void izbrisi_matricu(Matrica& mat) {
    if (mat.elementi == nullptr || mat.redaka <= 0) {
        return; 
    }
    
    // Oslobađanje memorije za svaki redak
    for (int i = 0; i < mat.redaka; ++i) {
        delete[] mat.elementi[i];
    }
    
    // Oslobađanje niza pokazivača
    delete[] mat.elementi;
    
    mat.elementi = nullptr;
    mat.redaka = 0;
    mat.stupaca = 0;
}

// -----------------------------------------------------------------
// FUNKCIJE ZA I/O
// -----------------------------------------------------------------

// Funkcija za unos elemenata matrice
void unesi_matricu(Matrica& mat) {
    std::cout << "Unesite elemente matrice " << mat.redaka << "x" << mat.stupaca << ":" << std::endl;
    for (int i = 0; i < mat.redaka; ++i) {
        for (int j = 0; j < mat.stupaca; ++j) {
            std::cout << "Element[" << i + 1 << "][" << j + 1 << "]: ";
            std::cin >> mat.elementi[i][j];
        }
    }
}

// Funkcija za generiranje matrice mxn s elementima u rasponu [a, b]
Matrica generiraj_matricu(int m, int n, float a, float b) {
    Matrica mat = alociraj_matricu(m, n);
    float raspon = b - a;
    
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            // Generiranje float broja u [a, b]
            mat.elementi[i][j] = a + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / raspon));
        }
    }
    
    return mat;
}

// Funkcija za ispisivanje matrice (4 decimale, poravnato udesno)
void ispisi_matricu(const Matrica& mat) {
    if (mat.elementi == nullptr) {
        std::cout << "Matrica je prazna ili nije alocirana." << std::endl;
        return;
    }
    
    std::cout << "Matrica " << mat.redaka << "x" << mat.stupaca << ":" << std::endl;
    for (int i = 0; i < mat.redaka; ++i) {
        for (int j = 0; j < mat.stupaca; ++j) {
            std::cout << std::fixed << std::setprecision(4) 
                      << std::setw(12) << mat.elementi[i][j]; 
        }
        std::cout << std::endl;
    }
}

// -----------------------------------------------------------------
// FUNKCIJE ZA OPERACIJE S MATRICAMA
// -----------------------------------------------------------------

// Zbrajanje matrica (A + B)
Matrica zbroji_matrice(const Matrica& A, const Matrica& B) {
    if (A.redaka != B.redaka || A.stupaca != B.stupaca) {
        throw std::invalid_argument("Matrice moraju imati iste dimenzije za zbrajanje.");
    }
    
    Matrica Rezultat = alociraj_matricu(A.redaka, A.stupaca);
    
    for (int i = 0; i < A.redaka; ++i) {
        for (int j = 0; j < A.stupaca; ++j) {
            Rezultat.elementi[i][j] = A.elementi[i][j] + B.elementi[i][j];
        }
    }
    
    return Rezultat;
}

// Oduzimanje matrica (A - B)
Matrica oduzmi_matrice(const Matrica& A, const Matrica& B) {
    if (A.redaka != B.redaka || A.stupaca != B.stupaca) {
        throw std::invalid_argument("Matrice moraju imati iste dimenzije za oduzimanje.");
    }
    
    Matrica Rezultat = alociraj_matricu(A.redaka, A.stupaca);
    
    for (int i = 0; i < A.redaka; ++i) {
        for (int j = 0; j < A.stupaca; ++j) {
            Rezultat.elementi[i][j] = A.elementi[i][j] - B.elementi[i][j];
        }
    }
    
    return Rezultat;
}

// Množenje matrica (A * B)
Matrica pomnozi_matrice(const Matrica& A, const Matrica& B) {
    if (A.stupaca != B.redaka) {
        throw std::invalid_argument("Broj stupaca prve matrice mora biti jednak broju redaka druge matrice za mnozenje.");
    }
    
    Matrica Rezultat = alociraj_matricu(A.redaka, B.stupaca);
    
    for (int i = 0; i < A.redaka; ++i) {
        for (int j = 0; j < B.stupaca; ++j) {
            Rezultat.elementi[i][j] = 0.0f;
            for (int k = 0; k < A.stupaca; ++k) {
                Rezultat.elementi[i][j] += A.elementi[i][k] * B.elementi[k][j];
            }
        }
    }
    
    return Rezultat;
}

// Transponiranje matrice
Matrica transponiraj_matricu(const Matrica& mat) {
    Matrica Transponirana = alociraj_matricu(mat.stupaca, mat.redaka);
    
    for (int i = 0; i < mat.redaka; ++i) {
        for (int j = 0; j < mat.stupaca; ++j) {
            Transponirana.elementi[j][i] = mat.elementi[i][j];
        }
    }
    
    return Transponirana;
}

// -----------------------------------------------------------------
// MAIN FUNKCIJA ZA TESTIRANJE
// -----------------------------------------------------------------

int main() {
    // Inicijalizacija generatora nasumičnih brojeva
    srand(static_cast<unsigned int>(time(0)));
    
    Matrica A, B, C, R, T;
    
    try {
        // Generiranje matrica
        std::cout << "--- Generiranje Matrica ---\n";
        A = generiraj_matricu(3, 2, 0.0f, 10.0f); // 3x2 matrica
        ispisi_matricu(A);
        
        B = generiraj_matricu(3, 2, 5.0f, 15.0f); // 3x2 matrica
        ispisi_matricu(B);

        // Zbrajanje
        std::cout << "--- Zbrajanje (A + B) ---\n";
        R = zbroji_matrice(A, B);
        ispisi_matricu(R);
        izbrisi_matricu(R);
        
        // Transponiranje
        std::cout << "--- Transponiranje (A^T) ---\n";
        T = transponiraj_matricu(A); // Transponirana je 2x3
        ispisi_matricu(T);

        // Množenje
        std::cout << "--- Mnozenje (T * B) (2x3 * 3x2 = 2x2) ---\n";
        R = pomnozi_matrice(T, B);
        ispisi_matricu(R);
        izbrisi_matricu(R);
        
        // Primjer unosa (Unosimo 2x2 matricu)
        std::cout << "--- Unos Matrice C (2x2) ---\n";
        C = alociraj_matricu(2, 2);
        unesi_matricu(C);
        ispisi_matricu(C);

    } catch (const std::invalid_argument& e) {
        std::cerr << "Greska: " << e.what() << std::endl;
    }

    // Oslobađanje svih alociranih matrica
    izbrisi_matricu(A);
    izbrisi_matricu(B);
    izbrisi_matricu(T);
    izbrisi_matricu(C);
    
    return 0;
}