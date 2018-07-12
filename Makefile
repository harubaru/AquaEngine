CXX = clang++ -target i686-pc-windows-gnu
CC = clang -target i686-pc-windows-gnu
LD = clang++ -target i686-pc-windows-gnu

#CXX = g++
#CC  = gcc
#LD  = g++

INCLUDE_PATHS = -IC:./dependencies/includes -I/usr/include/freetype2
LIBRARY_PATHS = -LC:./dependencies/libs

C_COMPILER_FLAGS = -I./include -O2 $(INCLUDE_PATHS)
CXX_COMPILER_FLAGS = -std=c++14 -I./include -O2 -Wall -Wextra $(INCLUDE_PATHS)

BINFOLDER = ./bin

include ./src/Makefile

ifeq ($(OS), Windows_NT)
	BINARY = aquaengine
	LIBRARIES = -lpthread -lSDl2 -lglew32 -lopengl32 -lassimp -lfreetype -lopenal32 -logg -lvorbis -lvorbisfile
	LINKER_FLAGS = -DDLL_BUILD $(LIBRARIES) -shared -Wl,--out-implib=$(BINFOLDER)/lib$(BINARY).a

	LDMSG = LD $(BINARY)
	CLEANMSG = rm -rf OBJS
	CXXMSG = CXX $<
	CCMSG = CC $<
else
	UNAME := $(shell uname -s)
	ifeq ($(UNAME), Linux)
		LINKER_FLAGS   = -lGL -lGLEW -lSDL2 -lassimp -lfreetype
		BINARY = aquaengine
	endif
endif

all: $(OBJS)
	@echo $(LDMSG)
	$(LD) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(BINFOLDER)/$(BINARY).dll
	
test:
	windres ./src/icon.rc -O coff -o ./src/icon.res
	$(CXX) $(CXX_COMPILER_FLAGS) -c ./src/main.cpp -o ./src/main.o
	$(LD) ./src/main.o ./src/icon.res $(INCLUDE_PATHS) $(LIBRARY_PATHS) -L./bin -o $(BINFOLDER)/test.exe $(LIBRARIES) -laquaengine

%.o: %.cpp
	@echo $(CXXMSG)
	$(CXX) $(CXX_COMPILER_FLAGS) -c $< -o $@

%.o: %.c
	@echo $(CCMSG)
	$(CC) $(C_COMPILER_FLAGS) -c $< -o $@

.PHONY : clean

clean:
	rm -rf $(OBJS) ./src/main.o

$(V).SILENT: