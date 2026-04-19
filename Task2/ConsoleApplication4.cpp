#include <iostream>

using namespace std;

double calculateQ(double a[], double b[], int size) {
    double sum1 = 0.0;
    double sum2 = 0.0;
    double sum3 = 0.0;
    for (int i = 0; i < size; i++) {
        sum1 += a[i];
        sum2 += (a[i] * a[i] - b[i]);
        sum3 += (b[i] * a[i]);
    }
    return sum1 + sum2 + sum3;
}

int main() {
    double arrayA[6] = { 1.5, 1.3, 2.0, 3.6, 4.1, -1.6 };
    double arrayB[6] = { 2.1, 1.5, -1.0, 2.3, 4.3, 5.6 };
    int n = 6;
    double Q = calculateQ(arrayA, arrayB, n);
    cout << "The meaning of the expression Q = " << Q << endl;

    return 0;
}