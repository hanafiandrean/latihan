IMAGE := jcc-practice-fmtstr-auth
PORT  := 9002

build:
	docker build -t $(IMAGE) .

start: build
	docker run -d --rm -p $(PORT):9002 --name $(IMAGE) $(IMAGE)

stop:
	-docker stop $(IMAGE)

restart: stop start

compile:
	gcc -o chall chall.c -fno-stack-protector -no-pie -m64

connect:
	nc localhost $(PORT)
