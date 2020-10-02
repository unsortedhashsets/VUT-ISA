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
	sudo cp $(OBJECT_PATH)/mibs/$(MIB) /usr/share/snmp/mibs/$(MIB)

	sudo snmpset localhost UCD-DLMOD-MIB::dlmodStatus.1 i create
	sudo snmpset localhost UCD-DLMOD-MIB::dlmodStatus.2 i create
	sudo snmpset localhost UCD-DLMOD-MIB::dlmodStatus.3 i create
	sudo snmpset localhost UCD-DLMOD-MIB::dlmodStatus.4 i create

	sudo snmpset localhost UCD-DLMOD-MIB::dlmodName.1 s "nstAgentPluginLogin" UCD-DLMOD-MIB::dlmodPath.1 s "$(OBJECT_PATH)$(OBJECT).so"
	sudo snmpset localhost UCD-DLMOD-MIB::dlmodName.2 s "nstAgentPluginTimeInRFC3339" UCD-DLMOD-MIB::dlmodPath.2 s "$(OBJECT_PATH)$(OBJECT).so"
	sudo snmpset localhost UCD-DLMOD-MIB::dlmodName.3 s "nstAgentPluginInt32" UCD-DLMOD-MIB::dlmodPath.3 s "$(OBJECT_PATH)$(OBJECT).so"
	sudo snmpset localhost UCD-DLMOD-MIB::dlmodName.4 s "nstAgentPluginReleaseVersion" UCD-DLMOD-MIB::dlmodPath.4 s "$(OBJECT_PATH)$(OBJECT).so"

	sudo snmpset localhost UCD-DLMOD-MIB::dlmodStatus.1 i load
	sudo snmpset localhost UCD-DLMOD-MIB::dlmodStatus.2 i load
	sudo snmpset localhost UCD-DLMOD-MIB::dlmodStatus.3 i load
	sudo snmpset localhost UCD-DLMOD-MIB::dlmodStatus.4 i load

	sudo snmptable localhost UCD-DLMOD-MIB::dlmodTable
	sudo snmptranslate -M+. -m$(MIB) -Tp

server: 
	sudo snmpd -f -L -DnstAgentPluginLogin -DnstAgentPluginTimeInRFC3339 -DnstAgentPluginInt32 -DnstAgentPluginReleaseVersion ,dlmod

test:

	sudo snmpget localhost NET-SNMP-TUTORIAL-MIB::nstAgentPluginLogin.0
	sudo snmpget localhost NET-SNMP-TUTORIAL-MIB::nstAgentPluginTimeInRFC3339.0
	sudo snmpget localhost NET-SNMP-TUTORIAL-MIB::nstAgentPluginInt32.0
	sudo snmpget localhost NET-SNMP-TUTORIAL-MIB::nstAgentPluginReleaseVersion.0
	
	sudo snmpget localhost .1.3.6.1.3.22.1.0
	sudo snmpget localhost .1.3.6.1.3.22.2.0
	sudo snmpget localhost .1.3.6.1.3.22.3.0
	sudo snmpget localhost .1.3.6.1.3.22.4.0

undeploy:

	sudo snmpset localhost UCD-DLMOD-MIB::dlmodStatus.1 i unload
	sudo snmpset localhost UCD-DLMOD-MIB::dlmodStatus.2 i unload
	sudo snmpset localhost UCD-DLMOD-MIB::dlmodStatus.3 i unload
	sudo snmpset localhost UCD-DLMOD-MIB::dlmodStatus.4 i unload

