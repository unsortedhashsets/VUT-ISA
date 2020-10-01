CC=gcc

CFLAGS=-I. `net-snmp-config --cflags`

DLFLAGS=-fPIC -shared

plugin: xabram00_AgentPluginObject.c Makefile
	$(CC) $(CFLAGS) $(DLFLAGS) -c -o xabram00_AgentPluginObject.o xabram00_AgentPluginObject.c
	$(CC) $(CFLAGS) $(DLFLAGS) -o xabram00_AgentPluginObject.so xabram00_AgentPluginObject.o