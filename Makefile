CC = g++
C = gcc
LD = g++

INCLUDE_PATHS = -IC:./dependencies/includes
LIBRARY_PATHS = -LC:./dependencies/libs

C_COMPILER_FLAGS = -I./include -O3 $(INCLUDE_PATHS)
CXX_COMPILER_FLAGS = -std=c++14 -I./include -O3 -Wall -Wextra -Werror $(INCLUDE_PATHS)
LINKER_FLAGS   = -lmingw32 -lSDL2main -lSDl2 -lglew32 -lopengl32 -lassimp.dll

BINARY = AquaGL.exe
BINFOLDER = ./bin

include ./src/Makefile

all: $(BINARY)

$(BINARY): $(OBJS)
	$(LD) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(BINFOLDER)/$(BINARY)

%.o: %.cpp
	$(CC) $(CXX_COMPILER_FLAGS) -c $< -o $@

%.o: %.c
	$(C) $(C_COMPILER_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BINFOLDER)/$(BINARY)
