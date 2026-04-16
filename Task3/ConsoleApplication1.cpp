#include <iostream>
#include <cstdlib> 
#include <ctime>   
#include <iomanip> 

using namespace std;

int main() {
    srand(time(NULL));

    int n, k;
    int variant = 12; 

    cout << "array size n: ";
    cin >> n;

    cout << "Number k: ";
    cin >> k;

    int** matrix = new int* [n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n];
    }

    int min_val = -10 - variant;
    int max_val = 10 + variant;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = min_val + rand() % (max_val - min_val + 1);
        }
    }

    cout << "\n Initial matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << matrix[i][j] << " ";
        }
        cout << "\n";
    }

    int max_element = matrix[0][0];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] > max_element) {
                max_element = matrix[i][j]; 
            }
        }
    }

    int count4 = 0;
    int count8 = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (i > j && i < n - 1 - j) {
                if (k != 0 && matrix[i][j] % k == 0) {
                    count4++;
                }
            }
            else if (i < j && i > n - 1 - j) {
                count8++;
                matrix[i][j] = max_element;
            }

        }
    }
    cout << "\nMax Value: " << max_element << "\n";
    cout << "Sector 4 (count of multiples of " << k << "): " << count4 << "\n";
    cout << "Sector 8 (count of elements): " << count8 << "\n";

    cout << "\nMatrix after replacement in sector 8:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(5) << matrix[i][j] << " ";
        }
        cout << "\n";
    }

    for (int i = 0; i < n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}