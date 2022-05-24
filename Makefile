CC = gcc
CFLAGS = -Wall -g -I ./src -std=gnu11 
OBJS = s1

all: $(OBJS)

s1: src/s1.c src/gen_js.c src/gen_s1.c src/gen_dart.c src/gen_py.c
	$(CC) $(CFLAGS) $^ -o $@

run: $(OBJS)
	./s1 prog/hello.s1 -o out/hello.py
	python3 out/hello.py

test: $(OBJS)
	./cj2js.sh

clean:
	rm -f $(OBJS)
