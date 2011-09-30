/*
 * Note: this file originally auto-generated by mib2c
 */

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/net-snmp-agent-includes.h>
#include <net-snmp/agent/table_container.h>

#include <net-snmp/library/container.h>

#include "pgstatDatabaseTable.h"

#ifdef USE_CACHE
static void     _cache_free(netsnmp_cache * cache, void *magic);
static int      _cache_load(netsnmp_cache * cache, void *vmagic);
#endif

/** Initializes the pgstatDatabaseTable module */
void
init_pgstatDatabaseTable(void)
{
    /*
     * here we initialize all the tables we're planning on supporting 
     */
    initialize_table_pgstatDatabaseTable();
}

/** Initialize the pgstatDatabaseTable table by defining its contents and how it's structured */
void
initialize_table_pgstatDatabaseTable(void)
{
    const oid       pgstatDatabaseTable_oid[] = { 1, 3, 6, 1, 4, 1, 27645, 3, 1 };
    const size_t    pgstatDatabaseTable_oid_len = OID_LENGTH(pgstatDatabaseTable_oid);

    netsnmp_handler_registration *reg = NULL;
    netsnmp_mib_handler *handler = NULL;
    netsnmp_container *container = NULL;
    netsnmp_table_registration_info *table_info = NULL;
#ifdef USE_CACHE
    netsnmp_cache  *cache = NULL;
#endif

    DEBUGMSGTL(("pgstatDatabaseTable:init",
                "initializing table pgstatDatabaseTable\n"));

    reg =
        netsnmp_create_handler_registration("pgstatDatabaseTable",
                                            pgstatDatabaseTable_handler,
                                            pgstatDatabaseTable_oid,
                                            pgstatDatabaseTable_oid_len,
                                            HANDLER_CAN_RONLY);
    if (NULL == reg) {
        snmp_log(LOG_ERR,
                 "error creating handler registration for pgstatDatabaseTable\n");
        goto bail;
    }

    container =
        netsnmp_container_find("pgstatDatabaseTable:table_container");
    if (NULL == container) {
        snmp_log(LOG_ERR,
                 "error creating container for pgstatDatabaseTable\n");
        goto bail;
    }

    table_info = SNMP_MALLOC_TYPEDEF(netsnmp_table_registration_info);
    if (NULL == table_info) {
        snmp_log(LOG_ERR,
                 "error allocating table registration for pgstatDatabaseTable\n");
        goto bail;
    }
    netsnmp_table_helper_add_indexes(table_info, ASN_INTEGER,   /* index: pgstatDatabaseId */
                                     0);
    table_info->min_column = COLUMN_PGSTATDATABASEID;
    table_info->max_column = COLUMN_PGSTATDATABASETUPLESMODIFIED;

    /*
     * inject container_table helper
     */
    handler = netsnmp_container_table_handler_get(table_info, container,
                                                  TABLE_CONTAINER_KEY_NETSNMP_INDEX);
    if (NULL == handler) {
        snmp_log(LOG_ERR,
                 "error allocating table registration for pgstatDatabaseTable\n");
        goto bail;
    }
    if (SNMPERR_SUCCESS != netsnmp_inject_handler(reg, handler)) {
        snmp_log(LOG_ERR,
                 "error injecting container_table handler for pgstatDatabaseTable\n");
        goto bail;
    }
    handler = NULL;             /* reg has it, will reuse below */

#ifdef USE_CACHE
    /*
     * inject cache helper
     */
    cache = netsnmp_cache_create(30,    /* timeout in seconds */
                                 _cache_load, _cache_free,
                                 pgstatDatabaseTable_oid,
                                 pgstatDatabaseTable_oid_len);

    if (NULL == cache) {
        snmp_log(LOG_ERR,
                 "error creating cache for pgstatDatabaseTable\n");
        goto bail;
    }
    cache->flags = NETSNMP_CACHE_DONT_INVALIDATE_ON_SET;
    cache->magic = container;

    handler = netsnmp_cache_handler_get(cache);
    if (NULL == handler) {
        snmp_log(LOG_ERR,
                 "error creating cache handler for pgstatDatabaseTable\n");
        goto bail;
    }

    if (SNMPERR_SUCCESS != netsnmp_inject_handler(reg, handler)) {
        snmp_log(LOG_ERR,
                 "error injecting cache handler for pgstatDatabaseTable\n");
        goto bail;
    }
    handler = NULL;             /* reg has it */
#endif

    /*
     * register the table
     */
    if (SNMPERR_SUCCESS != netsnmp_register_table(reg, table_info)) {
        snmp_log(LOG_ERR,
                 "error registering table handler for pgstatDatabaseTable\n");
        goto bail;
    }

    /*
     * Initialise the contents of the table here
     */


    return;                     /* ok */

    /*
     * Some error occurred during registration. Clean up and bail.
     */
  bail:                        /* not ok */

    if (handler)
        netsnmp_handler_free(handler);

#ifdef USE_CACHE
    if (cache)
        netsnmp_cache_free(cache);
#endif

    if (table_info)
        netsnmp_table_registration_info_free(table_info);

    if (container)
        CONTAINER_FREE(container);

    if (reg)
        netsnmp_handler_registration_free(reg);
}

