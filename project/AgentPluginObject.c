/*****************************************************************************************
 *                        Project Implementation for IPK 2020/2021                       *
 *       Implement MIB module and dynamically loadable SNMP agent extension net-snmp.    *
 *                                   Date: 15.10.2020                                    *
 *                                Author: Mikhail Abramov                                *
 *                               xabram00@stud.fit.vutbr.cz                              *
 *****************************************************************************************/

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <sys/utsname.h>
#include "AgentPluginObject.h"

/*****************************************************************************************
 *                                    Objects deffinitions:                              *
 *****************************************************************************************/

static char nstAgentPluginLogin_object[8] = "xabram00";
static int  nstAgentPluginInt32_object = 0;
static char nstAgentPluginTimeInRFC3339_object[28];
static char nstAgentPluginReleaseVersion_object[50];

/*****************************************************************************************
 *                                     OID deffinitions:                                 *
 *****************************************************************************************/

static oid nstAgentPluginLogin_oid[]          = {1, 3, 6, 1, 3, 22, 1 };
static oid nstAgentPluginTimeInRFC3339_oid[]  = {1, 3, 6, 1, 3, 22, 2 };
static oid nstAgentPluginInt32_oid[]          = {1, 3, 6, 1, 3, 22, 3 };
static oid nstAgentPluginReleaseVersion_oid[] = {1, 3, 6, 1, 3, 22, 4 };


/*****************************************************************************************
 *                               Additionals functions block:                            *
 *                                 - returnSystemInformation                             *
 *                                 - returnTimeInRFC3339                                 *
 *****************************************************************************************/

/*
 * Function:  returnSystemInformation 
 * --------------------
 * Get information about OS release version (use sys/utsname.h library):
 *    example output: "3.10.0-1127.19.1.el7.x86_64"
 *
 *  @return void -> updates static output value
 */
void returnSystemInformation(){
    struct utsname detect;
    uname(&detect);
    strcpy(nstAgentPluginReleaseVersion_object, detect.release);
}

/*
 * Function:  returnTimeInRFC3339 
 * --------------------
 * Get information about current time and translate in RFC3339 format:
 *    https://tools.ietf.org/html/rfc3339
 *  example output: "2020-10-17T15:35:51-04:00"
 *
 *  @return void -> updates static output value
 */
void returnTimeInRFC3339(){
    time_t now = time(NULL);
    struct tm *tm;
    int off_sign;
    int off;
    if ((tm = localtime(&now)) == NULL){
        strcpy(nstAgentPluginTimeInRFC3339_object, "Error during time check");
    }
    else{
        off_sign = '+';
        off = (int)tm->tm_gmtoff;
        if (tm->tm_gmtoff < 0){
            off_sign = '-';
            off = -off;
        }
        sprintf(nstAgentPluginTimeInRFC3339_object,
                "%d-%d-%dT%02d:%02d:%02d%c%02d:%02d",
                tm->tm_year + 1900,
                tm->tm_mon + 1,
                tm->tm_mday,
                tm->tm_hour,
                tm->tm_min,
                tm->tm_sec,
                off_sign,
                off / 3600,
                off % 3600);
    }
}


/*****************************************************************************************
 *                                 Handlers functions block:                             *
 *                               - handle_nstAgentPluginLogin                            *
 *                               - handle_nstAgentPluginTimeInRFC3339                    *
 *                               - handle_nstAgentPluginInt32                            *
 *                               - handle_nstAgentPluginReleaseVersion                   *
 *****************************************************************************************/

/*
 * Function:  handle_nstAgentPluginLogin 
 * --------------------
 *  Net-SNMP Agent handler
 *  http://www.net-snmp.org/dev/agent/group__handler.html#details
 * 
 *  @param netsnmp_mib_handler:
 *  @param netsnmp_handler_registration:
 *  @param netsnmp_agent_request_info:
 *  @param netsnmp_request_info:
 *  @return int: ERROR number or 0
 */
int handle_nstAgentPluginLogin(netsnmp_mib_handler *handler,
                               netsnmp_handler_registration *reginfo,
                               netsnmp_agent_request_info *reqinfo,
                               netsnmp_request_info *requests){
    switch (reqinfo->mode){
        case MODE_GET:
            DEBUGMSGTL(("nstAgentPluginLogin", 
                        "MODE_GET: string value = %s\n",
                        nstAgentPluginLogin_object));
            snmp_set_var_typed_value(requests->requestvb,
                                     ASN_OCTET_STR,
                                     (u_char *)&nstAgentPluginLogin_object,
                                     strlen(nstAgentPluginLogin_object));
            break;
        default:
            DEBUGMSGTL(("nstAgentPluginLogin", 
                        "Unknown mode (%d)\n",
                        reqinfo->mode));
            snmp_log(LOG_ERR,
                     "Unknown mode (%d)\n",
                     reqinfo->mode);
            return SNMP_ERR_GENERR;
    }
    return SNMP_ERR_NOERROR;
}

