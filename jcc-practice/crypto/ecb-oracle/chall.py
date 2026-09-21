#!/usr/bin/env python3
"""
ecb-oracle -- latihan Attack-Defense JCC
Kategori  : Cryptography
Kesulitan : Medium

Server menerima data (hex) dari kamu, menempelkannya di depan FLAG
rahasia, lalu meng-enkripsi gabungan tersebut dengan AES-ECB dan
mengembalikan ciphertext-nya (hex). ECB mengenkripsi tiap blok 16
byte secara independen dan deterministik -- manfaatkan sifat ini.
"""

import os
import sys
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad

KEY = os.urandom(16)
FLAG = open("flag.txt", "rb").read().strip()


def encrypt(user_input: bytes) -> bytes:
    data = user_input + FLAG
    cipher = AES.new(KEY, AES.MODE_ECB)
    return cipher.encrypt(pad(data, 16))


def main():
    print("=== ECB Oracle ===", flush=True)
    print("Kirim data dalam hex, akan dienkripsi bersama FLAG (ECB mode).", flush=True)
    while True:
        print("> ", end="", flush=True)
        line = sys.stdin.readline()
        if not line:
            break
        line = line.strip()
        if not line:
            continue
        try:
            data = bytes.fromhex(line)
        except ValueError:
            print("input harus hex valid", flush=True)
            continue
        if len(data) > 512:
            print("terlalu panjang", flush=True)
            continue
        ct = encrypt(data)
        print(ct.hex(), flush=True)


if __name__ == "__main__":
    main()
