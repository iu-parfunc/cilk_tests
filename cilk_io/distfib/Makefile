

# Dynamic:
CILK_SRC= ../../..
LIBPATHS= -L$(CILK_SRC)/build/ -L$(CILK_SRC)/lib/
LIBS= -levent -levent_pthreads -lcilkrts

# Simple example
# main.exe: main.c
all:
	icc -I$(CILK_SRC)/include/ $(LIBPATHS) $(LIBS) server.c -o server.exe
	icc -I$(CILK_SRC)/include/ $(LIBPATHS) $(LIBS) distfib.c -o distfib.exe


run: all
	export LD_LIBRARY_PATH=$(CILK_SRC)/build:$(CILK_SRC)/lib:$(LD_LIBRARY_PATH)
	./server.exe &
	./distfib.exe
	kill %1



clean:
	rm -rf *.o *.exe
