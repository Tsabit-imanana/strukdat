#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct node {
    char nama[100];     // Array for storing names
    char jenis_kelamin; // L/P
    struct node *next;
};

// Function prototypes
void tambahMahasiswa(struct node **head);
void transverse(struct node *head);
void keluarLingkaran(struct node **head);
void pindahUrutan(struct node **head);
void pisahkanLingkaran(struct node *head);
void tampilkanUrutanBernyanyi(struct node *head);

// Variabel global untuk lingkaran pria dan wanita
struct node *headPria = NULL;
struct node *tailPria = NULL;

struct node *headWanita = NULL;
struct node *tailWanita = NULL;

int cindyDalamLingkaran = 0; // Variabel global untuk melacak status Cindy

int main() {
    struct node *head = NULL;
    int pilih;

    do {
        system("cls");
        printf("Masukkan pilihan:\n");
        printf("1. Tambah mahasiswa\n");
        printf("2. Keluar dari lingkaran\n");
        printf("3. Pindah urutan bernyanyi\n");
        printf("4. Tampilkan urutan bernyanyi\n");
        printf("5. Pisahkan lingkaran\n");
        printf("0. Keluar program\n");

        printf("MASUKKAN PILIHAN: ");
        fflush(stdin);
        scanf("%d", &pilih);

        if (pilih == 1) {
            tambahMahasiswa(&head);
        } else if (pilih == 2) {
            keluarLingkaran(&head);
        } else if (pilih == 3) {
            pindahUrutan(&head);
        } else if (pilih == 4) {
            tampilkanUrutanBernyanyi(head);
            getch();
        } else if (pilih == 5) {
            pisahkanLingkaran(head);
        } else if (pilih == 0) {
            printf("Keluar dari program.\n");
        } else {
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
            getch();
        }

    } while (pilih != 0);

    return 0;
}

void tambahMahasiswa(struct node **head) {
    char nama[100]; // Array for storing the name
    char jenis_kelamin;
    struct node *pNew = (struct node *)malloc(sizeof(struct node));

    system("cls");
    printf("Masukkan nama mahasiswa/i: ");
    scanf("%s", nama);
    printf("Jenis kelamin L/P: ");
    scanf(" %c", &jenis_kelamin); // Notice the space before %c

    // Cek jika mahasiswa yang ditambahkan adalah Cindy
    if (strcmp(nama, "Cindy") == 0 && cindyDalamLingkaran == 0) {
        // Cek jumlah mahasiswi dalam lingkaran
        struct node *pCur = *head;
        int jumlahMahasiswi = 0;

        if (pCur != NULL) { // Jika list tidak kosong
            do {
                if (pCur->jenis_kelamin == 'P') {
                    jumlahMahasiswi++; // Hitung mahasiswi
                }
                pCur = pCur->next;
            } while (pCur != *head);
        }

        // Pastikan ada setidaknya dua mahasiswi
        if (jumlahMahasiswi < 2) {
            printf("Cindy tidak dapat bergabung karena tidak ada cukup mahasiswi lainnya dalam lingkaran.\n");
            getch();
            return; // Keluar dari fungsi
        }

        cindyDalamLingkaran = 1; // Tandai Cindy sudah dalam lingkaran
    }

    if (pNew != NULL) {
        strcpy(pNew->nama, nama); // Copy the name to the new node
        pNew->jenis_kelamin = jenis_kelamin;

        if (*head == NULL) {
            pNew->next = pNew; // Point to itself (circular)
            *head = pNew;
        } else {
            struct node *pCur = *head;
            // Find the last node
            while (pCur->next != *head) {
                pCur = pCur->next;
            }
            pNew->next = *head; // Point to head
            pCur->next = pNew;  // Last node points to new node
        }

        // Menampilkan informasi tentang mahasiswa yang berhasil ditambahkan
        printf("Mahasiswa bernama %s dengan jenis kelamin %c berhasil ditambahkan.\n", pNew->nama, pNew->jenis_kelamin);
        getch();
    } else {
        printf("Alokasi memori gagal.\n");
        getch();
    }
}

