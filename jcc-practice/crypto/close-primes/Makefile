IMAGE := jcc-practice-close-primes
PORT  := 9101

build:
	docker build -t $(IMAGE) .

start: build
	docker run -d --rm -p $(PORT):9101 --name $(IMAGE) $(IMAGE)

stop:
	-docker stop $(IMAGE)

restart: stop start

connect:
	nc localhost $(PORT)
