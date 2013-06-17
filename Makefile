CC  = clang
CXX = clang++

CC_ARGS = ~/.vim/bundle/clang_complete/bin/cc_args.py

CC := $(if $(shell ls $(CC_ARGS)),$(CC_ARGS) $(CC),$(CC))
CXX := $(if $(shell ls $(CC_ARGS)),$(CC_ARGS) $(CXX),$(CXX))

ORIGINAL_CFLAGS   := $(CFLAGS)
ORIGINAL_CPPFLAGS := $(CPPFLAGS)

CFLAGS = -Wall -pedantic

CFLAGS += -g
#CFLAGS += -O4
CFLAGS += -MD -MP -MF .dep/$(subst /,-,$@).d
CFLAGS += $(ORIGINAL_CFLAGS)
CFLAGS += -iquote$(abspath ./src)

NEW_SDL_FOLDER = /Users/nemo157/sources/SDL/install

SDL_CFLAGS += $(shell pkg-config --cflags sdl2)
NEW_SDL_CFLAGS += -I$(NEW_SDL_FOLDER)/SDL2 -D_THREAD_SAFE

CPPFLAGS = $(CFLAGS) $(ORIGINAL_CPPFLAGS)

SDL_LDFLAGS += $(shell pkg-config --libs --static sdl2)
NEW_SDL_LDFLAGS += -L$(NEW_SDL_FOLDER)/lib $(NEW_SDL_FOLDER)/libSDL2.a -lm -liconv -Wl,-framework,OpenGL -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,AudioUnit

-include local.mk

###############################################################################

C_FILES =  $(wildcard src/*.c)
C_FILES += $(wildcard src/*/*.c)

CPP_FILES =  $(wildcard src/*.cpp)
CPP_FILES += $(wildcard src/*/*.cpp)
CPP_FILES += src/GL_bindings.cpp

OBJECTS = $(C_FILES:.c=) $(CPP_FILES:.cpp=)

PROJECT = gamelike

###############################################################################

all: src/GL_bindings.hpp $(PROJECT)-optimized $(PROJECT)
rebuild: clean all


$(PROJECT): $(OBJECTS:src/%=build/%.o)
	$(CXX) $(CPPFLAGS) $(SDL_CFLAGS) -o $@ $^ $(LDFLAGS) $(SDL_LDFLAGS)

$(PROJECT)-optimized: $(OBJECTS:src/%=build/%-optimized.o)
	$(CXX) $(CPPFLAGS) $(SDL_CFLAGS) -o $@ $^ $(LDFLAGS) $(SDL_LDFLAGS)

$(PROJECT)-new-sdl: $(OBJECTS:src/%=build/%-new-sdl.o) /Users/nemo157/sources/SDL/install/lib/libSDL2.a
	$(CXX) $(CPPFLAGS) $(NEW_SDL_CFLAGS) -o $@ $^ $(LDFLAGS) $(NEW_SDL_LDFLAGS)


src/GL_bindings.hpp src/GL_bindings.cpp: src/GL_bindings.rb
	ruby src/GL_bindings.rb


build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) -std=gnu99 $(CFLAGS) $(SDL_CFLAGS) -o $@ -c $<

build/%-optimized.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) -O4 -std=gnu99 $(CFLAGS) $(SDL_CFLAGS) -o $@ -c $<

build/%-new-sdl.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) -std=gnu99 $(CFLAGS) $(NEW_SDL_CFLAGS) -o $@ -c $<


build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -std=c++0x -Wno-variadic-macros $(CPPFLAGS) $(SDL_CFLAGS) -o $@ -c $<

build/%-optimized.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -O4 -std=c++0x -Wno-variadic-macros $(CPPFLAGS) $(SDL_CFLAGS) -o $@ -c $<

build/%-new-sdl.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -std=c++0x -Wno-variadic-macros $(CPPFLAGS) $(NEW_SDL_CFLAGS) -o $@ -c $<


clean:
	rm -rf build/*
	rm -rf .dep/*
	rm -rf src/GL_bindings.hpp src/GL_bindings.cpp


.PRECIOUS: build/%.o
.PHONY: all rebuild clean

# Include the dependency files, should be the last of the makefile
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)
