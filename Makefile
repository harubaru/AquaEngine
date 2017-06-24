CC = g++
C = gcc
LD = g++

INCLUDE_PATHS = -IC:./dependencies/includes
LIBRARY_PATHS = -LC:./dependencies/libs

C_COMPILER_FLAGS = -I./include -O3 $(INCLUDE_PATHS)
CXX_COMPILER_FLAGS = -std=c++14 -I./include -O3 -Wall -Wextra -Werror $(INCLUDE_PATHS)
LINUX_LINKER_FLAGS   = -lSDL2 -lGLEW -lGL -lassimp
WIN32_LINKER_FLAGS   = -lmingw32 -lSDL2main -lSDl2 -lglew32 -lopengl32 -lassimp.dll

LINUX_BINARY = aquaengine
WIN32_BINARY = aquaengine.exe
BINFOLDER = ./bin

include ./src/Makefile

help:
	echo "{win32 | linux | clean}"

linux: $(LINUX_BINARY)

win32: $(WIN32_BINARY)

$(LINUX_BINARY): $(OBJS)
	$(LD) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINUX_LINKER_FLAGS) -o $(BINFOLDER)/$(LINUX_BINARY)
	chmod +x $(BINFOLDER)/$(LINUX_BINARY)

$(WIN32_BINARY): $(OBJS)
	$(LD) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(WIN32_LINKER_FLAGS) -o $(BINFOLDER)/$(WIN32_BINARY)

%.o: %.cpp
	$(CC) $(CXX_COMPILER_FLAGS) -c $< -o $@

%.o: %.c
	$(C) $(C_COMPILER_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
