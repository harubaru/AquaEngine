
INCLUDE_PATHS = -IC:./dependencies/includes -I/usr/include/freetype2
LIBRARY_PATHS = -LC:./dependencies/libs

C_COMPILER_FLAGS = -ggdb -I./include -O2 -Wall -Wextra -fPIC $(INCLUDE_PATHS)
CXX_COMPILER_FLAGS = -ggdb -std=c++14 -I./include -O2 -Wall -Wextra -fPIC $(INCLUDE_PATHS)

BINFOLDER = ./bin

include ./src/Makefile

ifeq ($(OS), Windows_NT)
	CXX = clang++ -target i686-pc-windows-gnu
	CC = clang -target i686-pc-windows-gnu
	LD = clang++ -target i686-pc-windows-gnu
	WINDRES = windres ./src/icon.rc -O coff -o ./src/icon.res
	RES = ./src/icon.res

	BINARY = aquaengine
	EXTENSION = dll
	TESTBINARY = test.exe
	LIBRARIES = -lpthread -lSDl2 -lopengl32 -lassimp -lfreetype -lopenal32 -logg -lvorbis -lvorbisfile
	LINKER_FLAGS = -DDLL_BUILD $(LIBRARIES) -shared -Wl,--out-implib=$(BINFOLDER)/lib$(BINARY).a

	LDMSG = LD $(BINARY)
	CLEANMSG = rm -rf OBJS
	CXXMSG = CXX $<
	CCMSG = CC $<
else
	UNAME := $(shell uname -s)
	ifeq ($(UNAME), Linux)
		CXX = clang++
		CC = clang
		LD = clang++
		WINDRES = 
		RES = 

		BINARY = aquaengine
		EXTENSION = so
		TESTBINARY = test
		LIBRARIES =  -lpthread -lGL -lSDL2 -lassimp -lfreetype -lopenal -logg -lvorbis -lvorbisfile
		LINKER_FLAGS   = -DDLL_BUILD $(LIBARIES) -shared -Wl,-soname,./lib$(BINARY).$(EXTENSION)

		LDMSG = "LD $(BINARY)"
		CLEANMSG = "rm -rf OBJS"
		CXXMSG = "CXX $<"
		CCMSG = "CC $<"
	endif
endif

all: $(OBJS)
	@echo $(LDMSG)
	$(LD) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(LINKER_FLAGS) -o lib$(BINARY).$(EXTENSION)
	mv lib$(BINARY).$(EXTENSION) ./$(BINFOLDER)
	
test:
	$(WINDRES)
	$(CXX) $(CXX_COMPILER_FLAGS) -c ./src/main.cpp -o ./src/main.o
	$(LD) ./src/main.o $(RES) $(INCLUDE_PATHS) $(LIBRARY_PATHS) -L$(BINFOLDER) -o $(BINFOLDER)/$(TESTBINARY) $(LIBRARIES) -l$(BINARY)

%.o: %.cpp
	@echo $(CXXMSG)
	$(CXX) $(CXX_COMPILER_FLAGS) -c $< -o $@

%.o: %.c
	@echo $(CCMSG)
	$(CC) $(C_COMPILER_FLAGS) -c $< -o $@

%.res: %.rc
	@echo $(RCMSG)

.PHONY : clean

clean:
	rm -rf $(OBJS) ./src/main.o

$(V).SILENT: