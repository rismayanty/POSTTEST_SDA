#include <iostream>
using namespace std;

void swapnilai(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int nilai1, nilai2;

    cout << "=== PERTUKARAN NILAI ===" << endl;
    
    cout << "Masukkan nilai 1: ";
    cin >> nilai1;
    cout << "Masukkan nilai 2: ";
    cin >> nilai2;

    // befor3
    cout << "\n--- SEBELUM DITUKAR ---" << endl;
    cout << "Nilai 1: " << nilai1 << endl;
    cout << "Nilai 2: " << nilai2 << endl;

    swapnilai(&nilai1, &nilai2);

    // aft3r
    cout << "\n--- SESUDAH DITUKAR ---" << endl;
    cout << "Nilai 1: " << nilai1 << endl;
    cout << "Nilai 2: " << nilai2 << endl;

    return 0;
}