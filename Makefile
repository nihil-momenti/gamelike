CC  = gcc
CXX = g++

ORIGINAL_CFLAGS   := $(CFLAGS)
ORIGINAL_CPPFLAGS := $(CPPFLAGS)

CFLAGS = -Wall -pedantic

CFLAGS += -g
CFLAGS += -O3
#CFLAGS += -stdlib=libc++
CFLAGS += -MD -MP -MF .dep/$(subst /,-,$@).d
CFLAGS += $(ORIGINAL_CFLAGS)
CFLAGS += -iquote$(abspath ./src)
#CFLAGS += -I/usr/local/include/c++/v1

SDL_CFLAGS += $(shell sdl2-config --cflags)

CPPFLAGS = $(CFLAGS) $(ORIGINAL_CPPFLAGS)

SDL_LDFLAGS += $(shell sdl2-config --static-libs)

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

all: src/GL_bindings.hpp $(PROJECT)
rebuild: clean all


$(PROJECT): $(OBJECTS:src/%=build/%.o)
	$(CXX) $(CPPFLAGS) $(SDL_CFLAGS) -o $@ $^ $(LDFLAGS) $(SDL_LDFLAGS)


src/GL_bindings.hpp src/GL_bindings.cpp: src/GL_bindings.rb
	ruby src/GL_bindings.rb


build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) -std=gnu99 $(CFLAGS) $(SDL_CFLAGS) -o $@ -c $<


build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -std=c++0x $(CPPFLAGS) $(SDL_CFLAGS) -o $@ -c $<


clean:
	rm -rf build/*
	rm -rf .dep/*
	rm -rf src/GL_bindings.hpp src/GL_bindings.cpp


.PRECIOUS: build/%.o
.PHONY: all rebuild clean

# Include the dependency files, should be the last of the makefile
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)
