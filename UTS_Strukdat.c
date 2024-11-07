#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MahasiswaS 20

typedef struct Mahasiswa {
    char name[30];
    char gender;
    struct Mahasiswa* next;
} Mahasiswa;

typedef struct Circle {
    Mahasiswa* head;
    int count;
} Circle;

Circle circle = {NULL, 0};

Mahasiswa* createMahasiswa(char* name, char gender) {
    Mahasiswa* newMahasiswa = (Mahasiswa*)malloc(sizeof(Mahasiswa));
    strcpy(newMahasiswa->name, name);
    newMahasiswa->gender = gender;
    newMahasiswa->next = NULL;
    return newMahasiswa;
}

void addMahasiswa(Circle* circle, char* name, char gender) {
    if (circle->count >= MAX_MahasiswaS) {
        printf("Lingkaran api unggun penuh, tidak bisa tambah mahasiswa.\n");
        return;
    }

    Mahasiswa* newMahasiswa = NULL;

    if (strcmp(name, "Irsyad") == 0 || strcmp(name, "Arsyad") == 0) {
        char siblingName[30];
        if (strcmp(name, "Irsyad") == 0) {
            strcpy(siblingName, "Arsyad");
        } else {
            strcpy(siblingName, "Irsyad");
        }

        Mahasiswa* current = circle->head;
        if (current != NULL) {
            do {
                if (strcmp(current->name, siblingName) == 0) {
                    newMahasiswa = createMahasiswa(name, 'L');
                    if (current->next == circle->head) {
                        current->next = newMahasiswa;
                        newMahasiswa->next = circle->head;
                    } else {
                        Mahasiswa* temp = current->next;
                        current->next = newMahasiswa;
                        newMahasiswa->next = temp;
                    }
                    circle->count++;
                    printf("%s Telah Ditambahkan Setelah %s.\n", name, siblingName);
                    return;
                }
                current = current->next;
            } while (current != circle->head);
        }

        newMahasiswa = createMahasiswa(name, 'L');
        if (circle->head == NULL) {
            circle->head = newMahasiswa;
            newMahasiswa->next = newMahasiswa;
        } else {
            Mahasiswa* temp = circle->head;
            while (temp->next != circle->head) {
                temp = temp->next;
            }
            temp->next = newMahasiswa;
            newMahasiswa->next = circle->head;
        }
        circle->count++;
        printf("%s Telah ditambahkan. %s Akan ditambahkan nanti.\n", name, siblingName);
        return;
    }

    if (strcmp(name, "Cindy") != 0) {
        newMahasiswa = createMahasiswa(name, gender);
        if (circle->head == NULL) {
            circle->head = newMahasiswa;
            newMahasiswa->next = newMahasiswa;
        } else {
            Mahasiswa* temp = circle->head;
            while (temp->next != circle->head) {
                temp = temp->next;
            }
            temp->next = newMahasiswa;
            newMahasiswa->next = circle->head;
        }
        circle->count++;
        printf("%s Telah Di tambahkan.\n", name);
        return;
    }

    int femaleCount = 0;
    Mahasiswa* current = circle->head;
    Mahasiswa* prev = NULL;
    Mahasiswa* secondFemale = NULL;
    if (circle->head != NULL) {
        do {
            if (current->gender == 'P' && current->next->gender == 'P') {
                femaleCount = 2;
                prev = current;
                secondFemale = current->next;
                break;
            }
            current = current->next;
        } while (current != circle->head);
    }
    if (femaleCount == 2) {
        newMahasiswa = createMahasiswa("Cindy", 'P');
        prev->next = newMahasiswa;
        newMahasiswa->next = secondFemale;
        printf("Cindy Telah Ditambahkan diantara %s dan %s.\n", prev->name, secondFemale->name);
        circle->count++;
    } else {
        printf("Cindy Tidak mau bergabung ke dalam lingkaran.\n");
    }
}

