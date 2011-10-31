ROOT_DIR = $(shell cd ../../.. && pwd)

install.made: build.made
	cd SDL_image && make install
	touch install.made

build.made: configure.made
	cd SDL_image && make
	touch build.made

configure.made: clone.made
	cd SDL_image && sh autogen.sh && \
		./configure --prefix=$(ROOT_DIR)/ext/SDL CPPFLAGS=-I/usr/X11/include LDFLAGS=-L/usr/X11/lib
	touch configure.made

clone.made:
	rm -fr SDL_image
	hg clone http://hg.libsdl.org/SDL_image SDL_image
	touch clone.made

clean:
	rm -f *.made
	rm -fr SDL_image
