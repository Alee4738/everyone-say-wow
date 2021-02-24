CC="gcc"
CCFLAGS="-g3"

HOST="root"
IP="192.168.0.150"

default: main.c
	$(CC) $(CCFLAGS) $^ -l mraa -o ../dist/wow
	# $(CC) $(CCFLAGS) $^ -o ../dist/wow

hello: hello.c
	$(CC) $(CCFLAGS) $^ -L ../lib/mymath/bin/static -L ../lib/mymath/bin/shared -l mymath -o ../dist/hello

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

watchHello:
	while true; do \
		echo "\nmake" && \
		make hello && \
		echo "\nscp" && \
		make cp && \
		echo "\n" ; \
		inotifywait -qr -e modify -e move -e create -e delete . ; \
	done