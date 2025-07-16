#include <iostream>
#include <cstdlib>      
#include <ctime>        
#include <algorithm>    
#include <chrono>

using namespace std;

// Generate random array of given size
void generateRandomArray(int arr[], int size, int minVal = 1, int maxVal = 100) {
    for (int i = 0; i < size; i++) {
        arr[i] = minVal + rand() % (maxVal - minVal + 1);
    }
}

// Display array
void displayArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << "\n";
}


//Binary Search
int binarySearch(int arr[], int L, int R, int x) {
    if (L > R)
        return -1;

    int M = L + (R - L) / 2;

    if (arr[M] == x)
        return M;
    else if (arr[M] < x)
        return binarySearch(arr, M + 1, R, x);
    else
        return binarySearch(arr, L, M - 1, x);
}
//exponential search
int recursiveExponentialSearch(int arr[], int n, int x, int i) {
    if (i >= n || arr[i] > x) {
        int low = i / 2;
        int high = min(i, n - 1);
        return binarySearch(arr, low, high, x);
    }

    if (arr[i] == x)
        return i;

    return recursiveExponentialSearch(arr, n, x, i * 2);
}

int exponentialSearch(int arr[], int n, int x) {
    if (arr[0] == x)
        return 0;
    return recursiveExponentialSearch(arr, n, x, 1);
}

// Quick Sort
int partition(int arr[], int low, int high) {
    int pivotIndex = low + rand() % (high - low + 1);
    swap(arr[pivotIndex], arr[high]);

    int pivotValue = arr[high];
    int i = low;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivotValue) {
            swap(arr[i], arr[j]);
            i++;
        }
    }

    swap(arr[i], arr[high]);
    return i;
}

void quicksort_recursion(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quicksort_recursion(arr, low, pivotIndex - 1);
        quicksort_recursion(arr, pivotIndex + 1, high);
    }
}

void quicksort(int arr[], int length) {
    quicksort_recursion(arr, 0, length - 1);
}

// Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(int arr[], int length) {
    mergeSort(arr, 0, length - 1);
}

int main() {
    srand(time(0)); // Seed random generator

    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    if (size <= 0) {
        cout << "Invalid size entered. Exiting.\n";
        return 1;
    }

    int* original = new int[size];
    generateRandomArray(original, size);

    cout << "\nOriginal Array:\n";
    displayArray(original, size);

    int* arrQuick = new int[size];
    int* arrMerge = new int[size];
    copy(original, original + size, arrQuick);
    copy(original, original + size, arrMerge);

    auto startQuick = chrono::high_resolution_clock::now();
    quicksort(arrQuick, size);
    auto endQuick = chrono::high_resolution_clock::now();
    auto timeQuick = chrono::duration_cast<chrono::nanoseconds>(endQuick - startQuick).count();

    cout << "\nSorted Array (Quick Sort):\n";
    displayArray(arrQuick, size);
    cout << "Time taken by Quick Sort: " << timeQuick << " nanoseconds\n";

    auto startMerge = chrono::high_resolution_clock::now();
    mergeSort(arrMerge, size);
    auto endMerge = chrono::high_resolution_clock::now();
    auto timeMerge = chrono::duration_cast<chrono::nanoseconds>(endMerge - startMerge).count();

    cout << "\nSorted Array (Merge Sort):\n";
    displayArray(arrMerge, size);
    cout << "Time taken by Merge Sort: " << timeMerge << " nanoseconds\n";

    int x;
    cout << "\nEnter value to search using Binary and Exponential Search: ";
    cin >> x;

    cout << "\nNote: Search indices refer to the sorted Quick Sort array.\n";

    // Binary Search
    auto startBinary = chrono::high_resolution_clock::now();
    int indexBinary = binarySearch(arrQuick, 0, size - 1, x);
    auto endBinary = chrono::high_resolution_clock::now();
    auto timeBinary = chrono::duration_cast<chrono::nanoseconds>(endBinary - startBinary).count();

    cout << "\nBinary Search Result:\n";
    if (indexBinary != -1)
        cout << "Found at index " << indexBinary << "\n";
    else
        cout << "Not Found\n";
    cout << "Time taken: " << timeBinary << " nanoseconds\n";

    auto startExpo = chrono::high_resolution_clock::now();
    int indexExpo = exponentialSearch(arrQuick, size, x);
    auto endExpo = chrono::high_resolution_clock::now();
    auto timeExpo = chrono::duration_cast<chrono::nanoseconds>(endExpo - startExpo).count();

    cout << "\nExponential Search Result:\n";
    if (indexExpo != -1)
        cout << "Found at index " << indexExpo << "\n";
    else
        cout << "Not Found\n";
    cout << "Time taken: " << timeExpo << " nanoseconds\n";

    delete[] original;
    delete[] arrQuick;
    delete[] arrMerge;

    return 0;
}