/** Typical data structure for a row entry */
typedef struct pgstatDatabaseTable_entry_s {
    netsnmp_index   oid_index;

    /*
     * Index values 
     */
    long            pgstatDatabaseId;

    /*
     * Column values 
     */
    //long            pgstatDatabaseId;
    char            pgstatDatabaseName[64];
    size_t          pgstatDatabaseName_len;
    u_long          pgstatDatabaseBackends;
    u_long          pgstatDatabaseCommits;
    u_long          pgstatDatabaseRollbacks;
    u_long          pgstatDatabaseBlocksRead;
    u_long          pgstatDatabaseBlocksHit;
    u_long          pgstatDatabaseTuplesReturned;
    u_long          pgstatDatabaseTuplesFetched;
    u_long          pgstatDatabaseTuplesInserted;
    u_long          pgstatDatabaseTuplesUpdated;
    u_long          pgstatDatabaseTuplesDeleted;
    u_long          pgstatDatabaseSizeMB;
    u_long          pgstatDatabaseRollbackRatio;
    u_long          pgstatDatabaseCacheHitRatio;
    u_long          pgstatDatabaseTuplesModified;

    int             valid;
} pgstatDatabaseTable_entry;

/** create a new row in the table */
pgstatDatabaseTable_entry *
pgstatDatabaseTable_createEntry(netsnmp_container * container, //,
                                long pgstatDatabaseId)
{
    pgstatDatabaseTable_entry *entry;

    entry = SNMP_MALLOC_TYPEDEF(pgstatDatabaseTable_entry);
    if (!entry)
        return NULL;

    entry->pgstatDatabaseId = pgstatDatabaseId;
    entry->oid_index.len = (int) NULL; //XXX;
    entry->oid_index.oids = (int) NULL; //YYY;

    CONTAINER_INSERT(container, entry);
    return entry;
}

/** remove a row from the table */
void
pgstatDatabaseTable_removeEntry(netsnmp_container * container,
                                pgstatDatabaseTable_entry * entry)
{

    if (!entry)
        return;                 /* Nothing to remove */
    CONTAINER_REMOVE(container, entry);
    if (entry)
        SNMP_FREE(entry);       /* XXX - release any other internal resources */
}

/** remove a row from the table */
void
pgstatDatabaseTable_freeEntry(pgstatDatabaseTable_entry * entry)
{

    if (!entry)
        return;                 /* Nothing to remove */
    SNMP_FREE(entry);           /* XXX - release any other internal resources */
}

