CC = gcc
CFLAGS = -Wall -Wno-unused-function -g -I ./src -std=gnu11 
OBJS = s1 vm1

all: $(OBJS)

s1: src/s1.c src/gen_js.c src/gen_s1.c src/gen_dart.c src/gen_py.c src/gen_ir.c
	$(CC) $(CFLAGS) $^ -o $@

vm1: src/vm/vm1.c
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
test-dart: $(OBJS)
	chmod +x ./dart_test.sh
	chmod +x ./dart_run.sh
	./dart_test.sh
test-ir: $(OBJS)
	chmod +x ./ir_test.sh
	chmod +x ./ir_run.sh
	./ir_test.sh

test-flutter: $(OBJS)
	(./s1 ./prog/flutter/home_page.s1 -o ./out/flutter/lib/home_page.dart)
	(cd ./out/flutter && flutter run -d chrome)

clean:
	rm -f $(OBJS)
