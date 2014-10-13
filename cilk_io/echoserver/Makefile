
# This is a minimal example of how to build a client app that uses the
# Cilk IO lib.

# Dynamic:
LIBPATHS= -L$(CILK_SRC)/build/ -L$(CILK_SRC)/deps/build/lib/
LIBS= -levent -lcilkrts

# Simple example
# echoserver.exe: echoserver.c
all:
	icc -I$(CILK_SRC)/include/ $(LIBPATHS) $(LIBS) echoserver.c -o echoserver.exe


run:
	export LD_LIBRARY_PATH=$(CILK_SRC)/build:$(CILK_SRC)/lib:$(LD_LIBRARY_PATH)
	./echoserver.exe
