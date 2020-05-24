CFLAGS := -Wall -Wextra -Wpedantic -std=c99

INCLUDEDIRS := -I packets/
BUILDDIR ?= $(shell pwd)/../../build

debug : CFLAGS += -Og -g
release : CFLAGS += -Os

.PHONY: debug release

debug: evloop.o socket_setup.o
	$(MAKE) --directory=packets
	mv *.o $(BUILDDIR)/

release: evloop.o socket_setup.o
	$(MAKE) --directory=packets
	mv *.o $(BUILDDIR)/

evloop.o: evloop.c
	$(CC) $(CFLAGS) $(INCLUDEDIRS) -c $< -o $@

socket_setup.o: socket_setup.c
	$(CC) $(CFLAGS) $(INCLUDEDIRS) -c $< -o $@

