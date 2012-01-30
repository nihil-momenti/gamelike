CC  = clang
CXX = clang++

ORIGINAL_CFLAGS   := $(CFLAGS)
ORIGINAL_CPPFLAGS := $(CPPFLAGS)

CFLAGS = -Wall -pedantic

CFLAGS += -g
#CFLAGS += -O4
CFLAGS += -MD -MP -MF .dep/$(subst /,-,$@).d
CFLAGS += $(shell pkg-config --cflags sdl2)
CFLAGS += $(ORIGINAL_CFLAGS)
CFLAGS += -iquote$(abspath ./src)

CPPFLAGS = $(CFLAGS) $(ORIGINAL_CPPFLAGS)

LDFLAGS += $(shell pkg-config --libs sdl2)

-include local.mk

###############################################################################

C_FILES =  $(wildcard src/*.c)
C_FILES += $(wildcard src/*/*.c)

CPP_FILES =  $(wildcard src/*.cpp)
CPP_FILES += $(wildcard src/*/*.cpp)
CPP_FILES += src/GL_bindings.cpp

OBJECTS = $(C_FILES:.c=.o) $(CPP_FILES:.cpp=.o)

PROJECT = gamelike

###############################################################################

all: src/GL_bindings.hpp $(PROJECT)
rebuild: clean all


$(PROJECT): $(OBJECTS:src/%=build/%)
	$(CXX) $(CPPFLAGS) -o $@ $^ $(LDFLAGS)


src/GL_bindings.hpp src/GL_bindings.cpp: src/GL_bindings.rb
	ruby src/GL_bindings.rb

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) -std=gnu99 $(CFLAGS) -o $@ -c $<


build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) -std=c++0x -Wno-variadic-macros $(CPPFLAGS) -o $@ -c $<


clean:
	rm -rf build/*
	rm -rf .dep/*
	rm -rf src/GL_bindings.hpp src/GL_bindings.cpp


.PRECIOUS: build/%.o
.PHONY: all rebuild clean

# Include the dependency files, should be the last of the makefile
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)
