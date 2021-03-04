CC="gcc"
CCFLAGS="-g3"

HOST="root"
IP="192.168.0.150"

default: main.c
	@# link dynamic library (when running, need to have set LD_LIBRARY_PATH)
	$(CC) $(CCFLAGS) $^ -L ../lib/mraa/build/src -l mraa -o ../dist/wow

scp:
	make cp

cp:
	scp -r ./ $(HOST)@$(IP):~/everyone-say-wow/src/
	scp -r ../lib/mymath/src/ $(HOST)@$(IP):~/everyone-say-wow/lib/mymath/

watch:
	while true; do \
		echo "\nmake" && \
		make && \
		echo "\nscp" && \
		make cp && \
		echo "\n" ; \
		inotifywait -qr -e modify -e move -e create -e delete . ; \
	done

# a dummy hello world project

watchHello:
	while true; do \
		echo "\nmake" && \
		make hello && \
		echo "\nscp" && \
		make cp && \
		echo "\n" ; \
		inotifywait -qr -e modify -e move -e create -e delete . ; \
	done

hello: hello.c
	@# link static library
	gcc $(CCFLAGS) $^ -L ../lib/mymath/bin/static -l mymath -o ../dist/hello
	@# link dynamic library (when running, need to have set LD_LIBRARY_PATH)
	@# gcc $(CCFLAGS) $^ -L ../lib/mymath/bin/shared -l mymath -o ../dist/hello

world: world.cpp
	@# link static library
	g++ $(CCFLAGS) $^ -L ../lib/mymath/bin/static -l mymath -o ../dist/world
	@# link dynamic library (when running, need to have set LD_LIBRARY_PATH)
	@# g++ $(CCFLAGS) $^ -L ../lib/mymath/bin/shared -l mymath -o ../dist/world