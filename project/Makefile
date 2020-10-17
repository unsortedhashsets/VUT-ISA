CC=gcc

CFLAGS=-I. `net-snmp-config --cflags`

DLFLAGS=-fPIC -shared

OBJECT=AgentPluginObject
current_dir = $(shell pwd)
MIB=XABRAM00-MIB

NO_COLOR=\033[0m'
TEST_COLOR='\033[93m
OK_COLOR='\033[92m
ERROR_COLOR='\033[91m

build: $(OBJECT).c Makefile
	$(CC) $(CFLAGS) $(DLFLAGS) -c -o $(OBJECT).o $(OBJECT).c
	$(CC) $(CFLAGS) $(DLFLAGS) -o $(OBJECT).so $(OBJECT).o

mib:
	cp $(current_dir)/mibs/$(MIB).txt /usr/share/snmp/mibs/$(MIB).txt
	snmptranslate -M+. -m$(MIB) -Tp

server:
	snmpd -f -L -DnstAgentPluginLogin -DnstAgentPluginTimeInRFC3339 -DnstAgentPluginInt32 -DnstAgentPluginReleaseVersion,dlmod

deploy:
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.1 i create UCD-DLMOD-MIB::dlmodStatus.2 i create UCD-DLMOD-MIB::dlmodStatus.3 i create UCD-DLMOD-MIB::dlmodStatus.4 i create

	snmpset localhost UCD-DLMOD-MIB::dlmodName.1 s "nstAgentPluginLogin" UCD-DLMOD-MIB::dlmodPath.1 s "$(current_dir)/$(OBJECT).so"
	snmpset localhost UCD-DLMOD-MIB::dlmodName.2 s "nstAgentPluginTimeInRFC3339" UCD-DLMOD-MIB::dlmodPath.2 s "/$(current_dir)/$(OBJECT).so"
	snmpset localhost UCD-DLMOD-MIB::dlmodName.3 s "nstAgentPluginInt32" UCD-DLMOD-MIB::dlmodPath.3 s "$(current_dir)/$(OBJECT).so"
	snmpset localhost UCD-DLMOD-MIB::dlmodName.4 s "nstAgentPluginReleaseVersion" UCD-DLMOD-MIB::dlmodPath.4 s "/$(current_dir)/$(OBJECT).so"

	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.1 i load UCD-DLMOD-MIB::dlmodStatus.2 i load UCD-DLMOD-MIB::dlmodStatus.3 i load UCD-DLMOD-MIB::dlmodStatus.4 i load

	snmptable localhost UCD-DLMOD-MIB::dlmodTable


undeploy:
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.1 i unload UCD-DLMOD-MIB::dlmodStatus.2 i unload UCD-DLMOD-MIB::dlmodStatus.3 i unload UCD-DLMOD-MIB::dlmodStatus.4 i unload

test:
	@echo -e $(OK_COLOR)OK TESTS$(NO_COLOR)
	@echo ""
	snmpget localhost XABRAM00-MIB::nstAgentPluginLogin.0 XABRAM00-MIB::nstAgentPluginTimeInRFC3339.0 XABRAM00-MIB::nstAgentPluginInt32.0 XABRAM00-MIB::nstAgentPluginReleaseVersion.0
	@echo ""
	snmpset localhost XABRAM00-MIB::nstAgentPluginInt32.0 i 1234
	@echo ""
	snmpget localhost XABRAM00-MIB::nstAgentPluginInt32.0
	@echo ""
	snmpget localhost .1.3.6.1.3.22.1.0 .1.3.6.1.3.22.2.0 .1.3.6.1.3.22.3.0 .1.3.6.1.3.22.4.0
	@echo ""
	snmpset localhost .1.3.6.1.3.22.3.0 i 666
	@echo ""
	snmpget localhost .1.3.6.1.3.22.3.0
	@echo ""
	@echo -e $(ERROR_COLOR)REMOTE FAILED TESTS$(NO_COLOR)
	@echo -e $(TEST_COLOR)notWritable tests $(NO_COLOR)
	@echo ""
	snmpset localhost XABRAM00-MIB::nstAgentPluginLogin.0 s "TEST"          || true 
	@echo ""       
	snmpset localhost XABRAM00-MIB::nstAgentPluginTimeInRFC3339.0 s "TEST"  || true    
	@echo ""    
	snmpset localhost XABRAM00-MIB::nstAgentPluginReleaseVersion.0 s "TEST" || true
	@echo ""
	snmpset localhost .1.3.6.1.3.22.1.0 s "TEST" || true
	@echo "" 
	snmpset localhost .1.3.6.1.3.22.2.0 s "TEST" || true
	@echo ""
	snmpset localhost .1.3.6.1.3.22.4.0 s "TEST" || true
	@echo ""   
	@echo -e $(TEST_COLOR)Error value tests $(NO_COLOR)
	@echo ""
	snmpset localhost XABRAM00-MIB::nstAgentPluginInt32.0 s "TEST"      || true
	@echo ""
	snmpset localhost XABRAM00-MIB::nstAgentPluginInt32.0 i 2147483648  || true
	@echo ""
	snmpset localhost XABRAM00-MIB::nstAgentPluginInt32.0 i -2147483649 || true
	@echo ""
	snmpset localhost .1.3.6.1.3.22.3.0 s "TEST"      || true

remote-test:
ifdef IP
	@echo -e $(OK_COLOR)REMOTE OK TESTS$(NO_COLOR)
	@echo ""
	snmpget -v 2c -c public ${IP} XABRAM00-MIB::nstAgentPluginLogin.0 XABRAM00-MIB::nstAgentPluginTimeInRFC3339.0 XABRAM00-MIB::nstAgentPluginInt32.0 XABRAM00-MIB::nstAgentPluginReleaseVersion.0      
	@echo ""
	snmpset -v 2c -c public ${IP} XABRAM00-MIB::nstAgentPluginInt32.0 i 1234  
	@echo ""
	snmpget -v 2c -c public ${IP} XABRAM00-MIB::nstAgentPluginInt32.0         
	@echo ""
	snmpget -v 2c -c public ${IP} .1.3.6.1.3.22.1.0 .1.3.6.1.3.22.2.0 .1.3.6.1.3.22.3.0 .1.3.6.1.3.22.4.0
	@echo ""
	snmpset -v 2c -c public ${IP} .1.3.6.1.3.22.3.0 i 666
	@echo ""
	snmpget -v 2c -c public ${IP} .1.3.6.1.3.22.3.0
	@echo ""
	@echo -e $(ERROR_COLOR)REMOTE FAILED TESTS$(NO_COLOR)
	@echo -e $(TEST_COLOR)notWritable tests $(NO_COLOR)
	@echo ""
	snmpset -v 2c -c public ${IP} XABRAM00-MIB::nstAgentPluginLogin.0 s "TEST"          || true 
	@echo ""       
	snmpset -v 2c -c public ${IP} XABRAM00-MIB::nstAgentPluginTimeInRFC3339.0 s "TEST"  || true     
	@echo ""   
	snmpset -v 2c -c public ${IP} XABRAM00-MIB::nstAgentPluginReleaseVersion.0 s "TEST" || true
	@echo ""
	snmpset -v 2c -c public ${IP} .1.3.6.1.3.22.1.0 s "TEST" || true 	  
	@echo ""
	snmpset -v 2c -c public ${IP} .1.3.6.1.3.22.2.0 s "TEST" || true   
	@echo ""
	snmpset -v 2c -c public ${IP} .1.3.6.1.3.22.4.0 s "TEST" || true    
	@echo ""
	@echo -e $(TEST_COLOR)Error value tests $(NO_COLOR)
	@echo ""
	snmpset -v 2c -c public ${IP} XABRAM00-MIB::nstAgentPluginInt32.0 s "TEST"      || true
	@echo ""
	snmpset -v 2c -c public ${IP} XABRAM00-MIB::nstAgentPluginInt32.0 i 2147483648  || true
	@echo ""
	snmpset -v 2c -c public ${IP} XABRAM00-MIB::nstAgentPluginInt32.0 i -2147483649 || true
	@echo ""
	snmpset -v 2c -c public ${IP} .1.3.6.1.3.22.3.0 s "TEST"      || true
	@echo -e $(ERROR_COLOR)REMOTE FAILED TESTS (all should fail) $(NO_COLOR)
else
	@echo 'please, define: IP="<ip>"'
endif