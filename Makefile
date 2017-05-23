CC = g++
LD = g++

INCLUDE_PATHS = -IC:./dependencies/includes
LIBRARY_PATHS = -LC:./dependencies/libs

COMPILER_FLAGS = -std=c++14 -I./include -O3 -Wall -Wextra -Werror
LINKER_FLAGS   = -lmingw32 -lSDL2main -lSDl2 -lglew32 -lopengl32

BINARY = AquaGL.exe
BINFOLDER = ./bin

include ./src/Makefile

all: $(BINARY)

$(BINARY): $(OBJS)
	echo $(OBJS)
	$(LD) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o $(BINFOLDER)/$(BINARY)

%.o: %.cpp
	$(CC) $(COMPILER_FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BINFOLDER)/$(BINARY)

