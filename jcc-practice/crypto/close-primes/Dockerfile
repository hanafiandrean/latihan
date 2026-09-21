FROM python:3.11-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    socat \
    && rm -rf /var/lib/apt/lists/*

RUN pip install --no-cache-dir pycryptodome sympy

WORKDIR /chall
COPY gen.py .
COPY flag.txt .

EXPOSE 9101
CMD ["socat", "TCP-LISTEN:9101,reuseaddr,fork", "EXEC:python3 /chall/gen.py"]
