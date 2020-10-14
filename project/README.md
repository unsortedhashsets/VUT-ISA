# Program description
Implementation of the MIB module and dynamically loadable SNMP agent extension for net-snmp

# Compilation
* Compile the program by entering the command `make` or `make build`.
* In case of if is necessary to use agent extension through the MIB name (for example for the `make test` and `make remote-test` commands) additionally use command `make mib` to copy the MIB file to special MIB's directory and see the information about the modules.

# Launch
* Start server on the additional terminal with command `make server` it will launch server with debug mode for needed modules.
* Use `make deploy` command to deploy agent extension into the running server (you will be able to see logs on the server terminal)
* If you are still on the agent's machine you also can use some local manual tests with command `make tests` to see the results and logs on the server part.
* On the other remote machine you can do commands: `make mib` (to copy mib information), and use `make remote-test <server-machine-IP>` (take care about firewall rules).
* LOCAL manual command example: `snmpget localhost .1.3.6.1.3.22.3.0`
  * Output example: 
* REMOTE manual command example through the MIB: `snmpget -v 2c -c public <server-machine-IP> XABRAM00-MIB::nstAgentPluginReleaseVersion.0`
  * Output example: 

# List of uploaded files
* AgentPluginObject.c
* AgentPluginObject.h
* mib/XABRAM00-MIB.txt
* Makefile
* manual.pdf
* README.md