void removeMahasiswa(Circle* circle, char* name) {
    if (circle->head == NULL) {
        printf("Lingkaran Kosong.\n");
        return;
    }
    Mahasiswa* current = circle->head;
    do {
        if (strcmp(current->name, "Cindy") == 0) {
            Mahasiswa* prev = current->next;
            Mahasiswa* next = current->next->next;
            if (prev->gender == 'P' && next->gender == 'P') {
                if (strcmp(name, prev->name) == 0 || strcmp(name, next->name) == 0) {
                    printf("Tidak memperbolehkan %s Untuk pergi.\n", name);
                    return;
                }
            }
        }
        current = current->next;
    } while (current != circle->head);

    Mahasiswa* temp = circle->head;
    Mahasiswa* prev = NULL;
    do {
        if (strcmp(temp->name, name) == 0) {
            if (prev == NULL) {
                if (circle->head == circle->head->next) {
                    free(circle->head);
                    circle->head = NULL;
                } else {
                    Mahasiswa* last = circle->head;
                    while (last->next != circle->head) {
                        last = last->next;
                    }
                    last->next = temp->next;
                    circle->head = temp->next;
                    free(temp);
                }
            } else {
                prev->next = temp->next;
                free(temp);
            }
            circle->count--;
            printf("%s Telah keluar lingkaran.\n", name);
            return;
        }
        prev = temp;
        temp = temp->next;
    } while (temp != circle->head);

    printf("Mahasiswa %s Tidak Di dalam lingkaran.\n", name);
}

void printCircle(Circle* circle) {
    if (circle->head == NULL) {
        printf("Lingkaran Kosong.\n");
        return;
    }

    Mahasiswa* temp = circle->head;
    do {
        printf("%s (%c) -> ", temp->name, temp->gender);
        temp = temp->next;
    } while (temp != circle->head);
    printf("\n");
}

int main() {
    int choice;
    char name[30];
    char gender;

    while (1) {
        printf("\n1. Tambah Mahasiswa\n");
        printf("2. Mahasiswa Keluar \n");
        printf("3. Tampilkan Lingkaran Mahasiswa\n");
        printf("4. Pisahkan Lingkaran\n");
        printf("5. Exit\n");
        printf("Masukkan Pilihan: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Masukkan Nama: ");
                scanf("%s", name);
                printf("Masukkan Gender (L/P): ");
                scanf(" %c", &gender);

                addMahasiswa(&circle, name, gender);
                break;

            case 2:
                printf("Masukkan Nama mahasiswa yg keluar: ");
                scanf("%s", name);
                removeMahasiswa(&circle, name);
                break;

            case 3:
                printCircle(&circle);
                break;

            case 5:
                printf("Exiting...\n");
                exit(0);
            case 4:
                splitByGender(&circle);
                break;
            default:
                printf("Pilihan Salah!\n");
        }
    }

    return 0;
}

void splitByGender(Circle* circle) {
    if (circle->head == NULL) {
        printf("Tidak ada mahasiswa di lingkaran.\n");
        return;
    }

    Circle maleCircle = { NULL, 0 };
    Circle femaleCircle = { NULL, 0 };

    Mahasiswa* current = circle->head;

    do {
        if (current->gender == 'L') {
            Mahasiswa* newMahasiswa = createMahasiswa(current->name, 'L');
            if (maleCircle.head == NULL) {
                maleCircle.head = newMahasiswa;
                newMahasiswa->next = newMahasiswa;
            } else {
                Mahasiswa* temp = maleCircle.head;
                while (temp->next != maleCircle.head) {
                    temp = temp->next;
                }
                temp->next = newMahasiswa;
                newMahasiswa->next = maleCircle.head;
            }
            maleCircle.count++;
        } else if (current->gender == 'P') {
            Mahasiswa* newMahasiswa = createMahasiswa(current->name, 'P');
            if (femaleCircle.head == NULL) {
                femaleCircle.head = newMahasiswa;
                newMahasiswa->next = newMahasiswa;
            } else {
                Mahasiswa* temp = femaleCircle.head;
                while (temp->next != femaleCircle.head) {
                    temp = temp->next;
                }
                temp->next = newMahasiswa;
                newMahasiswa->next = femaleCircle.head;
            }
            femaleCircle.count++;
        }
        current = current->next;
    } while (current != circle->head);

    printf("Linkaran Untuk laki- laki :\n");
    printCircle(&maleCircle);
    printf("Linkaran Untuk Perempuan :\n");
    printCircle(&femaleCircle);
}