/*
 * Function:  handle_nstAgentPluginTimeInRFC3339 
 * --------------------
 *  Net-SNMP Agent handler
 *  http://www.net-snmp.org/dev/agent/group__handler.html#details
 * 
 *  @param netsnmp_mib_handler:
 *  @param netsnmp_handler_registration:
 *  @param netsnmp_agent_request_info:
 *  @param netsnmp_request_info:
 *  @return int: ERROR number or 0
 */
int handle_nstAgentPluginTimeInRFC3339(netsnmp_mib_handler *handler,
                                       netsnmp_handler_registration *reginfo,
                                       netsnmp_agent_request_info *reqinfo,
                                       netsnmp_request_info *requests){
    returnTimeInRFC3339();
    switch (reqinfo->mode)    {
        case MODE_GET:
            DEBUGMSGTL(("nstAgentPluginTimeInRFC3339", 
                        "MODE_GET: string value = %s\n",
                        nstAgentPluginTimeInRFC3339_object));
            snmp_set_var_typed_value(requests->requestvb, 
                                     ASN_OCTET_STR,
                                     (u_char *)&nstAgentPluginTimeInRFC3339_object,
                                     strlen(nstAgentPluginTimeInRFC3339_object));
            break;
        default:
            DEBUGMSGTL(("nstAgentPluginTimeInRFC3339", 
                        "Unknown mode (%d)\n",
                        reqinfo->mode));
            snmp_log(LOG_ERR,
                     "Unknown mode (%d)\n",
                     reqinfo->mode);
            return SNMP_ERR_GENERR;
    }
    return SNMP_ERR_NOERROR;
}

/*
 * Function:  handle_nstAgentPluginInt32 
 * --------------------
 *  Net-SNMP Agent handler
 *  http://www.net-snmp.org/dev/agent/group__handler.html#details
 * 
 *  @param netsnmp_mib_handler:
 *  @param netsnmp_handler_registration:
 *  @param netsnmp_agent_request_info:
 *  @param netsnmp_request_info:
 *  @return int: ERROR number or 0
 */
int handle_nstAgentPluginInt32(netsnmp_mib_handler *handler,
                               netsnmp_handler_registration *reginfo,
                               netsnmp_agent_request_info *reqinfo,
                               netsnmp_request_info *requests){
    int ret = 0;
    int tmp = 0;
    switch (reqinfo->mode)    {
        case MODE_GET:
        
            DEBUGMSGTL(("nstAgentPluginInt32", 
                        "MODE_GET: int32 value = %d\n",
                        nstAgentPluginInt32_object));
            snmp_set_var_typed_value(requests->requestvb,
                                     ASN_INTEGER,
                                     (u_char *)&nstAgentPluginInt32_object,
                                     sizeof(nstAgentPluginInt32_object));
            break;
        case MODE_SET_RESERVE1:
            /*
            * check type 
            */
            DEBUGMSGTL(("nstAgentPluginInt32",
                        "MODE_SET_RESERVE1: check value type\n"));
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if (ret != SNMP_ERR_NOERROR){
                return ret;
            }
            break;
        case MODE_SET_RESERVE2:
            /*
            * reserve old value 
            */
            DEBUGMSGTL(("nstAgentPluginInt32",
                        "MODE_SET_RESERVE2: reserve value = %d\n",
                        nstAgentPluginInt32_object));
            tmp = nstAgentPluginInt32_object;
        case MODE_SET_ACTION:
            /*
            * update current value
            * Additional check in case of int64
            */
            if (*(requests->requestvb->val.integer) < INT32_MIN ||
                *(requests->requestvb->val.integer) > INT32_MAX){
                DEBUGMSGTL(("nstAgentPluginInt32",
                            "MODE_SET_ACTION: Wrong value = %lu\n",
                            *(requests->requestvb->val.integer)));
                return SNMP_ERR_WRONGVALUE;
            }
            nstAgentPluginInt32_object = *(requests->requestvb->val.integer);
            DEBUGMSGTL(("nstAgentPluginInt32",
                        "MODE_SET_ACTION: new int32 value = %d\n",
                        nstAgentPluginInt32_object));
            break;
        case MODE_SET_UNDO:
            /*
            * ack, something somewhere failed.  We reset back to the
            * previously old value by extracting the previosuly
            * stored information back out of the request 
            */
            nstAgentPluginInt32_object = tmp;
            DEBUGMSGTL(("nstAgentPluginInt32",
                        "MODE_SET_UNDO: value = %d\n",
                        nstAgentPluginInt32_object));
            break;
        case MODE_SET_COMMIT:
            DEBUGMSGTL(("nstAgentPluginInt32",
                        "MODE_SET_COMMIT: skip\n"));
        case MODE_SET_FREE:
            /*
            * the only thing to do here is free the old memdup'ed
            * value, but it's auto-freed by the datalist recovery, so
            * we don't have anything to actually do here 
            */
            DEBUGMSGTL(("nstAgentPluginInt32",
                        "MODE_SET_FREE: skip\n"));
            break;
        default:
            DEBUGMSGTL(("nstAgentPluginInt32", 
                        "Unknown mode (%d)\n",
                        reqinfo->mode));
            snmp_log(LOG_ERR, 
                     "unknown mode (%d)\n",
                     reqinfo->mode);
            return SNMP_ERR_GENERR;
    }
    return SNMP_ERR_NOERROR;
}

