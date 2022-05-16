CC = gcc
CFLAGS = -Wall -g -I ./src -std=gnu11 
OBJS = s1

all: $(OBJS)

s1: src/s1.c src/gen_js.c src/gen_s1.c
	$(CC) $(CFLAGS) $^ -o $@

run: $(OBJS)
	./cj prog/sum.cj -o out/sum.js
	deno run out/sum.js

test: $(OBJS)
	./cj2js.sh

clean:
	rm -f $(OBJS)
