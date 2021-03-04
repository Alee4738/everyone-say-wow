default: static shared

static: multiply.c power.c
	gcc -c $^
	mkdir -p ../bin/static
	ar rcs ../bin/static/libmymath.a multiply.o power.o

shared: multiply.c power.c
	gcc -fPIC -c $^
	mkdir -p ../bin/shared
	gcc -shared multiply.o power.o -o ../bin/shared/libmymath.so

clean:
	rm -rf *.o ../bin/*
