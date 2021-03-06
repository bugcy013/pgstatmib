/*
 * pgstatServer MIB group interface
 *
 * Note: this file originally auto-generated by mib2c
 */
#ifndef PGSTATSERVER_H
#define PGSTATSERVER_H

/* module name */
#define PGSTATSERVER_NAME	"pgstatServer"

#define PGSTATSERVER_CACHE_TIMEOUT	30	// in seconds

/* structures */
typedef struct {
	u_int	database_count;
	u_long	total_size;
	u_int	total_backends;
	u_long	total_commits;
	u_long	total_rollbacks;
	u_long	total_blks_read;
	u_long	total_blks_hit;
	u_int	rollback_ratio;
	u_int	cache_hit_ratio;
	time_t last_load; // for caching control
} pgstatServerData;

/*
 * function declarations 
 */
void            init_pgstatServer(void);
void 			refresh_numbers_pgstatServer(void);
void 			load_numbers_from_db_pgstatServer(void);
FindVarMethod   getvalue_pgstatServer;

/* scalar number definitions */
#define PGSTATSERVER_DATABASECOUNT		1
#define PGSTATSERVER_TOTALSIZE			2
#define PGSTATSERVER_TOTALBACKENDS		3
#define PGSTATSERVER_TOTALCOMMITS		4
#define PGSTATSERVER_TOTALROLLBACKS		5
#define PGSTATSERVER_TOTALBLOCKSREAD		6
#define PGSTATSERVER_TOTALBLOCKSHIT		7
#define PGSTATSERVER_ROLLBACKRATIO		8
#define PGSTATSERVER_CACHEHITRATIO		9

#define PGSTATSERVER_FIRST		PGSTATSERVER_DATABASECOUNT
#define PGSTATSERVER_LAST		PGSTATSERVER_CACHEHITRATIO

#endif	/* PGSTATSERVER_H */

