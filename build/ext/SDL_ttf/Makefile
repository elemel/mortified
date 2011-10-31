ROOT_DIR = $(shell cd ../../.. && pwd)

install.made: build.made
	cd SDL_ttf && make install
	touch install.made

build.made: configure.made
	cd SDL_ttf && make
	touch build.made

configure.made: clone.made
	cd SDL_ttf && sh autogen.sh && \
		./configure --prefix=$(ROOT_DIR)/ext/SDL --with-freetype-prefix=/usr/X11
	touch configure.made

clone.made:
	rm -fr SDL_ttf
	hg clone http://hg.libsdl.org/SDL_ttf SDL_ttf
	touch clone.made

clean:
	rm -f *.made
	rm -fr SDL_ttf
