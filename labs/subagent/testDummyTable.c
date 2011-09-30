#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/table_container.h>
#include <net-snmp/data_access/swinst.h>
#include <net-snmp/agent/cache_handler.h>

#include "testDummyTable.h"

#define MYTABLE "testDummyTable"

netsnmp_feature_require(table_container)

static netsnmp_table_registration_info *table_info;

static void _cache_free(netsnmp_cache * cache, void *magic);
static int _cache_load(netsnmp_cache * cache, void *magic);

/** Initializes the testDummyTable module */
void
init_testDummyTable(void)
{
    /*
     * here we initialize all the tables we're planning on supporting 
     */
    initialize_table_testDummyTable();
}

void
shutdown_testDummyTable(void)
{
    if (table_info) {
		netsnmp_table_registration_info_free(table_info);
		table_info = NULL;
    }
}

/** Initialize the testDummyTable table by defining its contents and how it's structured */
void
initialize_table_testDummyTable(void)
{
    static oid testDummyTable_oid[] = { 1, 3, 6, 1, 2, 1, 25, 6, 3 };
    size_t testDummyTable_oid_len = OID_LENGTH(testDummyTable_oid);

    netsnmp_handler_registration *reg;
    netsnmp_mib_handler *handler = NULL;
    netsnmp_container *container = NULL;
    netsnmp_cache *cache = NULL;

    DEBUGMSGTL(("testDummy", "initialize\n"));

    reg =
        netsnmp_create_handler_registration("testDummyTable",
                                            testDummyTable_handler,
                                            testDummyTable_oid,
                                            testDummyTable_oid_len,
                                            HANDLER_CAN_RONLY);
    if (NULL == reg) {
        snmp_log(LOG_ERR,"error creating handler registration for "
                 MYTABLE "\n");
        goto bail;
    }

    container = netsnmp_container_find("testDummyTable:table_container");
    if (NULL == container) {
        snmp_log(LOG_ERR,"error creating container for "
                 MYTABLE "\n");
        goto bail;
    }

    table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
    if (NULL == table_info) {
        snmp_log(LOG_ERR,"error allocating table registration for "
                 MYTABLE "\n");
        goto bail;
    }

    netsnmp_table_helper_add_indexes(table_info, ASN_INTEGER,   /* index: testDummyIndex */
                                     0);
    table_info->min_column = COLUMN_TESTDUMMYINDEX;
    table_info->max_column = COLUMN_TESTDUMMYDATE;

    /*************************************************
     *
     * inject container_table helper
     */
    handler = netsnmp_container_table_handler_get(table_info, container,
                                                  TABLE_CONTAINER_KEY_NETSNMP_INDEX);
    if (NULL == handler) {
        snmp_log(LOG_ERR,"error allocating table registration for "
                 MYTABLE "\n");
        goto bail;
    }
    if (SNMPERR_SUCCESS != netsnmp_inject_handler(reg, handler)) {
        snmp_log(LOG_ERR,"error injecting container_table handler for "
                 MYTABLE "\n");
        goto bail;
    }
    handler = NULL; /* reg has it, will reuse below */

    /*************************************************
     *
     * inject cache helper
     */
    cache = netsnmp_cache_create(30,    /* timeout in seconds */
                                 _cache_load, _cache_free,
                                 testDummyTable_oid,
                                 testDummyTable_oid_len);

    if (NULL == cache) {
        snmp_log(LOG_ERR, "error creating cache for "
                 MYTABLE "\n");
        goto bail;
    }
    cache->magic = container;

    handler = netsnmp_cache_handler_get(cache);
    if (NULL == handler) {
        snmp_log(LOG_ERR, "error creating cache handler for "
                 MYTABLE "\n");
        goto bail;
    }
    if (SNMPERR_SUCCESS != netsnmp_inject_handler(reg, handler)) {
        snmp_log(LOG_ERR,"error injecting cache handler for "
                 MYTABLE "\n");
        goto bail;
    }
    handler = NULL; /* reg has it*/

    if (SNMPERR_SUCCESS != netsnmp_register_table(reg, table_info)) {
        snmp_log(LOG_ERR,"error registering table handler for "
                 MYTABLE "\n");
        goto bail;
    }

    return; /* ok */


  bail: /* not ok */
    
    if (handler)
        netsnmp_handler_free(handler);

    if (cache)
        netsnmp_cache_free(cache);

    if (table_info)
        netsnmp_table_registration_info_free(table_info);

    if (container)
        CONTAINER_FREE(container);

    if (reg) 
        netsnmp_handler_registration_free(reg);

}

