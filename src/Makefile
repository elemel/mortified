PLATFORM := mac

BOX2D_INCLUDE_DIR := ../ext/Box2D/include
BOX2D_LIB_DIR := ../ext/Box2D/lib
BOOST_INCLUDE_DIR := ../ext/boost/include
RAPIDXML_INCLUDE_DIR := ../ext/rapidxml/include
SDL_INCLUDE_DIR := ../ext/SDL/include
SDL_LIB_DIR := ../ext/SDL/lib

ifeq ($(PLATFORM),linux)
	OPENGL_LDFLAGS := -lGL
endif
ifeq ($(PLATFORM),mac)
	OPENGL_LDFLAGS := -framework OpenGL
endif

SRC_DIRS := $(shell find . -type d)
SRCS := $(shell find . -type f -name '*.cpp')
DEPS := $(SRCS:.cpp=.d)
OBJS := $(SRCS:.cpp=.o)

CPPFLAGS := \
	-MMD \
	$(addprefix -I,$(SRC_DIRS)) \
	-I$(BOX2D_INCLUDE_DIR) \
	-I$(BOOST_INCLUDE_DIR) \
	-I$(RAPIDXML_INCLUDE_DIR) \
	-I$(SDL_INCLUDE_DIR)
CXXFLAGS := -g -Wall -Wextra -Werror
LDFLAGS := \
	-L$(BOX2D_LIB_DIR) -lBox2D \
	-L$(SDL_LIB_DIR) -lSDL -lSDL_image -lSDL_ttf \
	-framework OpenGL

all: mortified

mortified: $(OBJS)
	g++ -o mortified $(OBJS) $(LDFLAGS)

clean:
	rm -f mortified $(DEPS) $(OBJS)

.PHONY: all clean

-include $(DEPS)
