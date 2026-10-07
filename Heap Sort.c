#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Gunakan: %s [nama_file.csv]\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("Gagal membuka file %s\n", argv[1]);
        return 1;
    }

    int kapasitas = 15000;
    int *arr = malloc(kapasitas * sizeof(int));
    int n = 0;

    while (fscanf(fp, "%d", &arr[n]) == 1) {
        n++;
    }
    fclose(fp);

    clock_t mulai = clock();
    heapSort(arr, n);
    clock_t selesai = clock();

    double waktu = (double)(selesai - mulai) / CLOCKS_PER_SEC;
    printf("Waktu eksekusi Heap Sort (%s): %.6f detik\n", argv[1], waktu);

    free(arr);
    return 0;
}