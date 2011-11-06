ROOT_DIR = $(shell cd ../../.. && pwd)

install.made: build.made
	cd SDL_image && make install
	touch install.made

build.made: clean.made
	cd SDL_image && make
	touch build.made

clean.made: configure.made
	cd SDL_image && make clean
	touch clean.made

configure.made: clone.made
	cd SDL_image && sh autogen.sh && \
		./configure \
			--enable-imageio=no \
			--enable-jpg-shared=no --enable-png-shared=no --enable-tif-shared=no \
			--prefix=$(ROOT_DIR)/ext/SDL \
			CPPFLAGS=-I/usr/X11/include LDFLAGS=-L/usr/X11/lib
	touch configure.made

clone.made:
	rm -fr SDL_image
	hg clone http://hg.libsdl.org/SDL_image SDL_image
	touch clone.made

clean:
	rm -f *.made
	rm -fr SDL_image
