CC=gcc

CFLAGS=-I. `net-snmp-config --cflags`

DLFLAGS=-fPIC -shared

OBJECT=AgentPluginObject
OBJECT_PATH=/home/user/VUT-ISA/project/
MIB=XABRAM00-MIB

NO_COLOR=\033[0m'
TEST_COLOR='\033[93m
OK_COLOR='\033[92m
ERROR_COLOR='\033[91m

build: $(OBJECT).c Makefile
	$(CC) $(CFLAGS) $(DLFLAGS) -c -o $(OBJECT).o $(OBJECT).c
	$(CC) $(CFLAGS) $(DLFLAGS) -o $(OBJECT).so $(OBJECT).o

mib:
	cp mibs/$(MIB).txt /usr/share/snmp/mibs/$(MIB).txt
	snmptranslate -M+. -m$(MIB) -Tp

server:
	snmpd -f -L -DnstAgentPluginLogin -DnstAgentPluginTimeInRFC3339 -DnstAgentPluginInt32 -DnstAgentPluginReleaseVersion,dlmod

deploy:
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.1 i create
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.2 i create
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.3 i create
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.4 i create

	snmpset localhost UCD-DLMOD-MIB::dlmodName.1 s "nstAgentPluginLogin" UCD-DLMOD-MIB::dlmodPath.1 s "$(OBJECT).so"
	snmpset localhost UCD-DLMOD-MIB::dlmodName.2 s "nstAgentPluginTimeInRFC3339" UCD-DLMOD-MIB::dlmodPath.2 s "$(OBJECT).so"
	snmpset localhost UCD-DLMOD-MIB::dlmodName.3 s "nstAgentPluginInt32" UCD-DLMOD-MIB::dlmodPath.3 s "$(OBJECT).so"
	snmpset localhost UCD-DLMOD-MIB::dlmodName.4 s "nstAgentPluginReleaseVersion" UCD-DLMOD-MIB::dlmodPath.4 s "$(OBJECT).so"

	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.1 i load
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.2 i load
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.3 i load
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.4 i load

	snmptable localhost UCD-DLMOD-MIB::dlmodTable


undeploy:
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.1 i unload
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.2 i unload
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.3 i unload
	snmpset localhost UCD-DLMOD-MIB::dlmodStatus.4 i unload

test:
	@echo -e $(OK_COLOR)LOCAL OK TESTS (all should pass) $(NO_COLOR)
	snmpget localhost XABRAM00-MIB::nstAgentPluginLogin.0
	snmpget localhost XABRAM00-MIB::nstAgentPluginTimeInRFC3339.0
	snmpget localhost XABRAM00-MIB::nstAgentPluginInt32.0
	snmpget localhost XABRAM00-MIB::nstAgentPluginReleaseVersion.0
	snmpget localhost .1.3.6.1.3.22.1.0
	snmpget localhost .1.3.6.1.3.22.2.0
	snmpget localhost .1.3.6.1.3.22.3.0
	snmpget localhost .1.3.6.1.3.22.4.0
	@echo -e $(OK_COLOR)REMOTE OK TESTS passed $(NO_COLOR)
	@echo -e $(ERROR_COLOR)REMOTE FAILED TESTS (all should fail) $(NO_COLOR)
	@echo -e $(TEST_COLOR)notWritable tests $(NO_COLOR)
	snmpset localhost XABRAM00-MIB::nstAgentPluginLogin.0 s "TEST"          || true        
	snmpset localhost XABRAM00-MIB::nstAgentPluginTimeInRFC3339.0 s "TEST"  || true        
	snmpset localhost XABRAM00-MIB::nstAgentPluginReleaseVersion.0 s "TEST" || true
	snmpset localhost .1.3.6.1.3.22.1.0 s "TEST" || true 	  
	snmpset localhost .1.3.6.1.3.22.2.0 s "TEST" || true   
	snmpset localhost .1.3.6.1.3.22.4.0 s "TEST" || true    
	@echo -e $(TEST_COLOR)Error value tests $(NO_COLOR)
	snmpset localhost XABRAM00-MIB::nstAgentPluginInt32.0 s "TEST"      || true
	snmpset localhost XABRAM00-MIB::nstAgentPluginInt32.0 i 2147483648  || true
	snmpset localhost XABRAM00-MIB::nstAgentPluginInt32.0 i -2147483649 || true
	snmpset localhost .1.3.6.1.3.22.3.0 s "TEST"      || true
	@echo -e $(ERROR_COLOR)REMOTE FAILED TESTS (all should fail) $(NO_COLOR)

remote-test:
	@echo -e $(OK_COLOR)REMOTE OK TESTS (all should pass) $(NO_COLOR)
	snmpget -v 2c -c public 192.168.56.4 XABRAM00-MIB::nstAgentPluginLogin.0         
	snmpget -v 2c -c public 192.168.56.4 XABRAM00-MIB::nstAgentPluginTimeInRFC3339.0 
	snmpget -v 2c -c public 192.168.56.4 XABRAM00-MIB::nstAgentPluginInt32.0         
	snmpset -v 2c -c public 192.168.56.4 XABRAM00-MIB::nstAgentPluginInt32.0 i 1234  
	snmpget -v 2c -c public 192.168.56.4 XABRAM00-MIB::nstAgentPluginInt32.0         
	snmpget -v 2c -c public 192.168.56.4 XABRAM00-MIB::nstAgentPluginReleaseVersion.0
	snmpget -v 2c -c public 192.168.56.4 .1.3.6.1.3.22.1.0 	  
	snmpget -v 2c -c public 192.168.56.4 .1.3.6.1.3.22.2.0    
	snmpget -v 2c -c public 192.168.56.4 .1.3.6.1.3.22.3.0    
	snmpset -v 2c -c public 192.168.56.4 .1.3.6.1.3.22.3.0 i 0
	snmpget -v 2c -c public 192.168.56.4 .1.3.6.1.3.22.3.0    
	snmpget -v 2c -c public 192.168.56.4 .1.3.6.1.3.22.4.0    
	@echo -e $(OK_COLOR)REMOTE OK TESTS passed $(NO_COLOR)
	@echo -e $(ERROR_COLOR)REMOTE FAILED TESTS (all should fail) $(NO_COLOR)
	@echo -e $(TEST_COLOR)notWritable tests $(NO_COLOR)
	snmpset -v 2c -c public 192.168.56.4 XABRAM00-MIB::nstAgentPluginLogin.0 s "TEST"          || true        
	snmpset -v 2c -c public 192.168.56.4 XABRAM00-MIB::nstAgentPluginTimeInRFC3339.0 s "TEST"  || true        
	snmpset -v 2c -c public 192.168.56.4 XABRAM00-MIB::nstAgentPluginReleaseVersion.0 s "TEST" || true
	snmpset -v 2c -c public 192.168.56.4 .1.3.6.1.3.22.1.0 s "TEST" || true 	  
	snmpset -v 2c -c public 192.168.56.4 .1.3.6.1.3.22.2.0 s "TEST" || true   
	snmpset -v 2c -c public 192.168.56.4 .1.3.6.1.3.22.4.0 s "TEST" || true    
	@echo -e $(TEST_COLOR)Error value tests $(NO_COLOR)
	snmpset -v 2c -c public 192.168.56.4 XABRAM00-MIB::nstAgentPluginInt32.0 s "TEST"      || true
	snmpset -v 2c -c public 192.168.56.4 XABRAM00-MIB::nstAgentPluginInt32.0 i 2147483648  || true
	snmpset -v 2c -c public 192.168.56.4 XABRAM00-MIB::nstAgentPluginInt32.0 i -2147483649 || true
	snmpset -v 2c -c public 192.168.56.4 .1.3.6.1.3.22.3.0 s "TEST"      || true
	@echo -e $(ERROR_COLOR)REMOTE FAILED TESTS (all should fail) $(NO_COLOR)