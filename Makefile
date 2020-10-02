CC=gcc

CFLAGS=-I. `net-snmp-config --cflags`

DLFLAGS=-fPIC -shared

OBJECT=xabram00_AgentPluginObject
OBJECT_PATH=/home/user/VUT-ISA/
MIB=XABRAM00-MIB

build: $(OBJECT).c Makefile
	$(CC) $(CFLAGS) $(DLFLAGS) -c -o $(OBJECT).o $(OBJECT).c
	$(CC) $(CFLAGS) $(DLFLAGS) -o $(OBJECT).so $(OBJECT).o

deploy:
	cp $(OBJECT_PATH)/mibs/$(MIB).txt /usr/share/snmp/mibs/$(MIB).txt

	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.1 i create
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.2 i create
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.3 i create
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.4 i create

	snmpset localhost UCD-DLMOD-MIB::dlmodName.1 s "nstAgentPluginLogin" UCD-DLMOD-MIB::dlmodPath.1 s "$(OBJECT_PATH)$(OBJECT).so"
	snmpset localhost UCD-DLMOD-MIB::dlmodName.2 s "nstAgentPluginTimeInRFC3339" UCD-DLMOD-MIB::dlmodPath.2 s "$(OBJECT_PATH)$(OBJECT).so"
	snmpset localhost UCD-DLMOD-MIB::dlmodName.3 s "nstAgentPluginInt32" UCD-DLMOD-MIB::dlmodPath.3 s "$(OBJECT_PATH)$(OBJECT).so"
	snmpset localhost UCD-DLMOD-MIB::dlmodName.4 s "nstAgentPluginReleaseVersion" UCD-DLMOD-MIB::dlmodPath.4 s "$(OBJECT_PATH)$(OBJECT).so"

	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.1 i load
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.2 i load
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.3 i load
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.4 i load

	snmptable localhost UCD-DLMOD-MIB::dlmodTable
	snmptranslate -M+. -m$(MIB) -Tp

server: 
	snmpd -f -L -DnstAgentPluginLogin,-DnstAgentPluginTimeInRFC3339,-DnstAgentPluginInt32,-DnstAgentPluginReleaseVersion,dlmod

test:

	snmpget localhost XABRAM00-MIB::nstAgentPluginLogin.0
	snmpget localhost XABRAM00-MIB::nstAgentPluginTimeInRFC3339.0
	snmpget localhost XABRAM00-MIB::nstAgentPluginInt32.0
	snmpget localhost XABRAM00-MIB::nstAgentPluginReleaseVersion.0
	
	snmpget localhost .1.3.6.1.3.22.1.0
	snmpget localhost .1.3.6.1.3.22.2.0
	snmpget localhost .1.3.6.1.3.22.3.0
	snmpget localhost .1.3.6.1.3.22.4.0

undeploy:

	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.1 i unload
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.2 i unload
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.3 i unload
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.4 i unload

