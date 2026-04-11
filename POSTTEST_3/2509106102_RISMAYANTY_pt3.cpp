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

struct transaksi {
    string namaPenumpang;
    string rute;
    int harga;
    int kodeKereta;
};

const int MAX_DATA = 100;
const int MAX_QUEUE = 50;
const int MAX_STACK = 50;

kereta daftarkereta[MAX_DATA];
int jumlahdata = 0;

transaksi queueTiket[MAX_QUEUE];
int frontQueue = -1, rearQueue = -1;

transaksi stackRiwayat[MAX_STACK];
int topStack = -1;

void swapkereta(kereta* a, kereta* b) {
    kereta temp = *a;
    *a = *b;
    *b = temp;
}

void swapTransaksi(transaksi* a, transaksi* b) {
    transaksi temp = *a;
    *a = *b;
    *b = temp;
}

bool isQueueFull() {
    return rearQueue == MAX_QUEUE - 1;
}

bool isQueueEmpty() {
    return frontQueue == -1 || frontQueue > rearQueue;
}

void enqueue(transaksi* queue, int &front, int &rear, transaksi data) {
    if (rear >= MAX_QUEUE - 1) {
        cout << ">> ANTRIAN PENUH (Overflow) <<" << endl;
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear++;
    *(queue + rear) = data;
    cout << ">> " << data.namaPenumpang << " berhasil masuk antrian <<" << endl;
}

transaksi dequeue(transaksi* queue, int &front, int &rear) {
    transaksi kosong = {"", "", 0, 0};
    if (front == -1 || front > rear) {
        cout << ">> ANTRIAN KOSONG (Underflow) <<" << endl;
        return kosong;
    }
    transaksi data = *(queue + front);
    front++;
    if (front > rear) {
        front = rear = -1;
    }
    return data;
}

transaksi peekQueue(transaksi* queue, int front, int rear) {
    transaksi kosong = {"", "", 0, 0};
    if (front == -1 || front > rear) {
        cout << ">> Antrian kosong <<" << endl;
        return kosong;
    }
    return *(queue + front);
}

void tampilkanQueue(transaksi* queue, int front, int rear) {
    cout << "\n=== ANTRIAN PEMBELIAN TIKET ===" << endl;
    if (front == -1 || front > rear) {
        cout << "Antrian kosong." << endl;
        return;
    }
    cout << left << setw(5) << "NO" 
         << setw(20) << "NAMA" 
         << setw(25) << "RUTE" 
         << setw(15) << "HARGA" 
         << setw(10) << "KODE" << endl;
    cout << "--------------------------------------------------------------" << endl;
    
    int no = 1;
    for (int i = front; i <= rear; i++) {
        cout << left << setw(5) << no++
             << setw(20) << (queue + i)->namaPenumpang
             << setw(25) << (queue + i)->rute
             << setw(15) << ("Rp " + to_string((queue + i)->harga))
             << setw(10) << setfill('0') << (queue + i)->kodeKereta << setfill(' ') << endl;
    }
    cout << "--------------------------------------------------------------" << endl;
}

bool isStackFull() {
    return topStack >= MAX_STACK - 1;
}

bool isStackEmpty() {
    return topStack < 0;
}

void push(transaksi* stack, int &top, transaksi data) {
    if (top >= MAX_STACK - 1) {
        cout << ">> RIWAYAT PENUH (Overflow) <<" << endl;
        return;
    }
    top++;
    *(stack + top) = data;
    cout << ">> Transaksi " << data.namaPenumpang << " berhasil dicatat <<" << endl;
}

transaksi pop(transaksi* stack, int &top) {
    transaksi kosong = {"", "", 0, 0};
    if (top < 0) {
        cout << ">> RIWAYAT KOSONG (Underflow) <<" << endl;
        return kosong;
    }
    transaksi data = *(stack + top);
    top--;
    return data;
}

transaksi peekStack(transaksi* stack, int top) {
    transaksi kosong = {"", "", 0, 0};
    if (top < 0) {
        cout << ">> Riwayat kosong <<" << endl;
        return kosong;
    }
    return *(stack + top);
}

void tampilkanStack(transaksi* stack, int top) {
    cout << "\n=== RIWAYAT TRANSAKSI ===" << endl;
    if (top < 0) {
        cout << "Riwayat kosong." << endl;
        return;
    }
    cout << left << setw(5) << "NO" 
         << setw(20) << "NAMA" 
         << setw(25) << "RUTE" 
         << setw(15) << "HARGA" 
         << setw(10) << "KODE" << endl;
    cout << "--------------------------------------------------------------" << endl;
    
    int no = 1;
    for (int i = 0; i <= top; i++) {
        cout << left << setw(5) << no++
             << setw(20) << (stack + i)->namaPenumpang
             << setw(25) << (stack + i)->rute
             << setw(15) << ("Rp " + to_string((stack + i)->harga))
             << setw(10) << setfill('0') << (stack + i)->kodeKereta << setfill(' ') << endl;
    }
    cout << "--------------------------------------------------------------" << endl;
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

void menusort(kereta* arr, int n) {
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

void menuQueue(kereta* arr, int n) {
    int pilihan;
    do {
        cout << "\n=== MENU ANTRIAN TIKET ===" << endl;
        cout << "1. Enqueue - Masuk Antrian" << endl;
        cout << "2. Dequeue - Proses Tiket" << endl;
        cout << "3. Peek - Lihat Depan Antrian" << endl;
        cout << "4. Tampil Semua Antrian" << endl;
        cout << "5. Menu Utama" << endl;
        cout << "Pilih Menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                if (jumlahdata == 0) {
                    cout << ">> Belum ada data kereta! <<" << endl;
                    break;
                }
                tampilkanjadwal(daftarkereta, jumlahdata);
                
                transaksi baru;
                cin.ignore();
                cout << "Nama Penumpang: ";
                getline(cin, baru.namaPenumpang);
                cout << "Kode Kereta: ";
                cin >> baru.kodeKereta;
                
                bool found = false;
                for (int i = 0; i < n; i++) {
                    if ((arr + i)->nomorkereta == baru.kodeKereta) {
                        baru.rute = (arr + i)->asal + "-" + (arr + i)->tujuan;
                        baru.harga = (arr + i)->hargatiket;
                        found = true;
                        break;
                    }
                }
                
                if (!found) {
                    cout << ">> Kode kereta tidak ditemukan! <<" << endl;
                    break;
                }
                
                enqueue(queueTiket, frontQueue, rearQueue, baru);
                break;
            }
            case 2: {
                transaksi diproses = dequeue(queueTiket, frontQueue, rearQueue);
                if (diproses.namaPenumpang != "") {
                    cout << "\n>> TIKET DIPROSES <<" << endl;
                    cout << "Nama: " << diproses.namaPenumpang << endl;
                    cout << "Rute: " << diproses.rute << endl;
                    cout << "Harga: Rp " << diproses.harga << endl;
                    cout << "Kode Kereta: " << setfill('0') << setw(3) << diproses.kodeKereta << setfill(' ') << endl;
                    
                    push(stackRiwayat, topStack, diproses);
                }
                break;
            }
            case 3: {
                transaksi depan = peekQueue(queueTiket, frontQueue, rearQueue);
                if (depan.namaPenumpang != "") {
                    cout << "\n>> PENUMPANG TERDEPAN <<" << endl;
                    cout << "Nama: " << depan.namaPenumpang << endl;
                    cout << "Rute: " << depan.rute << endl;
                    cout << "Harga: Rp " << depan.harga << endl;
                }
                break;
            }
            case 4:
                tampilkanQueue(queueTiket, frontQueue, rearQueue);
                break;
            case 5:
                cout << "back to menu utama..." << endl;
                break;
            default:
                cout << "TIDAK VALID!" << endl;
        }
    } while (pilihan != 5);
}

