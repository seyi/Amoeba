/*	@(#)bsync.c	1.4	96/02/27 10:11:53 */
/*
 * Copyright 1994 Vrije Universiteit, The Netherlands.
 * For full copyright and restrictions on use see the file COPYRIGHT in the
 * top level of the Amoeba distribution.
 */

/*
** bsync
**
**  Sync all the committed bullet files to disk.  This is useful for
**  shutting down a bullet server.
**
**  Author:  Gregory J. Sharp, June 1991
*/

#include "amoeba.h"
#include "cmdreg.h"
#include "stderr.h"
#include "module/name.h"
#include "ampolicy.h"
#include "bullet/bullet.h"

#include "stdio.h"
#include "stdlib.h"

errstat	b_sync();


main(argc, argv)
int	argc;
char *	argv[];
{
    char *	capname;
    capability	cap;
    errstat	err;

    if (argc == 1)
	capname = DEF_BULLETSVR;
    else
	if (argc == 2)
	    capname = argv[1];
	else
	{
	    fprintf(stderr, "Usage: %s [bullet-supercap]; default is %s\n",
		    argv[0], DEF_BULLETSVR);
	    exit(1);
	}
    
    if ((err = name_lookup(capname, &cap)) != STD_OK)
    {
	fprintf(stderr, "%s: directory lookup of '%s' failed: %s\n",
					argv[0], capname, err_why(err));
	exit(1);
    }
    if ((err = b_sync(&cap)) != STD_OK)
    {
	fprintf(stderr, "%s: failed: %s\n", argv[0], err_why(err));
	exit(1);
    }
    exit(0);
}
