#include <iostream>
#include <string>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    Mahasiswa mhs[5];
    
    cout << "=== DATA MAHASISWA ===" << endl;
    
    for (int i = 0; i < 5; i++) {
        cout << "\nMahasiswa ke-" << (i + 1) << ":" << endl;
        
        cout << "Nama : ";
        getline(cin, mhs[i].nama);
        
        cout << "NIM  : ";
        cin >> mhs[i].nim;
        cin.ignore(1000, '\n');
        
        cout << "IPK  : ";
        cin >> mhs[i].ipk;
        cin.ignore(1000, '\n');
    }
    
    // ipk tertinggi
    int indeksTertinggi = 0;
    float ipkTertinggi = mhs[0].ipk;
    
    for (int i = 1; i < 5; i++) {
        if (mhs[i].ipk > ipkTertinggi) {
            ipkTertinggi = mhs[i].ipk;
            indeksTertinggi = i;
        }
    }
    
    cout << "\n=== MAHASISWA DENGAN IPK TERTINGGI ===" << endl;
    cout << "Nama : " << mhs[indeksTertinggi].nama << endl;
    cout << "NIM  : " << mhs[indeksTertinggi].nim << endl;
    cout << "IPK  : " << mhs[indeksTertinggi].ipk << endl;

    return 0;
}