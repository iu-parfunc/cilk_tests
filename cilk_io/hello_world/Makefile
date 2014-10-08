

# Dynamic:
LIBPATHS= -L$(CILK_SRC)/build/ -L$(CILK_SRC)/lib/
LIBS= -levent -lcilkrts

# Simple example
# main.exe: main.c
all:
	icc -I$(CILK_SRC)/include/ $(LIBPATHS) $(LIBS) main.c -o main.exe


run:
	export LD_LIBRARY_PATH=$(CILK_SRC)/build:$(CILK_SRC)/lib:$(LD_LIBRARY_PATH)
	./main.exe
