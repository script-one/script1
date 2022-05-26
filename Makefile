CC = gcc
CFLAGS = -Wall -g -I ./src -std=gnu11 
OBJS = s1

all: $(OBJS)

s1: src/s1.c src/gen_js.c src/gen_s1.c src/gen_dart.c src/gen_py.c
	$(CC) $(CFLAGS) $^ -o $@

hello: $(OBJS)
	./s1 prog/hello.s1 -o out/hello.js
	deno run out/hello.js
	./s1 prog/hello.s1 -o out/hello.py
	python3 out/hello.py
	./s1 prog/hello.s1 -o out/hello.dart
	dart run out/hello.dart

test-js: $(OBJS)
	chmod +x ./js_test.sh
	chmod +x ./js_run.sh
	./js_test.sh
test-py: $(OBJS)
	chmod +x ./py_test.sh
	chmod +x ./py_run.sh
	./py_test.sh


clean:
	rm -f $(OBJS)
