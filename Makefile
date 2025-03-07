.PHONY: build clean

RPI_PATH = "/run/media/frerf/RP2350/"

build:
	mkdir -p build && \
	cd build && \
	cmake .. && \
	make && \
	if [ -d $(RPI_PATH) ]; then \
		cp tactom-firmware.uf2 $(RPI_PATH); \
	fi

clean:
	rm -fr ./build
