# JCC Practice Pack — Pwn & Crypto

Paket latihan lokal buat persiapan Attack-Defense JCC. Empat challenge,
masing-masing punya source code, Dockerfile, dan Makefile bergaya
`make start/stop/restart` (mirip konvensi platform lomba).

## Prasyarat

- Docker & docker-compose
- `nc` (netcat) atau `pwntools` buat interaksi manual
- Python 3 + `pwntools`, `pycryptodome`, `sympy` kalau mau nulis exploit lokal
  (`pip install pwntools pycryptodome sympy`)

## Menjalankan semua challenge sekaligus

```bash
docker compose up --build -d
```

Atau satu-satu, masuk ke folder challenge lalu `make start`.

## Daftar Challenge

| Challenge | Kategori | Kesulitan | Port | Folder |
|---|---|---|---|---|
| warmup-stack | Pwn | Easy | 9001 | `pwn/warmup-stack` |
| fmtstr-auth | Pwn | Medium | 9002 | `pwn/fmtstr-auth` |
| close-primes | Crypto | Easy-Medium | 9101 | `crypto/close-primes` |
| ecb-oracle | Crypto | Medium | 9102 | `crypto/ecb-oracle` |

Connect ke tiap service: `nc localhost <port>`

---

### 1. warmup-stack (Pwn, Easy)

Program minta nama, lalu menampilkannya balik. Ada fungsi `win()` yang
membaca `/flag` tapi tidak pernah dipanggil dari alur program normal.

**Hint:** perhatikan fungsi pembaca input — apakah dia membatasi
panjang data yang ditulis ke buffer? Kalau tidak, buffer di stack bisa
"meluber" dan menimpa data lain, termasuk alamat kembali (return
address) fungsi. Cari offset-nya, lalu arahkan return address ke
alamat `win()` (`objdump -d chall | grep win`).

**Tools yang relevan:** `pwntools`, `gdb` + GEF/pwndbg, `objdump`.

### 2. fmtstr-auth (Pwn, Medium)

Ada menu dengan pilihan "Kirim pesan" dan "Ambil flag". Flag hanya
diberikan kalau variabel `authenticated` bernilai bukan 0 — tapi tidak
ada jalur normal di program yang mengubah nilainya.

**Hint:** perhatikan bagaimana pesan kamu ditampilkan balik ke layar.
Kalau input kamu diproses langsung sebagai *format string*, kamu bisa
membaca isi stack (`%p`, `%x`) dan bahkan menulis ke alamat memori
tertentu (`%n`). Cari alamat variabel `authenticated` lewat
`objdump -d chall` atau `nm chall`, lalu bangun payload write-nya.

**Tools yang relevan:** `pwntools` (`fmtstr_payload` sangat membantu),
`gdb` + GEF/pwndbg, `objdump`/`nm`.

### 3. close-primes (Crypto, Easy-Medium)

Server ngasih `n`, `e`, `c` — RSA standar. Tapi dua bilangan prima
penyusun `n` (p dan q) sengaja dibuat berdekatan nilainya.

**Hint:** kalau p dan q cukup dekat, `n = p*q` bisa difaktorkan tanpa
perlu brute-force penuh — ada teknik faktorisasi klasik yang
memanfaatkan `sqrt(n)` sebagai titik awal pencarian.

**Tools yang relevan:** Python + `gmpy2`/`sympy`, atau `RsaCtfTool`
buat cross-check.

### 4. ecb-oracle (Crypto, Medium)

Server nempelin FLAG di belakang data yang kamu kirim, lalu
mengenkripsi gabungannya pakai AES dalam mode ECB, dan mengembalikan
ciphertext-nya.

**Hint:** ECB mengenkripsi tiap blok 16-byte secara independen dan
deterministik — plaintext blok yang sama selalu menghasilkan
ciphertext blok yang sama. Kalau kamu bisa mengontrol berapa banyak
byte yang kamu kirim sebelum FLAG, kamu bisa "menggeser" satu byte
FLAG ke posisi yang bisa kamu tebak satu-persatu.

**Tools yang relevan:** Python + `pwntools`/`socket`, `pycryptodome`
buat eksperimen lokal.

---

## Progres belajar yang disarankan

1. Coba solve manual dulu tanpa lihat writeup apa pun — catat di mana
   kamu stuck.
2. Kalau lebih dari ~45 menit stuck, cari 1 keyword teknik yang
   relevan (bukan nama challenge-nya) dan baca konsepnya, bukan
   solusinya.
3. Setelah solve, tulis ulang exploit-nya dari nol tanpa lihat
   punyamu yang lama — ini yang bikin teknik nempel di kepala.
4. Kalau format ini udah lancar, coba ubah parameter (misal perkecil
   `gap` di `close-primes` biar makin gampang, atau perbesar biar
   makin susah) buat latihan variasi.

Kalau stuck total atau mau dicek pendekatan/exploit-nya, tinggal
tanya di chat — bisa dikasih hint bertahap tanpa langsung spoiler.