/*
 * Function:  handle_nstAgentPluginReleaseVersion 
 * --------------------
 *  Net-SNMP Agent handler
 *  http://www.net-snmp.org/dev/agent/group__handler.html#details
 * 
 *  @param netsnmp_mib_handler:
 *  @param netsnmp_handler_registration:
 *  @param netsnmp_agent_request_info:
 *  @param netsnmp_request_info:
 *  @return int: ERROR number or 0
 */
int handle_nstAgentPluginReleaseVersion(netsnmp_mib_handler *handler,
                                        netsnmp_handler_registration *reginfo,
                                        netsnmp_agent_request_info *reqinfo,
                                        netsnmp_request_info *requests){
    returnSystemInformation();
    switch (reqinfo->mode){
        case MODE_GET:
            DEBUGMSGTL(("nstAgentPluginReleaseVersion", 
                        "MODE_GET: string value = %s\n",
                        nstAgentPluginReleaseVersion_object));
            snmp_set_var_typed_value(requests->requestvb,
                                     ASN_OCTET_STR,
                                     (u_char *)&nstAgentPluginReleaseVersion_object,
                                     strlen(nstAgentPluginReleaseVersion_object));
            break;
        default:
            DEBUGMSGTL(("nstAgentPluginReleaseVersion", 
                        "Unknown mode (%d)\n",
                        reqinfo->mode));
            snmp_log(LOG_ERR,
                     "Unknown mode (%d)\n",
                     reqinfo->mode);
            return SNMP_ERR_GENERR;
    }
    return SNMP_ERR_NOERROR;
}


/*****************************************************************************************
 *                               Initialization functions block:                         *
 *                                 - init_nstAgentPluginLogin                            *
 *                                 - init_nstAgentPluginTimeInRFC3339                    *
 *                                 - init_nstAgentPluginInt32                            *
 *                                 - init_nstAgentPluginReleaseVersion                   *
 *****************************************************************************************/

/*
 * Function: init_nstAgentPluginLogin 
 * --------------------
 * Initialization function to start plugin object, automatically called by the agent
 * Function should be called init_MODULE_NAME, 
 * Create a scalar handler calling netsnmp_create_handler to handle incoming signals
 */
void init_nstAgentPluginLogin(void){
    DEBUGMSGTL(("nstAgentPluginLogin",
                "Initializing module\n"));
    DEBUGMSGTL(("nstAgentPluginLogin",
                "Initalizing scalar string. Default value = %s\n",
                                                         nstAgentPluginLogin_object));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("nstAgentPluginLogin",
                                             handle_nstAgentPluginLogin,
                                             nstAgentPluginLogin_oid,
                                             OID_LENGTH(nstAgentPluginLogin_oid),
                                             HANDLER_CAN_RONLY));
    DEBUGMSGTL(("nstAgentPluginLogin", 
                "Done initalizing module\n"));
}

/*
 * Function: init_nstAgentPluginTimeInRFC3339 
 * --------------------
 * Initialization function to start plugin object, automatically called by the agent
 * Function should be called init_MODULE_NAME, 
 * Create a scalar handler calling netsnmp_create_handler to handle incoming signals
 */
void init_nstAgentPluginTimeInRFC3339(void){
    DEBUGMSGTL(("nstAgentPluginTimeInRFC3339", 
                "Initializing module\n"));
    DEBUGMSGTL(("nstAgentPluginTimeInRFC3339", 
                "Initalizing scalar string.\n"));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("nstAgentPluginTimeInRFC3339",
                                       handle_nstAgentPluginTimeInRFC3339,
                                       nstAgentPluginTimeInRFC3339_oid,
                                       OID_LENGTH(nstAgentPluginTimeInRFC3339_oid),
                                       HANDLER_CAN_RONLY));
    DEBUGMSGTL(("nstAgentPluginTimeInRFC3339",
                "Done initalizing module\n"));
}

