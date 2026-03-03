#include <iostream>
using namespace std;

// procedure FindMin(A : array of n elements)
//   min ← A[0]
//   for i ← 1 to n − 1 do
//     if A[i] < min then
//       min ← A[i]
//     end if
//   end for
//   return min
// end procedure

// TABEL
//  ------------------------------------------
//  | Pseudocode        | Cost | Tmin | Tmax |
//  ------------------------------------------
//  | procedure FindMin | C1   | 1    | 1    |
//  | min <- A[0]       | C2   | 1    | 1    |
//  | for i <- 1 to n-1 | C3   | n    | n    |
//  | if A[i] < min     | C4   | n-1  | n-1  |
//  | min <- A[i]       | C5   | 0    | n-1  |
//  | end if            | C6   | n-1  | n-1  |
//  | end for           | C7   | n    | n    |
//  | return min        | C8   | 1    | 1    |
//  ------------------------------------------
  
// BEST CASE -> KONDISI SELALU SALAH (array sudah terurut naik)
// Tmin(n) =
// C1 + C2 + C3n + C4(n-1) + 0 + C6(n-1) + C7n + C8
// Hasil akhir -> O(n)

// WORST CASE -> KONDISI SELALU BENAR (array terurut turun)
// Tmax(n) =
// C1 + C2 + C3n + C4(n-1) + C5(n-1) + C6(n-1) + C7n + C8
// Hasil Akhir -> O(n)



void FindMin(int A[], int n, int &minValue, int &minIndex) {
    minValue = A[0];
    minIndex = 0;

    for (int i = 1; i < n; i++) {
        if (A[i] < minValue) {
            minValue = A[i];
            minIndex = i;
        }
    }
}

int main() {
    int fibonacci[] = {1, 1, 2, 3, 5, 8, 13, 21};
    int n = sizeof(fibonacci) / sizeof(fibonacci[0]);
    
    int minVal, minIdx;

    FindMin(fibonacci, n, minVal, minIdx);

    cout << "=== HASIL EKSEKUSI PROGRAM ===" << endl;
    cout << "Array Fibonacci: {1, 1, 2, 3, 5, 8, 13, 21}" << endl;
    cout << "Jumlah Elemen (n): " << n << endl;
    cout << "Nilai Minimum: " << minVal << endl;
    cout << "Indeks Minimum: " << minIdx << endl;

    return 0;
}