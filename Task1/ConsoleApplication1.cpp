#include <iostream>
#include <chrono>
#include <future>
#include <random>
#include <iomanip>

using namespace std;
using namespace std::chrono;
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
}

void countingSort(int arr[], int n) {
    int count[101] = { 0 };
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }
    int index = 0;
    for (int i = 0; i <= 100; i++) {
        while (count[i] > 0) {
            arr[index] = i;
            index++;
            count[i]--;
        }
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;

        int pi = i + 1;

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
void asyncQuickSort(int arr[], int low, int high, int depth = 0) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        int temp = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = temp;
        int pi = i + 1;
        if (depth < 3 && (high - low) > 10000) {
            future<void> left_task = async(launch::async, asyncQuickSort, arr, low, pi - 1, depth + 1);
            asyncQuickSort(arr, pi + 1, high, depth + 1);
            left_task.get();
        }
        else {
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
}
void copyArray(int source[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
}

int main() {
    int sizes[] = { 1000, 10000, 50000, 100000 };
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    cout << left << setw(15) << "Size (N)"
        << setw(18) << "Selection"
        << setw(18) << "Counting"
        << setw(18) << "Quick Sync"
        << setw(18) << "Quick Async" << endl;
    cout << string(85, '-') << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 100);

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int* original = new int[n];
        int* arr_test = new int[n];
        for (int i = 0; i < n; i++) {
            original[i] = distrib(gen);
        }

        double timeSelection = 0, timeCounting = 0, timeQuickSync = 0, timeQuickAsync = 0;
        copyArray(original, arr_test, n);
        auto start = high_resolution_clock::now();
        selectionSort(arr_test, n);
        auto stop = high_resolution_clock::now();
        timeSelection = duration_cast<microseconds>(stop - start).count() / 1000.0;
        copyArray(original, arr_test, n);
        start = high_resolution_clock::now();
        countingSort(arr_test, n);
        stop = high_resolution_clock::now();
        timeCounting = duration_cast<microseconds>(stop - start).count() / 1000.0;
        copyArray(original, arr_test, n);
        start = high_resolution_clock::now();
        quickSort(arr_test, 0, n - 1);
        stop = high_resolution_clock::now();
        timeQuickSync = duration_cast<microseconds>(stop - start).count() / 1000.0;
        copyArray(original, arr_test, n);
        start = high_resolution_clock::now();
        asyncQuickSort(arr_test, 0, n - 1);
        stop = high_resolution_clock::now();
        timeQuickAsync = duration_cast<microseconds>(stop - start).count() / 1000.0;
        cout << left << setw(15) << n
            << setw(18) << timeSelection
            << setw(18) << timeCounting
            << setw(18) << timeQuickSync
            << setw(18) << timeQuickAsync << endl;
        delete[] original;
        delete[] arr_test;
    }

    return 0;
}