/** handles requests for the pgstatDatabaseTable table */
int
pgstatDatabaseTable_handler(netsnmp_mib_handler *handler,
                            netsnmp_handler_registration *reginfo,
                            netsnmp_agent_request_info *reqinfo,
                            netsnmp_request_info *requests)
{

    netsnmp_request_info *request;
    netsnmp_table_request_info *table_info;
    netsnmp_container *container;
    pgstatDatabaseTable_entry *table_entry;

    DEBUGMSGTL(("pgstatDatabaseTable:handler", "Processing request (%d)\n",
                reqinfo->mode));

    switch (reqinfo->mode) {
    /*
     * Read-support (also covers GetNext requests)
     */
    case MODE_GET:
        for (request = requests; request; request = request->next) {
            if (request->processed)
                continue;
            table_entry = (pgstatDatabaseTable_entry *)
                netsnmp_container_table_extract_context(request);
            table_info = netsnmp_extract_table_info(request);
            if ((NULL == table_entry) || (NULL == table_info)) {
                snmp_log(LOG_ERR,
                         "could not extract table entry or info for pgstatDatabaseTable\n");
                snmp_set_var_typed_value(request->requestvb,
                                         SNMP_ERR_GENERR, NULL, 0);
                continue;
            }

            switch (table_info->colnum) {
            case COLUMN_PGSTATDATABASEID:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb, ASN_INTEGER,
                                           table_entry->pgstatDatabaseId);
                break;
            case COLUMN_PGSTATDATABASENAME:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_value(request->requestvb, ASN_OCTET_STR,
                                         table_entry->pgstatDatabaseName,
                                         table_entry->
                                         pgstatDatabaseName_len);
                break;
            case COLUMN_PGSTATDATABASEBACKENDS:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb, ASN_GAUGE,
                                           table_entry->
                                           pgstatDatabaseBackends);
                break;
            case COLUMN_PGSTATDATABASECOMMITS:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb, ASN_COUNTER,
                                           table_entry->
                                           pgstatDatabaseCommits);
                break;
            case COLUMN_PGSTATDATABASEROLLBACKS:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb, ASN_COUNTER,
                                           table_entry->
                                           pgstatDatabaseRollbacks);
                break;
            case COLUMN_PGSTATDATABASEBLOCKSREAD:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb, ASN_COUNTER,
                                           table_entry->
                                           pgstatDatabaseBlocksRead);
                break;
            case COLUMN_PGSTATDATABASEBLOCKSHIT:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb, ASN_COUNTER,
                                           table_entry->
                                           pgstatDatabaseBlocksHit);
                break;
            case COLUMN_PGSTATDATABASETUPLESRETURNED:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb, ASN_COUNTER,
                                           table_entry->
                                           pgstatDatabaseTuplesReturned);
                break;
            case COLUMN_PGSTATDATABASETUPLESFETCHED:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb, ASN_COUNTER,
                                           table_entry->
                                           pgstatDatabaseTuplesFetched);
                break;
            case COLUMN_PGSTATDATABASETUPLESINSERTED:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb, ASN_COUNTER,
                                           table_entry->
                                           pgstatDatabaseTuplesInserted);
                break;
            case COLUMN_PGSTATDATABASETUPLESUPDATED:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb, ASN_COUNTER,
                                           table_entry->
                                           pgstatDatabaseTuplesUpdated);
                break;
            case COLUMN_PGSTATDATABASETUPLESDELETED:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb, ASN_COUNTER,
                                           table_entry->
                                           pgstatDatabaseTuplesDeleted);
                break;
            case COLUMN_PGSTATDATABASESIZEMB:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb,
                                           ASN_UNSIGNED,
                                           table_entry->
                                           pgstatDatabaseSizeMB);
                break;
            case COLUMN_PGSTATDATABASEROLLBACKRATIO:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb,
                                           ASN_UNSIGNED,
                                           table_entry->
                                           pgstatDatabaseRollbackRatio);
                break;
            case COLUMN_PGSTATDATABASECACHEHITRATIO:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb,
                                           ASN_UNSIGNED,
                                           table_entry->
                                           pgstatDatabaseCacheHitRatio);
                break;
            case COLUMN_PGSTATDATABASETUPLESMODIFIED:
                if (!table_entry) {
                    netsnmp_set_request_error(reqinfo, request,
                                              SNMP_NOSUCHINSTANCE);
                    continue;
                }
                snmp_set_var_typed_integer(request->requestvb, ASN_COUNTER,
                                           table_entry->
                                           pgstatDatabaseTuplesModified);
                break;
            default:
                netsnmp_set_request_error(reqinfo, request,
                                          SNMP_NOSUCHOBJECT);
                break;
            }
        }
        break;

    }
    return SNMP_ERR_NOERROR;
}

#ifdef USE_CACHE
/**
 * @internal
 */
static int
_cache_load(netsnmp_cache * cache, void *vmagic)
{
    netsnmp_container *container;

    DEBUGMSGTL(("internal:pgstatDatabaseTable:_cache_load", "called\n"));

    if ((NULL == cache) || (NULL == cache->magic)) {
        snmp_log(LOG_ERR,
                 "invalid cache for pgstatDatabaseTable_cache_load\n");
        return -1;
    }
    container = (netsnmp_container *) cache->magic;

    /** should only be called for an invalid or expired cache */
    netsnmp_assert((0 == cache->valid) || (1 == cache->expired));

    /*
     * load cache here (or call function to do it)
     */
    /** CONTAINER_INSERT(container, record); */

    return 0;
}

/**
 * @Internal
 */
/** remove a row from the table */
static void
pgstatDatabaseTable_freeEntry_cb(pgstatDatabaseTable_entry * entry,
                                 void *magic)
{

    pgstatDatabaseTable_freeEntry(entry);
}

/**
 * @internal
 */
static void
_cache_free(netsnmp_cache * cache, void *magic)
{
    netsnmp_container *container;

    DEBUGMSGTL(("internal:pgstatDatabaseTable:_cache_free", "called\n"));

    if ((NULL == cache) || (NULL == cache->magic)) {
        snmp_log(LOG_ERR,
                 "invalid cache in pgstatDatabaseTable_cache_free\n");
        return;
    }
    container = (netsnmp_container *) cache->magic;

    /*
     * empty (but don't free) cache here
     */
    CONTAINER_CLEAR(container,
                    (netsnmp_container_obj_func *)
                    pgstatDatabaseTable_freeEntry_cb, NULL);
}

#endif	/* USE_CACHE */