void menuStack() {
    int pilihan;
    do {
        cout << "\n=== MENU RIWAYAT TRANSAKSI ===" << endl;
        cout << "1. Pop - Batalkan Transaksi Terakhir" << endl;
        cout << "2. Peek - Lihat Transaksi Terakhir" << endl;
        cout << "3. Tampil Semua Riwayat" << endl;
        cout << "4. Menu Utama" << endl;
        cout << "Pilih Menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                transaksi dibatalkan = pop(stackRiwayat, topStack);
                if (dibatalkan.namaPenumpang != "") {
                    cout << "\n>> TRANSAKSI DIBATALKAN <<" << endl;
                    cout << "Nama: " << dibatalkan.namaPenumpang << endl;
                    cout << "Rute: " << dibatalkan.rute << endl;
                    cout << "Harga: Rp " << dibatalkan.harga << endl;
                }
                break;
            }
            case 2: {
                transaksi terakhir = peekStack(stackRiwayat, topStack);
                if (terakhir.namaPenumpang != "") {
                    cout << "\n>> TRANSAKSI TERAKHIR <<" << endl;
                    cout << "Nama: " << terakhir.namaPenumpang << endl;
                    cout << "Rute: " << terakhir.rute << endl;
                    cout << "Harga: Rp " << terakhir.harga << endl;
                }
                break;
            }
            case 3:
                tampilkanStack(stackRiwayat, topStack);
                break;
            case 4:
                cout << "back to menu utama..." << endl;
                break;
            default:
                cout << "TIDAK VALID!" << endl;
        }
    } while (pilihan != 4);
}

int main() {
    int pilihan;

    daftarkereta[0] = {1, "tirta", "bandung", "jakarta", 500000};
    daftarkereta[1] = {2, "argo", "jakarta", "bandung", 450000};
    daftarkereta[2] = {3, "wishel", "semarang", "yogyakarta", 550000};
    jumlahdata = 3;

    do {
        cout << "\n=== SISTEM MANAJEMEN KERETA API ===" << endl;
        cout << "1. Jadwal Kereta" << endl;
        cout << "2. Tambah Data Kereta" << endl;
        cout << "3. Menu Search" << endl;
        cout << "4. Menu Sort" << endl;
        cout << "5. Antrian Tiket" << endl;
        cout << "6. Riwayat Transaksi" << endl;
        cout << "7. Keluar" << endl;
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
                menusort(daftarkereta, jumlahdata);
                break;
            case 5:
                menuQueue(daftarkereta, jumlahdata);
                break;
            case 6:
                menuStack();
                break;
            case 7:
                cout << "THANK YOU! BE CAREFUL..." << endl;
                break;
            default:
                cout << "TIDAK VALID!" << endl;
        }
    } while (pilihan != 7);

    return 0;
} 