void keluarLingkaran(struct node **head) {
    char nama[100];
    struct node *pCur, *ppre;

    system("cls");
    printf("Masukkan nama mahasiswa/i yang ingin keluar dari lingkaran: ");
    scanf("%s", nama);

    if (*head == NULL) {
        printf("List kosong, tidak ada mahasiswa.\n");
        getch();
        return;
    }

    pCur = *head;
    ppre = NULL;
    do {
        if (strcmp(pCur->nama, nama) == 0) {
            break;
        }
        ppre = pCur;
        pCur = pCur->next;
    } while (pCur != *head);

    if (strcmp(pCur->nama, nama) != 0) {
        printf("Mahasiswa dengan nama %s tidak ditemukan.\n", nama);
        getch();
        return;
    }

    // Jika node head yang dihapus
    if (pCur == *head) {
        if (pCur->next == *head) {
            // Jika hanya ada satu node
            free(pCur);
            *head = NULL;
        } else {
            struct node *tail = *head;
            while (tail->next != *head) {
                tail = tail->next;
            }
            *head = (*head)->next; // Ubah head ke node berikutnya
            tail->next = *head;    // Tail menunjuk ke head baru
            free(pCur);
        }
    } else {
        // Menghapus node dari tengah atau akhir
        ppre->next = pCur->next;
        free(pCur);
    }

    printf("%s berhasil keluar dari lingkaran.\n", nama);
    getch();
}

void pindahUrutan(struct node **head) {
    if (*head == NULL) {
        printf("Tidak ada mahasiswa yang bernyanyi.\n");
        getch();
        return;
    }

    // Tampilkan urutan mahasiswa saat ini sebelum pemindahan
    printf("Urutan mahasiswa saat ini sebelum pemindahan:\n");
    transverse(*head);

    char nama[100];
    printf("Masukkan nama mahasiswa/i yang ingin dipindahkan ke urutan pertama: ");
    scanf("%s", nama);

    struct node *pCur = *head;
    struct node *pPrev = NULL;
    int found = 0;

    // Mencari mahasiswa yang dipilih
    do {
        if (strcmp(pCur->nama, nama) == 0) {
            found = 1; // Mahasiswa ditemukan
            break;
        }
        pPrev = pCur;
        pCur = pCur->next;
    } while (pCur != *head);

    // Jika mahasiswa tidak ditemukan
    if (!found) {
        printf("Mahasiswa dengan nama %s tidak ditemukan dalam urutan.\n", nama);
        getch();
        return;
    }

    // Jika mahasiswa yang dipilih bukan head
    if (pCur != *head) {
        if (pPrev != NULL) {
            pPrev->next = pCur->next; // Hapus mahasiswa dari urutan saat ini
        }

        // Tambahkan mahasiswa yang dipilih ke depan
        struct node *tail = *head;
        while (tail->next != *head) {
            tail = tail->next; // Cari tail
        }
        tail->next = pCur;  // Tail sekarang menunjuk ke mahasiswa yang dipilih
        pCur->next = *head; // Mahasiswa yang dipilih menunjuk ke head baru
        *head = pCur;       // Update head
    }

    // Menampilkan urutan setelah pemindahan
    printf("Urutan bernyanyi setelah pemindahan:\n");
    transverse(*head);
    printf("Sekarang %s menjadi yang pertama.\n", (*head)->nama);

    getch();
}

void tampilkanUrutanBernyanyi(struct node *head) {
    if (head == NULL) {
        printf("Tidak ada mahasiswa yang bernyanyi.\n");
        return;
    }

    printf("Urutan bernyanyi:\n");
    transverse(head);
}

void transverse(struct node *head) {
    if (head == NULL) {
        printf("List kosong.\n");
        return;
    }

    struct node *pCur = head;
    do {
        printf("Nama: %s, Jenis Kelamin: %c\n", pCur->nama, pCur->jenis_kelamin);
        pCur = pCur->next;
    } while (pCur != head);
}

void pisahkanLingkaran(struct node *head) {
    if (head == NULL) {
        printf("List kosong, tidak ada mahasiswa.\n");
        getch();
        return;
    }

    struct node *pCur = head;
    do {
        struct node *newNode = (struct node *)malloc(sizeof(struct node));
        if (newNode == NULL) {
            printf("Alokasi memori gagal\n");
            getch();
            return;
        }
        strcpy(newNode->nama, pCur->nama);
        newNode->jenis_kelamin = pCur->jenis_kelamin;

        if (pCur->jenis_kelamin == 'L') {
            if (headPria == NULL) {
                headPria = newNode;
                newNode->next = newNode; // Circular
                tailPria = newNode;
            } else {
                tailPria->next = newNode;
                newNode->next = headPria;
                tailPria = newNode;
            }
        } else if (pCur->jenis_kelamin == 'P') {
            if (headWanita == NULL) {
                headWanita = newNode;
                newNode->next = newNode; // Circular
                tailWanita = newNode;
            } else {
                tailWanita->next = newNode;
                newNode->next = headWanita;
                tailWanita = newNode;
            }
        }

        pCur = pCur->next;
    } while (pCur != head);

    printf("Lingkaran berhasil dipisahkan:\n");
    printf("Mahasiswa:\n");
    transverse(headPria);
    printf("Mahasiswi:\n");
    transverse(headWanita);

    getch();
}
