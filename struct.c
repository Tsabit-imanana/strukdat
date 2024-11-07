#include <stdio.h>
#include <string.h>

// Definisikan struct untuk data mahasiswa
struct Mahasiswa {
    char nama[50];
    int umur;
    float nilai;
};

// Fungsi untuk mengisi data mahasiswa
void isiDataMahasiswa(struct Mahasiswa *mhs, const char *nama, int umur, float nilai) {
    strcpy(mhs->nama, nama); // Menggunakan pointer untuk mengisi nama
    mhs->umur = umur;        // Menggunakan pointer untuk mengisi umur
    mhs->nilai = nilai;      // Menggunakan pointer untuk mengisi nilai
}

// Fungsi untuk menampilkan data mahasiswa
void tampilkanDataMahasiswa(struct Mahasiswa *mhs) {
    printf("Nama: %s\n", mhs->nama);
    printf("Umur: %d\n", mhs->umur);
    printf("Nilai: %.2f\n", mhs->nilai);
}

int main() {
    // Membuat variabel struct Mahasiswa
    struct Mahasiswa mhs1;
    
    // Mengisi data mahasiswa dengan pointer
    isiDataMahasiswa(&mhs1, "Andi", 20, 85.5);
    
    // Menampilkan data mahasiswa
    tampilkanDataMahasiswa(&mhs1);
    
    return 0;
}
