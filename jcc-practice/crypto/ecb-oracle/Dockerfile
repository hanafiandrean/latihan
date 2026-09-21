FROM python:3.11-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    socat \
    && rm -rf /var/lib/apt/lists/*

RUN pip install --no-cache-dir pycryptodome

WORKDIR /chall
COPY chall.py .
COPY flag.txt .

EXPOSE 9102
CMD ["socat", "TCP-LISTEN:9102,reuseaddr,fork", "EXEC:python3 /chall/chall.py"]
