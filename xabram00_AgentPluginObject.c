/*
 * Note: this file originally auto-generated by mib2c using
 *        $
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <sys/utsname.h>
#include "xabram00_AgentPluginObject.h"


static char nstAgentPluginLogin_object[8] = "xabram00";
static int nstAgentPluginInt32_object = 0;
static char nstAgentPluginTimeInRFC3339_object[50];
static char nstAgentPluginReleaseVersion_object[50];

static oid nstAgentPluginLogin_oid[] = {1, 3, 6, 1, 3, 22, 1 };
static oid nstAgentPluginTimeInRFC3339_oid[] = {1, 3, 6, 1, 3, 22, 2 };
static oid nstAgentPluginInt32_oid[] = {1, 3, 6, 1, 3, 22, 3 };
static oid nstAgentPluginReleaseVersion_oid[] = {1, 3, 6, 1, 3, 22, 4 };

/** Initializes the module_one module */
void init_nstAgentPluginLogin(void)
{
    DEBUGMSGTL(("module_one", "Initializing\n"));

    netsnmp_register_scalar(
        netsnmp_create_handler_registration("nstAgentPluginLogin",
                                            handle_nstAgentPluginLogin,
                                            nstAgentPluginLogin_oid,
                                            OID_LENGTH(nstAgentPluginLogin_oid),
                                            HANDLER_CAN_RONLY));
}

int handle_nstAgentPluginLogin(netsnmp_mib_handler *handler,
                               netsnmp_handler_registration *reginfo,
                               netsnmp_agent_request_info *reqinfo,
                               netsnmp_request_info *requests)
{
    switch (reqinfo->mode)
    {
    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb,
                                 ASN_OCTET_STR,
                                 (u_char *)&nstAgentPluginLogin_object,
                                 strlen(nstAgentPluginLogin_object));
        break;
    default:
        /* we should never get here, so this is a really bad error */
        snmp_log(LOG_ERR, "unknown mode (%d) in handle_nstAgentPluginLogin\n", reqinfo->mode);
        return SNMP_ERR_GENERR;
    }
    return SNMP_ERR_NOERROR;
}

void deinit_nstAgentPluginLogin(void)
{
    unregister_mib(nstAgentPluginLogin_oid, OID_LENGTH(nstAgentPluginLogin_oid));
}

void init_nstAgentPluginTimeInRFC3339(void)
{

    DEBUGMSGTL(("module_one", "Initializing\n"));

    netsnmp_register_scalar(
        netsnmp_create_handler_registration("nstAgentPluginLogin",
                                            handle_nstAgentPluginTimeInRFC3339,
                                            nstAgentPluginTimeInRFC3339_oid,
                                            OID_LENGTH(nstAgentPluginTimeInRFC3339_oid),
                                            HANDLER_CAN_RONLY));
}

int handle_nstAgentPluginTimeInRFC3339(netsnmp_mib_handler *handler,
                                       netsnmp_handler_registration *reginfo,
                                       netsnmp_agent_request_info *reqinfo,
                                       netsnmp_request_info *requests)
{
    char *tmp;
    returnTimeInRFC3339(&tmp);
    strcpy(nstAgentPluginTimeInRFC3339_object, tmp);
    switch (reqinfo->mode)
    {
    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb,
                                 ASN_OCTET_STR,
                                 (u_char *)&nstAgentPluginTimeInRFC3339_object,
                                 strlen(nstAgentPluginTimeInRFC3339_object));
        break;
    default:
        /* we should never get here, so this is a really bad error */
        snmp_log(LOG_ERR, "unknown mode (%d) in handle_nstAgentPluginLogin\n", reqinfo->mode);
        return SNMP_ERR_GENERR;
    }
    return SNMP_ERR_NOERROR;
}

