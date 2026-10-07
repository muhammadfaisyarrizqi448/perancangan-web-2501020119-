#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RUN 32

// ==================== 1. COMPARISON SORTS ====================

// Insertion Sort
void insertionSortArr(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

// Heap Sort Helper
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

// Merge Sort Helper
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int *leftArr = (int *)malloc(n1 * sizeof(int));
    int *rightArr = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++) rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }
    while (i < n1) arr[k++] = leftArr[i++];
    while (j < n2) arr[k++] = rightArr[j++];

    free(leftArr);
    free(rightArr);
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Timsort
void timSort(int arr[], int n) {
    for (int i = 0; i < n; i += RUN) {
        insertionSortArr(arr, i, (i + RUN - 1 < n - 1) ? (i + RUN - 1) : (n - 1));
    }
    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);
            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
}


// ==================== 2. NON-COMPARISON SORTS ====================

// Counting Sort
void countingSort(int inputArray[], int size) {
    if (size <= 0) return;
    int max = inputArray[0];
    for (int i = 1; i < size; i++) {
        if (inputArray[i] > max) max = inputArray[i];
    }

    int *countArray = (int *)calloc(max + 1, sizeof(int));
    int *outputArray = (int *)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) countArray[inputArray[i]]++;
    for (int i = 1; i <= max; i++) countArray[i] += countArray[i - 1];
    for (int i = size - 1; i >= 0; i--) {
        outputArray[countArray[inputArray[i]] - 1] = inputArray[i];
        countArray[inputArray[i]]--;
    }
    for (int i = 0; i < size; i++) inputArray[i] = outputArray[i];

    free(countArray);
    free(outputArray);
}


// ==================== MAIN PROGRAM ====================

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Cara Penggunaan: %s [file_data.csv] [metode]\n", argv[0]);
        printf("Pilihan Metode: insertion, selection, heap, merge, timsort, counting\n");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Gagal membuka file %s\n", argv[1]);
        return 1;
    }

    int kapasitas = 15000; // Sesuaikan dengan ukuran maksimal data (misal 10.000)
    int *arr = (int *)malloc(kapasitas * sizeof(int));
    int n = 0;

    while (fscanf(fp, "%d", &arr[n]) == 1) {
        n++;
    }
    fclose(fp);

    clock_t mulai = clock();

    // Pilih algoritma berdasarkan argumen kedua
    if (strcmp(argv[2], "insertion") == 0) {
        insertionSortArr(arr, 0, n - 1);
    } else if (strcmp(argv[2], "selection") == 0) {
        selectionSort(arr, n);
    } else if (strcmp(argv[2], "heap") == 0) {
        heapSort(arr, n);
    } else if (strcmp(argv[2], "merge") == 0) {
        mergeSort(arr, 0, n - 1);
    } else if (strcmp(argv[2], "timsort") == 0) {
        timSort(arr, n);
    } else if (strcmp(argv[2], "counting") == 0) {
        countingSort(arr, n);
    } else {
        printf("Metode '%s' tidak dikenali!\n", argv[2]);
        free(arr);
        return 1;
    }

    clock_t selesai = clock();
    double waktu = (double)(selesai - mulai) / CLOCKS_PER_SEC;

    printf("Algoritma: %s | File: %s | Waktu Eksekusi: %.6f detik\n", argv[2], argv[1], waktu);

    free(arr);
    return 0;
}