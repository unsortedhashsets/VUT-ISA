#ifndef AgentPluginObject_h
#define AgentPluginObject_h

void returnTimeInRFC3339(char ** RFC3339);
void returnSystemInformation(char ** ReleaseVersion);

Netsnmp_Node_Handler handle_nstAgentPluginLogin;
Netsnmp_Node_Handler handle_nstAgentPluginTimeInRFC3339;
Netsnmp_Node_Handler handle_nstAgentPluginInt32;
Netsnmp_Node_Handler handle_nstAgentPluginReleaseVersion;

void init_nstAgentPluginLogin(void);
void init_nstAgentPluginTimeInRFC3339(void);
void init_nstAgentPluginInt32(void);
void init_nstAgentPluginReleaseVersion(void);

void deinit_nstAgentPluginLogin(void);
void deinit_nstAgentPluginTimeInRFC3339(void);
void deinit_nstAgentPluginInt32(void);
void deinit_nstAgentPluginReleaseVersion(void);

#endif