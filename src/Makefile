CC="g++"
CCFLAGS="-g"
libName="libmraa.so"
hasLibrary=$(shell if test -f "${LIBRARY_PATH}/${libName}"; then echo "true"; else echo "false"; fi)

default: main.cpp
	@echo "LIBRARY_PATH=$(LIBRARY_PATH)"
	@echo "libName=${libName}"
	@echo "hasLibrary=${hasLibrary}"
	$(CC) $(CCFLAGS) $^ -l mraa -o ../dist/wow

cp:
	scp -r ./ root@10.0.0.5:~/everyone-say-wow/src/

watch:
	while true; do \
		echo "\nmake" && \
		make && \
		echo "\nscp" && \
		make cp && \
		echo "\n" ; \
		inotifywait -qr -e modify -e move -e create -e delete . ; \
	done
