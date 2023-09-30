GENERATES = *.o *.a *.so *.test prog prog-a prog-so README
CFLAGS=-Wall -fPIC
LIBRARY_DEPS = fun.o const.o

all:    README prog prog-a prog-so

test: prog prog-a prog-so
	./prog > prog.test 2>&1
	./prog-a > prog_a.test 2>&1
	./prog-so > prog_so.test 2>&1
	
	./prog 1 > prog_1.test 2>&1
	./prog-a 1 > prog_a_1.test 2>&1
	./prog-so 1 > prog_so_1.test 2>&1
	
	./prog 1 2 3 > prog_3.test 2>&1
	./prog-a 1 2 3 > prog_a_3.test 2>&1
	./prog-so 1 2 3 > prog_so_3.test 2>&1
	
	diff3 prog.test prog_a.test prog_so.test || true
	diff3 prog_1.test prog_a_1.test prog_so_1.test || true
	diff3 prog_3.test prog_a_3.test prog_so_3.test || true

prog:   const.o fun.o prog.o

prog-a: prog.o liboutput_static.a
	$(CC) -L. $< -loutput_static -o $@

prog-so: prog.o liboutput.so
	$(CC) -Wl,-rpath=$(shell pwd) -L. $< -loutput -o $@

liboutput_static.a: $(LIBRARY_DEPS)
	ar -rcs $@ $^

liboutput.so: $(LIBRARY_DEPS)
	$(CC) -shared $^ -o $@

fun.o: outlib.h

README: prog
	./$< 2> $@

clean:
	rm -rf $(GENERATES)
