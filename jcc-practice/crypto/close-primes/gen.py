#!/usr/bin/env python3
"""
close-primes -- latihan Attack-Defense JCC
Kategori  : Cryptography
Kesulitan : Easy-Medium

Setiap koneksi men-generate parameter RSA baru dengan p dan q yang
sengaja dibuat BERDEKATAN. Cari teknik faktorisasi klasik yang
memanfaatkan celah ini untuk memecah n menjadi p * q.
"""

import random
from sympy import nextprime
from Crypto.Util.number import getPrime, bytes_to_long

FLAG = open("flag.txt", "rb").read().strip()


def gen():
    bits = 512
    p = getPrime(bits)
    gap = random.randint(1, 5000) * 2   # p dan q sengaja berdekatan
    q = nextprime(p + gap)
    n = p * q
    e = 65537
    m = bytes_to_long(FLAG)
    c = pow(m, e, n)
    return n, e, c


def main():
    n, e, c = gen()
    print("=== Close Primes RSA ===")
    print(f"n = {n}")
    print(f"e = {e}")
    print(f"c = {c}")


if __name__ == "__main__":
    main()
