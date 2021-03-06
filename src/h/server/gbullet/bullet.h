/*	@(#)bullet.h	1.1	96/02/27 10:35:39 */
/*
 * Copyright 1994 Vrije Universiteit, The Netherlands.
 * For full copyright and restrictions on use see the file COPYRIGHT in the
 * top level of the Amoeba distribution.
 */

#ifndef __BULLET_H__
#define __BULLET_H__

/*
**	Constants used in both the bullet server and in the client stubs.
**	cmdreg.h defines the first error number and command codes for
**	the bullet server.
**
**   Author:
**	Greg Sharp 05-01-89
*/

/* Tunable Constants */
/*********************/

/*
** Size of Bullet Server's getreq buffer in bytes.
** Tuned to Ethernet:
** Ethernet packets have 1490 bytes
** Amoeba 3: first packet has 32 byte header, max trans size is 30000 bytes.
*/
#define	BS_REQBUFSZ		((1490 - sizeof (header)) + (19 * 1490))

/*
** When the bullet server starts up it tries to allocate most of the memory
** in the machine.  It does however leave up to BS_MEM_RESERVE bytes for
** use by the kernel and user processes.  It is in a #ifndef so that you
** can override it with a -D option on a command line.
*/
#ifndef BS_MEM_RESERVE
#	define	BS_MEM_RESERVE		0x300000
#endif

/* Number of sweep times over which to measure the load in sweeper thread. */
#define	BS_LOAD_BASE		2

/* Number of milliseconds between sweeps of the cache */
#define	BS_SWEEP_TIME		60000

/*
** Timeout for uncommitted files.
** It is a multiple of the BS_SWEEP_TIME - so the timeout will be
** (BS_CACHE_TIMEOUT * BS_SWEEP_TIME) milliseconds.
*/
#define BS_CACHE_TIMEOUT	10

/*
** A useful number for deciding a sensible number of inodes or cache slots
** to allocate.  The minimum number of cache slots is also a useful number.
*/
#define	AVERAGE_FILE_SIZE	(16*1024)
#define	BS_MIN_CACHE_SLOTS	1024

/* The Minimum amount of memory for cache that we require to run. */
#ifndef BS_MIN_MEMORY
#define	BS_MIN_MEMORY		(3*1024*1024) /* 3 Megabytes */
#endif

/* The threshold in free blocks below which we try to defer to others */
#ifndef BS_DEFER_THRESHOLD
#define	BS_DEFER_THRESHOLD	(Superblock.s_numblocks/10)
#endif

/* The number of time we retry when we get rpc_failure during replication */
#ifndef BS_RPC_RETRY
#define BS_RPC_RETRY		5
#endif

/* The number of blocks below which we try to avoid placing replica's
 * on a server.
 * The routine bs_rep contains further criteria.
 */
#ifndef BS_REP_AVOID
#define BS_REP_AVOID		100
#endif

#ifndef BS_PEER_MAP_TYPE
#define BS_PEER_MAP_TYPE	unsigned char
#endif

/* NON-Tunable stuff */
/*********************/

/* the name of the bullet server supercapability directory entry */
#define	BULLET_SVR_NAME		"bullet"

/* parameter names for std_[gs]etparams on group cap */
	/* Default replication factor */
#define	BS_REP_FACTOR	"replication factor"
	/* Repl. when SAFETY is on */
#define	BS_SAFETY_REPL	"safety replication"
	/* Log capability */
#define	BS_LOG_SERVER	"log server"

/* parameter names for std_[sg]etparams on member caps */
	/* Debug level */
#define BS_DEBUG_LEVEL	"debug level"
	/* Messages to be written to log server */
#define BS_MSG_LOGGING	"message logging"
	/* Message printing on console */
#define BS_MSG_PRINTING	"message printing"
	

/* Bullet File Size */
typedef	long			b_fsize;

#define	DEC_FILE_SIZE_BE(x)	dec_l_be(x)
#define	ENC_FILE_SIZE_BE(x)	enc_l_be(x)

#define	buf_put_bfsize		buf_put_int32
#define	buf_get_bfsize		buf_get_int32

/* Maximum size of Bullet Server's status message in bytes */
#define	BS_STATUS_SIZE		1024

/* Commit flags */
#define	BS_COMMIT		0x1
#define	BS_SAFETY		0x2

/* Flags to bs_state */
#define BS_TESTSTABLE		0x0	/* No action, flags only */
#define BS_EXIT			0x1	/* Stop current invocation */
#define BS_PASSIVE		0x2	/* Get passive */
#define BS_DETACH		0x3	/* To be removed for ever */
#define BS_CAIN			0x4	/* exit if not in same group */
#define BS_STATE_MASK		0xFF	/* Flag for the above */
#define BS_STATE_FORCE		0x100	/* Do even if not all present */

