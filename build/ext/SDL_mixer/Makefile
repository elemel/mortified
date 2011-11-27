ROOT_DIR = $(shell cd ../../.. && pwd)

install.made: build.made
	cd SDL_mixer && make install
	touch install.made

build.made: clean.made
	cd SDL_mixer && make
	touch build.made

clean.made: configure.made
	cd SDL_mixer && make clean
	touch clean.made

configure.made: clone.made
	cd SDL_mixer && sh autogen.sh && \
		./configure --prefix=$(ROOT_DIR)/ext/SDL --enable-music-ogg-shared=no --with-sdl-prefix=$(ROOT_DIR)/ext/SDL
	touch configure.made

clone.made:
	rm -fr SDL_mixer
	hg clone http://hg.libsdl.org/SDL_mixer SDL_mixer
	touch clone.made

clean:
	rm -f *.made
	rm -fr SDL_mixer