/** handles requests for the testDummyTable table */
int
testDummyTable_handler(netsnmp_mib_handler *handler,
                           netsnmp_handler_registration *reginfo,
                           netsnmp_agent_request_info *reqinfo,
                           netsnmp_request_info *requests)
{

    netsnmp_request_info *request;
    netsnmp_table_request_info *table_info;
    netsnmp_swinst_entry *table_entry;

    switch (reqinfo->mode) {
        /*
         * Read-support (also covers GetNext requests)
         */
    case MODE_GET:
        for (request = requests; request; request = request->next) {
            if (request->processed)
               continue;
            table_entry = (netsnmp_swinst_entry *)
                netsnmp_container_table_extract_context(request);
            table_info = netsnmp_extract_table_info(request);
            if ((NULL == table_entry) || (NULL == table_info)) {
                snmp_log(LOG_ERR, "could not extract table entry or info for "
                 MYTABLE "\n");
                snmp_set_var_typed_value(request->requestvb,
                                         SNMP_ERR_GENERR, NULL, 0);
                continue;
            }

            switch (table_info->colnum) {
            case COLUMN_TESTDUMMYINDEX:
                snmp_set_var_typed_integer(request->requestvb, ASN_INTEGER,
                                           table_entry->swIndex);
                break;
            case COLUMN_TESTDUMMYNAME: {
                snmp_set_var_typed_value(request->requestvb, ASN_OCTET_STR,
                                         (u_char *) table_entry->swName,
                                         table_entry->swName_len);
                } break;
            case COLUMN_TESTDUMMYID:
                snmp_set_var_typed_value(request->requestvb, ASN_OBJECT_ID,
                                         (u_char *) &nullOid, nullOidLen);
                break;
            case COLUMN_TESTDUMMYTYPE:
                snmp_set_var_typed_integer(request->requestvb, ASN_INTEGER,
                                           table_entry->swType);
                break;
            case COLUMN_TESTDUMMYDATE:
                snmp_set_var_typed_value(request->requestvb, ASN_OCTET_STR,
                                         (u_char *) table_entry->swDate, 
                                         table_entry->swDate_len);
                break;
            default:
                /*
                 * An unsupported/unreadable column (if applicable) 
                 */
                snmp_set_var_typed_value(request->requestvb,
                                         SNMP_NOSUCHOBJECT, NULL, 0);
            }
        }
        break;

    }
    return SNMP_ERR_NOERROR;
}

/***********************************************************************
 *
 * DATA ACCESS
 *
 * The data access mechanism here is rather simple: let newsnmp_swinst_*
 * take care of it.
 ***********************************************************************/
/**
 * @internal
 */
static int
_cache_load(netsnmp_cache * cache, void *vmagic)
{
    DEBUGMSGTL(("testDummyTable:cache", "load\n"));

    if ((NULL == cache) || (NULL == cache->magic)) {
        snmp_log(LOG_ERR, "invalid cache for testDummyTable_cache_load\n");
        return -1;
    }

    /** should only be called for an invalid or expired cache */
    netsnmp_assert((0 == cache->valid) || (1 == cache->expired));

//    cache->magic =
//        netsnmp_swinst_container_load((netsnmp_container *) cache->magic, 0);

    return 0;
}

/**
 * @internal
 */
static void
_cache_free(netsnmp_cache * cache, void *magic)
{
    if ((NULL == cache) || (NULL == cache->magic)) {
        snmp_log(LOG_ERR, "invalid cache in testDummyTable_cache_free\n");
        return;
    }
    DEBUGMSGTL(("testDummyTable:cache", "free\n"));

//    netsnmp_swinst_container_free_items((netsnmp_container *) cache->magic);
}
