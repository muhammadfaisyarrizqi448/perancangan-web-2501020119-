#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateCSV(char *namafile, int jumlah) {
    FILE *fp = fopen(namafile, "w");
    if (!fp) {
        printf("Gagal membuat file %s\n", namafile);
        return;
    }

    // Mengisi file dengan angka acak antara 1 sampai 1.000.000
    for (int i = 0; i < jumlah; i++) {
        int angka = (rand() % 1000000) + 1;
        fprintf(fp, "%d\n", angka);
    }

    fclose(fp);
    printf("Berhasil membuat %s berisi %d data.\n", namafile, jumlah);
}

int main() {
    // Menginisialisasi random number generator
    srand(time(NULL));

    // Membuat tiga file sesuai kebutuhan modul praktikum
    generateCSV("data100.csv", 100);
    generateCSV("data1000.csv", 1000);
    generateCSV("data10000.csv", 10000);

    return 0;
}
