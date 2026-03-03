#include <iostream>
using namespace std;

// membalik array (pakai pointer)
void balikArray(int* arr, int n) {
    int* start = arr;
    int* end = arr + n - 1;
    
    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;
        
        start++;
        end--;
    }
}

// nampilin array dan alamat
void nampilinArray(int* arr, int n) {
    int* p = arr;
    for (int i = 0; i < n; i++) {
        cout << "Elemen[" << i << "] = " << *p << "\tAlamat: " << p << endl;
        p++;
    }
}

int main() {
    int prima[7] = {2, 3, 5, 7, 11, 13, 17};
    int n = 7;
    
    cout << "=== ARRAY SEBELUM DIBALIK ===" << endl;
    nampilinArray(prima, n);
    
    balikArray(prima, n);
    
    cout << "\n=== ARRAY SETELAH DIBALIK ===" << endl;
    nampilinArray(prima, n);
    
    return 0;
}