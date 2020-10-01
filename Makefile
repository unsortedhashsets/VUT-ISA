CC=gcc

CFLAGS=-I. `net-snmp-config --cflags`

DLFLAGS=-fPIC -shared

plugin: module_one.c Makefile
	$(CC) $(CFLAGS) $(DLFLAGS) -c -o module_one.o module_one.c
	$(CC) $(CFLAGS) $(DLFLAGS) -o module_one.so module_one.o