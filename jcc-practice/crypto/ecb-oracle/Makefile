IMAGE := jcc-practice-ecb-oracle
PORT  := 9102

build:
	docker build -t $(IMAGE) .

start: build
	docker run -d --rm -p $(PORT):9102 --name $(IMAGE) $(IMAGE)

stop:
	-docker stop $(IMAGE)

restart: stop start

connect:
	nc localhost $(PORT)
