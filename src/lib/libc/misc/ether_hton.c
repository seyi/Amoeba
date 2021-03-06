/*	@(#)ether_hton.c	1.3	94/04/07 10:47:45 */
/*
 * Copyright 1994 Vrije Universiteit, The Netherlands.
 * For full copyright and restrictions on use see the file COPYRIGHT in the
 * top level of the Amoeba distribution.
 */

/*
**	ETHER_HOSTTON
**
**	This routine takes a host name and looks it up in the ethers
**	file (as defined in ampolicy.h) and returns in "eaddr" the
**	ethernet address of the host.
**	The function returns 0 on success and non-zero on failure.
**
**	Author: Gregory J. Sharp, Nov 1991
*/

#include "stdio.h"
#include "amoeba.h"
#include "cmdreg.h" 
#include "stderr.h"
#include "ampolicy.h"
#include "stdlib.h"
#include "ether_addr.h"
#include "bullet/bullet.h"
#include "module/name.h"

int
ether_hostton(hostname, eaddr)
char *			hostname;	/* in: user supplied buffer */
struct ether_addr *	eaddr;		/* out: address of required machine */
{
    capability	ethers_file;
    b_fsize	size;
    b_fsize	nbytes;
    errstat	err;
    char *	buf;
    char *	bp;

    /* Get capability for ethers file  & bullet server */
    if ((err = name_lookup(ETHERS_FILE, &ethers_file)) != STD_OK)
    {
	fprintf(stderr, "Can't lookup '%s': %s\n", ETHERS_FILE, err_why(err));
	return 1;
    }

    /* Read the entire file into core - it should fit in memory */
    if ((err = b_size(&ethers_file, &size)) != STD_OK)
    {
	fprintf(stderr, "Can't read '%s': %s\n", ETHERS_FILE, err_why(err));
	return 1;
    }
    
    /*
    ** We allocate one byte extra for a null byte to terminate the file
    */
    if ((buf = (char *) malloc((size_t) size+1)) == 0)
	return 1;
    
    if ((err = b_read(&ethers_file, (b_fsize) 0, buf, size, &nbytes)) != STD_OK)
    {
	fprintf(stderr, "Read of '%s' failed: %s\n", ETHERS_FILE, err_why(err));
	free(buf);
	return 1;
    }

    if (size != nbytes) /* read didn't return all the data - don't trust it */
    {
	free(buf);
	return 1;
    }

    /*
    ** Now we process the file, searching for the line whose host name
    ** matches.
    */

    *(buf+size) = '\0';
    bp = buf;
    while (*bp)
    {
	char hname[256]; /* ethernet address on current line of input */

	if (ether_line(bp, eaddr, hname) == 0 && strcmp(hname, hostname) == 0)
	{
	    free(buf);
	    return 0;
	}
	/* Else skip to the start of the next line and try again */
	while (*bp && *bp++ != '\n')
	    ; /* do nothing */
    }
    free(buf);
    return 1;
}
