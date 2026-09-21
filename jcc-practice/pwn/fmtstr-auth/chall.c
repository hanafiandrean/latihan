/*
 * fmtstr-auth — latihan Attack-Defense JCC
 * Kategori   : Binary Exploitation (pwn)
 * Kesulitan  : Medium
 *
 * Bug: printf(buf) di menu 1 memakai input user langsung sebagai
 * format string. Manfaatkan ini untuk membaca/menulis memori proses.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int authenticated = 0;   /* <- target: ubah nilainya jadi != 0 */

void give_flag() {
    if (!authenticated) {
        puts("[!] Kamu belum ter-autentikasi.");
        return;
    }
    FILE *f = fopen("/flag", "r");
    char buf[256];
    if (!f) {
        puts("flag tidak ditemukan, hubungi admin.");
        return;
    }
    if (fgets(buf, sizeof(buf), f)) {
        printf("Flag: %s", buf);
    }
    fclose(f);
}

void menu() {
    printf("\n1. Kirim pesan\n2. Ambil flag\n3. Keluar\n> ");
    fflush(stdout);
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);

    char buf[256];
    int choice;

    puts("=== JCC Auth Panel ===");
    while (1) {
        menu();
        if (scanf("%d", &choice) != 1) break;
        getchar(); /* konsumsi newline sisa scanf */

        if (choice == 1) {
            printf("Pesan: ");
            fflush(stdout);
            if (!fgets(buf, sizeof(buf), stdin)) break;
            printf(buf);           /* <-- format string vulnerability */
        } else if (choice == 2) {
            give_flag();
        } else {
            break;
        }
    }
    puts("Sampai jumpa!");
    return 0;
}
