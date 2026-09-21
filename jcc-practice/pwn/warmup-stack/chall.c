/*
 * warmup-stack — latihan Attack-Defense JCC
 * Kategori   : Binary Exploitation (pwn)
 * Kesulitan  : Easy (warmup)
 *
 * Catatan: fungsi baca_input() di bawah ini SENGAJA meniru perilaku
 * gets() klasik (baca sampai newline, TANPA validasi panjang) - kelas
 * bug yang sama seperti gets(), yang di glibc modern sudah dihapus
 * total dari library sehingga tidak bisa dipakai langsung untuk demo.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void win() {
    char buf[256];
    FILE *f = fopen("/flag", "r");
    if (!f) {
        puts("flag tidak ditemukan, hubungi admin.");
        exit(1);
    }
    if (fgets(buf, sizeof(buf), f)) {
        printf("%s", buf);
    }
    fclose(f);
    exit(0);
}

/* Baca input tanpa batas panjang - TIDAK AMAN, sengaja untuk latihan */
void baca_input(char *buf) {
    int c;
    int i = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        buf[i++] = (char) c;
    }
    buf[i] = '\0';
}

void vuln() {
    char buf[64];
    puts("=== Selamat datang di Warmup PWN JCC ===");
    printf("Masukkan nama kamu: ");
    fflush(stdout);
    baca_input(buf);
    printf("Halo, %s!\n", buf);
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    vuln();
    puts("Sampai jumpa!");
    return 0;
}