void returnTimeInRFC3339(char **RFC3339)
{
    time_t now = time(NULL);
    struct tm *tm;
    int off_sign;
    int off;

    if ((tm = localtime(&now)) == NULL)
    {
        *RFC3339 = "Error during time check";
    }
    else
    {
        off_sign = '+';
        off = (int)tm->tm_gmtoff;
        if (tm->tm_gmtoff < 0)
        {
            off_sign = '-';
            off = -off;
        }
	char tmp[50];
        sprintf(tmp , "%d-%d-%dT%02d:%02d:%02d%c%02d:%02d\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec, off_sign, off / 3600, off % 3600);
	*RFC3339 = tmp;
    }
}

void deinit_nstAgentPluginTimeInRFC3339(void)
{
    unregister_mib(nstAgentPluginTimeInRFC3339_oid, OID_LENGTH(nstAgentPluginTimeInRFC3339_oid));
}

/** Initializes the module_one module */
void init_nstAgentPluginReleaseVersion(void)
{
    DEBUGMSGTL(("nstAgentPluginReleaseVersion", "Initializing\n"));

    netsnmp_register_scalar(
        netsnmp_create_handler_registration("nstAgentPluginReleaseVersion",
                                            handle_nstAgentPluginReleaseVersion,
                                            nstAgentPluginReleaseVersion_oid,
                                            OID_LENGTH(nstAgentPluginReleaseVersion_oid),
                                            HANDLER_CAN_RONLY));
}

int handle_nstAgentPluginReleaseVersion(netsnmp_mib_handler *handler,
                                        netsnmp_handler_registration *reginfo,
                                        netsnmp_agent_request_info *reqinfo,
                                        netsnmp_request_info *requests)
{
    char *tmp;
    returnSystemInformation(&tmp);
    strcpy(nstAgentPluginReleaseVersion_object, tmp);
    switch (reqinfo->mode)
    {
    case MODE_GET:
        snmp_set_var_typed_value(requests->requestvb,
                                 ASN_OCTET_STR,
                                 (u_char *)&nstAgentPluginReleaseVersion_object,
                                 strlen(nstAgentPluginReleaseVersion_object));
        break;
    default:
        /* we should never get here, so this is a really bad error */
        snmp_log(LOG_ERR, "unknown mode (%d) in handle_nstAgentPluginReleaseVersion\n", reqinfo->mode);
        return SNMP_ERR_GENERR;
    }
    return SNMP_ERR_NOERROR;
}

void returnSystemInformation(char **ReleaseVersion)
{
    struct utsname detect;
    uname(&detect);
    *ReleaseVersion = detect.release;
}

void deinit_nstAgentPluginReleaseVersion(void)
{
    unregister_mib(nstAgentPluginReleaseVersion_oid, OID_LENGTH(nstAgentPluginReleaseVersion_oid));
}



void
init_nstAgentPluginInt32(void)
{

    /*
     * a debugging statement.  Run the agent with -DnstAgentPluginInt32_object to see
     * the output of this debugging statement. 
     */
    DEBUGMSGTL(("nstAgentPluginInt32_object",
                "Initializing the nstAgentPluginInt32_object module\n"));


    /*
     * the line below registers our variables defined above as
     * accessible and makes it writable.  A read only version of any
     * of these registration would merely call
     * register_read_only_int_instance() instead.  The functions
     * called below should be consistent with your MIB, however.
     * 
     * If we wanted a callback when the value was retrieved or set
     * (even though the details of doing this are handled for you),
     * you could change the NULL pointer below to a valid handler
     * function. 
     */
    DEBUGMSGTL(("nstAgentPluginInt32_object",
               "Initalizing nstAgentPluginInt32_object scalar integer.  Default value = %d\n",
                nstAgentPluginInt32_object));

    netsnmp_register_scalar(
        netsnmp_create_handler_registration("nstAgentPluginInt32", handle_nstAgentPluginInt32,
                               nstAgentPluginInt32_oid, OID_LENGTH(nstAgentPluginInt32_oid),
                               HANDLER_CAN_RWRITE
        ));

    DEBUGMSGTL(("nstAgentPluginInt32_object",
                "Done initalizing nstAgentPluginInt32_object module\n"));
}

void
deinit_nstAgentPluginInt32_object(void)
{
    unregister_mib(nstAgentPluginInt32_oid,OID_LENGTH(nstAgentPluginInt32_oid));
}









int
handle_nstAgentPluginInt32(netsnmp_mib_handler *handler,
                          netsnmp_handler_registration *reginfo,
                          netsnmp_agent_request_info   *reqinfo,
                          netsnmp_request_info         *requests)
{
    int ret;
    int tmp;
    int *cache = NULL;

    /* We are never called for a GETNEXT if it's registered as a
       "instance", as it's "magically" handled for us.  */

    /* a instance handler also only hands us one request at a time, so
       we don't need to loop over a list of requests; we'll only get one. */

    switch(reqinfo->mode) {

        case MODE_GET:
            snmp_set_var_typed_value(requests->requestvb, ASN_INTEGER, (u_char *) &nstAgentPluginInt32_object, sizeof(nstAgentPluginInt32_object));
            break;
        /*
         * SET REQUEST
         *
         * multiple states in the transaction.  See:
         * http://www.net-snmp.org/tutorial-5/toolkit/mib_module/set-actions.jpg
         */
        case MODE_SET_RESERVE1:
                /* or you could use netsnmp_check_vb_type_and_size instead */
            ret = netsnmp_check_vb_type(requests->requestvb, ASN_INTEGER);
            if ( ret != SNMP_ERR_NOERROR ) {
                return ret;
            }
            break;

        case MODE_SET_RESERVE2:
        /*
         * store old value for UNDO support in the future. 
         */
            tmp = nstAgentPluginInt32_object;
        case MODE_SET_ACTION:
            /*
            * update current value 
            */
            nstAgentPluginInt32_object = *(requests->requestvb->val.integer);
            DEBUGMSGTL(("testhandler", "new int32 value = %d\n", nstAgentPluginInt32_object));
            break;

        case MODE_SET_UNDO:
            /*
            * ack, something somewhere failed.  We reset back to the
            * previously old value by extracting the previosuly
            * stored information back out of the request 
            */
            nstAgentPluginInt32_object = tmp;
            DEBUGMSGTL(("testhandler", "undo => int32 value = %d\n", nstAgentPluginInt32_object));
            break;
            
        case MODE_SET_COMMIT:
        case MODE_SET_FREE:
            break;

        default:
            /* we should never get here, so this is a really bad error */
            snmp_log(LOG_ERR, "unknown mode (%d) in handle_nstAgentPluginInt32\n", reqinfo->mode );
            return SNMP_ERR_GENERR;
    }
    /*
     * free the information cache 
     */
    return SNMP_ERR_NOERROR;
}