/*
 * Function: init_nstAgentPluginInt32 
 * --------------------
 * Initialization function to start plugin object, automatically called by the agent
 * Function should be called init_MODULE_NAME, 
 * Create a scalar handler calling netsnmp_create_handler to handle incoming signals
 */
void init_nstAgentPluginInt32(void){
    DEBUGMSGTL(("nstAgentPluginInt32",
                "Initializing the module\n"));
    DEBUGMSGTL(("nstAgentPluginInt32", 
                "Initalizing scalar integer. Default value = %d\n",
                                                          nstAgentPluginInt32_object));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("nstAgentPluginInt32",
                                             handle_nstAgentPluginInt32,
                                             nstAgentPluginInt32_oid,
                                             OID_LENGTH(nstAgentPluginInt32_oid),
                                             HANDLER_CAN_RWRITE));
    DEBUGMSGTL(("nstAgentPluginInt32",
                "Done initalizing module\n"));
}

/*
 * Function: init_nstAgentPluginReleaseVersion 
 * --------------------
 * Initialization function to start plugin object, automatically called by the agent
 * Function should be called init_MODULE_NAME, 
 * Create a scalar handler calling netsnmp_create_handler to handle incoming signals
 */
void init_nstAgentPluginReleaseVersion(void){
    DEBUGMSGTL(("nstAgentPluginReleaseVersion",
                "Initializing module\n"));
    DEBUGMSGTL(("nstAgentPluginReleaseVersion",
                "Initalizing scalar string.\n"));
    netsnmp_register_scalar(
        netsnmp_create_handler_registration("nstAgentPluginReleaseVersion",
                                             handle_nstAgentPluginReleaseVersion,
                                             nstAgentPluginReleaseVersion_oid,
                                             OID_LENGTH(nstAgentPluginReleaseVersion_oid),
                                             HANDLER_CAN_RONLY));
    DEBUGMSGTL(("nstAgentPluginReleaseVersion",
                "Done initalizing module\n"));
}


/*****************************************************************************************
 *                             Deinitialization functions block:                         *
 *                               - deinit_nstAgentPluginLogin                            *
 *                               - deinit_nstAgentPluginTimeInRFC3339                    *
 *                               - deinit_nstAgentPluginInt32                            *
 *                               - deinit_nstAgentPluginReleaseVersion                   *
 *****************************************************************************************/

/*
 * Function: deinit_nstAgentPluginLogin 
 * --------------------
 * Unregisters a module registered against a given OID at the default priority.
 */
void deinit_nstAgentPluginLogin(void){
    DEBUGMSGTL(("nstAgentPluginLogin",
                "Deinitializing\n"));
    unregister_mib(nstAgentPluginLogin_oid,
                   OID_LENGTH(nstAgentPluginLogin_oid));
    DEBUGMSGTL(("nstAgentPluginLogin",
                "Done deinitalizing module\n"));
}

/*
 * Function: deinit_nstAgentPluginTimeInRFC3339 
 * --------------------
 * Unregisters a module registered against a given OID at the default priority.
 */
void deinit_nstAgentPluginTimeInRFC3339(void){
    DEBUGMSGTL(("nstAgentPluginTimeInRFC3339",
                "Deinitializing\n"));
    unregister_mib(nstAgentPluginTimeInRFC3339_oid,
                   OID_LENGTH(nstAgentPluginTimeInRFC3339_oid));
    DEBUGMSGTL(("nstAgentPluginTimeInRFC3339",
                "Done deinitalizing module\n"));
}

/*
 * Function: deinit_nstAgentPluginInt32 
 * --------------------
 * Unregisters a module registered against a given OID at the default priority.
 */
void deinit_nstAgentPluginInt32(void){
    DEBUGMSGTL(("nstAgentPluginInt32",
                "Deinitializing\n"));
    unregister_mib(nstAgentPluginInt32_oid,
                   OID_LENGTH(nstAgentPluginInt32_oid));
    DEBUGMSGTL(("nstAgentPluginInt32",
                "Done deinitalizing module\n"));
}

/*
 * Function:  deinit_nstAgentPluginReleaseVersion 
 * --------------------
 * Unregisters a module registered against a given OID at the default priority.
 */
void deinit_nstAgentPluginReleaseVersion(void){
    DEBUGMSGTL(("nstAgentPluginReleaseVersion",
                "Deinitializing\n"));
    unregister_mib(nstAgentPluginReleaseVersion_oid,
                   OID_LENGTH(nstAgentPluginReleaseVersion_oid));
    DEBUGMSGTL(("nstAgentPluginReleaseVersion",
                "Done deinitalizing module\n"));
}
