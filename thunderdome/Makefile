# The worst makefile in the world!

JULIA_PATH = $(HOME)/julia

SHLIB_EXT = dll
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	SHLIB_EXT = sh
endif
ifeq ($(UNAME_S),Darwin)
	SHLIB_EXT = dylib
endif

DEBUG = -g

default: all

all: example_client

libtd.$(SHLIB_EXT): td.h td.c
	$(CC) $(DEBUG) -fPIC -c td.c -o td.o
	$(CC) $(DEBUG) -shared -fPIC td.o -o $@ -ldl

libtd_julia.$(SHLIB_EXT): td.h td_julia.c libtd.$(SHLIB_EXT)
	$(CC) $(DEBUG) -fPIC -c td_julia.c -o td_julia.o -I$(JULIA_PATH)/src -I$(JULIA_PATH)/src/support -I$(JULIA_PATH)/usr/include
	$(CC) $(DEBUG) -shared -fPIC td_julia.o -o $@ $(JULIA_PATH)/usr/lib/libjulia.$(SHLIB_EXT) ./libtd.$(SHLIB_EXT)

example_client: example_client.c td.h libtd_julia.$(SHLIB_EXT)
	$(CC) $(DEBUG) $< -o $@ ./libtd.$(SHLIB_EXT)

clean:
	rm -f *.$(SHLIB_EXT) *.o
	rm -f example_client
