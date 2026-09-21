FROM ubuntu:22.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    gcc libc6-dev socat \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /chall
COPY chall.c .
COPY flag.txt /flag

RUN gcc -o chall chall.c -fno-stack-protector -no-pie -m64 \
    && chmod 444 /flag \
    && chmod 755 /chall/chall

EXPOSE 9002
CMD ["socat", "TCP-LISTEN:9002,reuseaddr,fork", "EXEC:/chall/chall"]
