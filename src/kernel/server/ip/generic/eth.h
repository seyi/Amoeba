/*	@(#)eth.h	1.3	96/02/27 14:16:02 */
/*
eth.h

Copyright 1995 Philip Homburg
*/

#ifndef ETH_H
#define ETH_H

#define NWEO_DEFAULT    (NWEO_EN_LOC | NWEO_DI_BROAD | NWEO_DI_MULTI | \
	NWEO_DI_PROMISC | NWEO_REMANY | NWEO_RWDATALL)

#define ETH0	0	/* port number of ethernet port 0 */
#define ETH1	1	/* port number of ethernet port 1 */

#define eth_addrcmp(a,b) (memcmp((_VOIDSTAR)&a, (_VOIDSTAR)&b, \
	sizeof(a)))

/* Forward declatations */

struct acc;

/* prototypes */

void eth_init ARGS(( void ));
int eth_open ARGS(( int port, int srfd,
	get_userdata_t get_userdata, put_userdata_t put_userdata,
	put_pkt_t put_pkt ));
int eth_ioctl ARGS(( int fd, unsigned long req));
int eth_read ARGS(( int port, size_t count ));
int eth_write ARGS(( int port, size_t count ));
int eth_cancel ARGS(( int fd, int which_operation ));
void eth_close ARGS(( int fd ));
int eth_send ARGS(( int port, struct acc *data, size_t data_len ));

#endif /* ETH_H */

/*
 * $PchId: eth.h,v 1.5 1995/11/21 06:45:27 philip Exp $
 */
