HOST="root"
IP="192.168.0.150"

default: clean static

static: multiply.c power.c
	gcc -c $^
	mkdir -p ../bin/static
	ar rcs ../bin/static/libmymath.a multiply.o power.o

clean:
	rm -rf *.o ../bin/*
