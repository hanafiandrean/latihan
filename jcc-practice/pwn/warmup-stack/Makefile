IMAGE := jcc-practice-warmup-stack
PORT  := 9001

build:
	docker build -t $(IMAGE) .

start: build
	docker run -d --rm -p $(PORT):9001 --name $(IMAGE) $(IMAGE)

stop:
	-docker stop $(IMAGE)

restart: stop start

compile:
	gcc -o chall chall.c -fno-stack-protector -no-pie -m64

connect:
	nc localhost $(PORT)
