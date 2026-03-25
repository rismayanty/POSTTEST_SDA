#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

struct kereta {
    int nomorkereta;
    string namakereta;
    string asal;
    string tujuan;
    int hargatiket;
};

void swapkereta(kereta* a, kereta* b) {
    kereta temp = *a;
    *a = *b;
    *b = temp;
}

void tampilkanjadwal(kereta* arr, int n) {
    cout << "\n=== JADWAL KERETA API ===" << endl;
    cout << left << setw(5) << "NO" 
         << setw(15) << "NAMA" 
         << setw(25) << "RUTE" 
         << setw(15) << "HARGA" 
         << setw(15) << "KODE KERETA" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    
    if (n == 0) {
        cout << "yahhh, belum ada data kereta nih..." << endl;
        return;
    }

    for (int i = 0; i < n; i++) {
        string rute = (arr + i)->asal + "-" + (arr + i)->tujuan;
        cout << left << setw(5) << i + 1
             << setw(15) << (arr + i)->namakereta
             << setw(25) << rute
             << setw(15) << ("Rp " + to_string((arr + i)->hargatiket))
             << setw(3) << setfill('0') << (arr + i)->nomorkereta << setfill(' ') << endl;
    }
    cout << "------------------------------------------------------------------------" << endl;
}

void tambahkereta(kereta* arr, int &n, int maxData) {
    if (n >= maxData) {
        cout << "DATA FULL! tidak bisa menambah kereta." << endl;
        return;
    }

    cout << "\n--- TAMBAH DATA KERETA BARU ---" << endl;
    kereta* baru = (arr + n); 

    baru->nomorkereta = n + 1;
    cin.ignore(); 
    
    cout << "NAMA KERETA: ";
    getline(cin, baru->namakereta);
    
    cout << "ASAL: ";
    getline(cin, baru->asal);
    
    cout << "TUJUAN: ";
    getline(cin, baru->tujuan);
    
    cout << "HARGA TIKET: ";
    cin >> baru->hargatiket;

    n++;
    cout << "DATA BERHASIL DITAMBAHKAN!" << endl;
}

void linearSearch(kereta* arr, int n, string asal, string tujuan) {
    cout << "\n--- MENCARI RUTE: " << asal << " -> " << tujuan << " ---" << endl;
    bool ditemukan = false;

    for (int i = 0; i < n; i++) {
        cout << "iterasi ke-" << i + 1 << ": lagi cek nih " 
             << (arr + i)->asal << " -> " << (arr + i)->tujuan << "... ";
        
        if ((arr + i)->asal == asal && (arr + i)->tujuan == tujuan) {
            cout << "COCOK!" << endl;
            cout << "ditemukan! pada index:" << i << endl;
            cout << "DETAIL: " << (arr + i)->namakereta << " (Rp " << (arr + i)->hargatiket << ")" << endl;
            ditemukan = true;
        } else {
            cout << "TIDAK COCOK!" << endl;
        }
    }

    if (!ditemukan) {
        cout << "RUTE GA ADA NIH..." << endl;
    }
}

void insertionsortnomor(kereta* arr, int n) {
    for (int i = 1; i < n; i++) {
        kereta key = *(arr + i);
        int j = i - 1;
        while (j >= 0 && (arr + j)->nomorkereta > key.nomorkereta) {
            *(arr + j + 1) = *(arr + j);
            j = j - 1;
        }
        *(arr + j + 1) = key;
    }
}

void jumpsearch(kereta* arr, int n, int target) {
    insertionsortnomor(arr, n); 
    int step = sqrt(n);
    int prev = 0;
    bool ditemukan = false;

    cout << "\n--- NOMOR KERETA: " << target << " ---" << endl;

    while (arr[step - 1].nomorkereta < target && step < n) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            cout << "NOMOR KERETA GA ADA..." << endl;
            return;
        }
    }

    for (int i = prev; i < min(step, n); i++) {
        if (arr[i].nomorkereta == target) {
            cout << "ditemukan! pada index: " << i << endl;
            cout << "NAMA: " << arr[i].namakereta << ", RUTE: " << arr[i].asal << "-" << arr[i].tujuan << endl;
            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "NOMOR KERETA GA ADA..." << endl;
    }
}

