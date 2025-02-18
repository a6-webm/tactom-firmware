.PHONY: build clean

build:
	mkdir -p build && \
	cd build && \
	cmake .. && \
	make

clean:
	rm -fr ./build
