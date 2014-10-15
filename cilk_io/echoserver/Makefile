
# This is a minimal example of how to build a client app that uses the
# Cilk IO lib.

# Dynamic:
CC = $(CONCURRENTCILK_CC)
CFLAGS = -fcilkplus
LIBPATHS= -L$(CILK_SRC)/build/ -L$(CILK_SRC)/deps/build/lib/
LIBS= -levent -levent_pthreads -lcilkrts -lpthread -ldl

# Simple example
# echoserver.exe: echoserver.c
all:
	$(CC) $(CFLAGS) -I$(CILK_SRC)/include/ $(LIBPATHS) $(LIBS) echoserver.c -o echoserver.exe


run:
	export LD_LIBRARY_PATH=$(CILK_SRC)/build:$(CILK_SRC)/lib:$(LD_LIBRARY_PATH)
	./echoserver.exe