void merge(kereta* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    kereta* L = new kereta[n1];
    kereta* R = new kereta[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].namakereta <= R[j].namakereta) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }

    delete[] L;
    delete[] R;
}

void mergesort(kereta* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void selectionsort(kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->hargatiket < (arr + minIdx)->hargatiket) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swapkereta((arr + i), (arr + minIdx));
        }
    }
    cout << "DATA BERDASARKAN HARGA TERMURAH" << endl;
}

void menusearch(kereta* arr, int n) {
    int pilihan;
    do {
        cout << "\n=== MENU SEARCH ===" << endl;
        cout << "1. Berdasarkan RUTE" << endl;
        cout << "2. Berdasarkan NOMOR KERETA" << endl;
        cout << "3. Menu Utama" << endl;
        cout << "Pilih Menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string asal, tujuan;
                cin.ignore();
                cout << "Asal: "; getline(cin, asal);
                cout << "Tujuan: "; getline(cin, tujuan);
                linearSearch(arr, n, asal, tujuan);
                break;
            }
            case 2: {
                int nomor;
                cout << "NOMOR KERETA: ";
                cin >> nomor;
                jumpsearch(arr, n, nomor);
                break;
            }
            case 3:
                cout << "back to menu utama..." << endl;
                break;
            default:
                cout << "TIDAK VALID!" << endl;
        }
    } while (pilihan != 3);
}

void nenusort(kereta* arr, int n) {
    int pilihan;
    do {
        cout << "\n=== MENU SORT ===" << endl;
        cout << "1. Berdasarkan NAMA KERETA" << endl;
        cout << "2. Berdasarkan HARGA TIKET" << endl;
        cout << "3. Menu Utama" << endl;
        cout << "Pilih Menu: ";
        cin >> pilihan;

        switch (pilihan) {  
            case 1:
                mergesort(arr, 0, n - 1);
                cout << "berhasil diurutkan nih!" << endl;
                tampilkanjadwal(arr, n);
                break;
            case 2:
                selectionsort(arr, n);
                tampilkanjadwal(arr, n);
                break;
            case 3:
                cout << "back to menu utama..." << endl;
                break;
            default:
                cout << "TIDAK VALID!" << endl;
        }
    } while (pilihan != 3);
}

int main() {
    const int MAX_DATA = 100;
    kereta daftarkereta[MAX_DATA];
    int jumlahdata = 0;
    int pilihan;

    daftarkereta[0] = {1, "tirta", "bandung", "jakarta", 500000};
    daftarkereta[1] = {2, "argo", "jakarta", "bandung", 450000};
    daftarkereta[2] = {3, "wishel", "semarang", "yogyakarta", 550000};
    jumlahdata = 3;

    do {
        cout << "\n=== MENU UTAMA ===" << endl;
        cout << "1. Jadwal Kereta" << endl;
        cout << "2. Tambah Data Kereta" << endl;
        cout << "3. Menu Search" << endl;
        cout << "4. Menu Sort" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilih Menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanjadwal(daftarkereta, jumlahdata);
                break;
            case 2:
                tambahkereta(daftarkereta, jumlahdata, MAX_DATA);
                break;
            case 3:
                menusearch(daftarkereta, jumlahdata);
                break;
            case 4:
                nenusort(daftarkereta, jumlahdata);
                break;
            case 5:
                cout << "THANK YOU! BE CAREFUL..." << endl;
                break;
            default:
                cout << "TIDAK VALID!" << endl;
        }
    } while (pilihan != 5);

    return 0;
}