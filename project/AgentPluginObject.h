/*****************************************************************************************
 *                        Project Implementation for IPK 2020/2021                       *
 *       Implement MIB module and dynamically loadable SNMP agent extension net-snmp.    *
 *                                   Date: 15.10.2020                                    *
 *                                Author: Mikhail Abramov                                *
 *                               xabram00@stud.fit.vutbr.cz                              *
 *****************************************************************************************/

#ifndef AgentPluginObject_h
#define AgentPluginObject_h

/*****************************************************************************************
 *                          Additionals functions block declaration:                     *
 *                                 - returnSystemInformation                             *
 *                                 - returnTimeInRFC3339                                 *
 *****************************************************************************************/
void returnTimeInRFC3339(void);
void returnSystemInformation(void);

/*****************************************************************************************
 *                             Handlers functions block declaration:                     *
 *                               - handle_nstAgentPluginLogin                            *
 *                               - handle_nstAgentPluginTimeInRFC3339                    *
 *                               - handle_nstAgentPluginInt32                            *
 *                               - handle_nstAgentPluginReleaseVersion                   *
 *****************************************************************************************/
Netsnmp_Node_Handler handle_nstAgentPluginLogin;
Netsnmp_Node_Handler handle_nstAgentPluginTimeInRFC3339;
Netsnmp_Node_Handler handle_nstAgentPluginInt32;
Netsnmp_Node_Handler handle_nstAgentPluginReleaseVersion;

/*****************************************************************************************
 *                            Initialization functions block declaration:                *
 *                                 - init_nstAgentPluginLogin                            *
 *                                 - init_nstAgentPluginTimeInRFC3339                    *
 *                                 - init_nstAgentPluginInt32                            *
 *                                 - init_nstAgentPluginReleaseVersion                   *
 *****************************************************************************************/
void init_nstAgentPluginLogin(void);
void init_nstAgentPluginTimeInRFC3339(void);
void init_nstAgentPluginInt32(void);
void init_nstAgentPluginReleaseVersion(void);

/*****************************************************************************************
 *                         Deinitialization functions block declaration:                 *
 *                               - deinit_nstAgentPluginLogin                            *
 *                               - deinit_nstAgentPluginTimeInRFC3339                    *
 *                               - deinit_nstAgentPluginInt32                            *
 *                               - deinit_nstAgentPluginReleaseVersion                   *
 *****************************************************************************************/
void deinit_nstAgentPluginLogin(void);
void deinit_nstAgentPluginTimeInRFC3339(void);
void deinit_nstAgentPluginInt32(void);
void deinit_nstAgentPluginReleaseVersion(void);

#endif