# Program description
Implementation of the MIB module and dynamically loadable SNMP agent extension for net-snmp

# Compilation
* Compile the program by entering the command `make` or `make build`.
* `(su/sudo)` In case of if is necessary to use agent extension through the MIB name (for example for the `make test` and `make remote-test` commands) additionally use command `make mib` to copy the MIB file to special MIB's directory and see the information about the modules.

# Launch
* `(su/sudo)` Start server on the additional terminal with command `make server` it will launch server with debug mode for needed modules.
* Use `make deploy` command to deploy agent extension into the running server (you will be able to see logs on the server terminal)
* If you are still on the agent's machine you also can use some local manual tests with command `make tests` to see the results and logs on the server part.
* On the other remote machine you can do commands: `(su/sudo) make mib` (to copy mib information), and use `make remote-test <server-machine-IP>` (take care about firewall rules).
* LOCAL manual command example: `snmpget localhost .1.3.6.1.3.22.2.0`
  * Output example: `SNMPv2-SMI::experimental.22.2.0 = STRING: "2020-10-14T17:14:52-04:00"`
* REMOTE manual command example through the MIB: `snmpget -v 2c -c public <server-machine-IP> XABRAM00-MIB::nstAgentPluginReleaseVersion.0`
  * Output example: `XABRAM00-MIB::nstAgentPluginReleaseVersion.0 = STRING: "3.10.0-1127.19.1.el7.x86_64"`

# List of uploaded files
* AgentPluginObject.c
* AgentPluginObject.h
* mibs/XABRAM00-MIB.txt
* Makefile
* manual.pdf
* README.md