/*
** Macro to convert bytes to blocks: s=size in bytes
*/
#define	NUMBLKS(s)		(((s) + Blksizemin1) >> Superblock.s_blksize)

/*
** Macro to round a byte count up to the nearest block size.
** s = destination for result AND size in bytes
*/
#define CEILING_BLKSZ(s)	{ register b_fsize bmin1 = Blksizemin1;	\
				  if ((s) & bmin1)			\
				     s = ((s) + bmin1) & ~bmin1;	\
				}

/* Bullet Server's Commands */
#define BS_USER_LAST_COM	(BULLET_FIRST_COM +29)
#define BS_ADM_FIRST_COM	(BS_USER_LAST_COM + 1)
#define BS_GRP_FIRST_COM	(BS_ADM_FIRST_COM +30)

#define	BS_CREATE		(BULLET_FIRST_COM + 1)
#define	BS_DELETE		(BULLET_FIRST_COM + 2)
#define	BS_FSCK			(BULLET_FIRST_COM + 3)
#define	BS_INSERT		(BULLET_FIRST_COM + 4)
#define	BS_MODIFY		(BULLET_FIRST_COM + 5)
#define	BS_READ			(BULLET_FIRST_COM + 6)
#define	BS_SIZE			(BULLET_FIRST_COM + 7)
#define	BS_DISK_COMPACT		(BULLET_FIRST_COM + 8)
#define BS_SYNC			(BULLET_FIRST_COM + 9)
#define BS_REPCHK		(BULLET_FIRST_COM +10)
#define BS_ATTACH		(BULLET_FIRST_COM +11)
#define BS_STATE		(BULLET_FIRST_COM +12)

/* Internal Group Bullet Commands */
#define BS_WELCOME		(BS_ADM_FIRST_COM    )
#define BS_REPLICATE		(BS_ADM_FIRST_COM + 1)
#define BS_UPDATE		(BS_ADM_FIRST_COM + 2)

/* Internal Group Bullet Broadcast commands */
#define BS_GRP_CONFIG		(BS_GRP_FIRST_COM)
#define BS_INODES		(BS_GRP_FIRST_COM + 1)
#define BS_RESOURCES		(BS_GRP_FIRST_COM + 2)
#define BS_CHECKLIFE		(BS_GRP_FIRST_COM + 3)
#define BS_SETLIFES		(BS_GRP_FIRST_COM + 4)
#define BS_AGE_DELAY		(BS_GRP_FIRST_COM + 5)

/* Bullet Server's Error Codes (none at present) */


/*
** Rights flags for bullet server.
** NB: ADMIN bit is only valid in supercap
*/
#define	BS_RGT_CREATE		((rights_bits) 0x01)
#define	BS_RGT_READ		((rights_bits) 0x02)
#define	BS_RGT_MODIFY		((rights_bits) 0x04)
#define	BS_RGT_DESTROY		((rights_bits) 0x08)
#define BS_RGT_ADMIN		((rights_bits) 0x80)
#define	BS_RGT_ALL		((rights_bits) PRV_ALL_RIGHTS)

/*
** Declaration of stubs for those that want to use them
*/

/* renaming first */
#define b_create        _b_create
#define b_delete        _b_delete
#define b_disk_compact  _b_disk_compact
#define b_fsck          _b_fsck
#define b_insert        _b_insert
#define b_modify        _b_modify
#define b_read          _b_read
#define b_size          _b_size
#define b_sync          _b_sync
#define gb_attach       _gb_attach
#define gb_repchk       _gb_repchk
#define gb_state        _gb_state

/* Then prototypes */
extern errstat	b_create _ARGS((capability *, char *, b_fsize,
						int, capability *));
extern errstat	b_delete _ARGS((capability *, b_fsize, b_fsize,
						int, capability *));
extern errstat	b_disk_compact _ARGS((capability *));
extern errstat	b_fsck _ARGS((capability *));
extern errstat	b_insert _ARGS((capability *, b_fsize, char *,
						b_fsize, int, capability *));
extern errstat	b_modify _ARGS((capability *, b_fsize, char *,
						b_fsize, int, capability *));
extern errstat	b_read _ARGS((capability *, b_fsize, char *,
						b_fsize, b_fsize *));
extern errstat	b_size _ARGS((capability *, b_fsize *));
extern errstat	b_sync _ARGS((capability *));
extern errstat	gb_attach _ARGS((capability *, capability *));
extern errstat	gb_repchk _ARGS((capability *));
extern errstat	gb_state _ARGS((capability *, int member, int flag));

#endif /* __BULLET_H__ */
