/*	@(#)gmon.c	1.2	96/02/27 11:13:45 */
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if 0
#ifndef lint
static char sccsid[] = "@(#)gmon.c	5.3 (Berkeley) 5/22/91";
#endif /* not lint */
#endif

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#ifdef DEBUG
#include <stdio.h>
#endif

#include "gmon.h"

#ifndef AMOEBA
extern void mcount(); /* asm ("mcount"); */
/* extern */ char *minbrk; /* asm ("_minbrk"); */
#else  /* AMOEBA */
#include <stdlib.h>
#include <amoeba.h>
#include <stderr.h>
#include <module/profiling.h>
#define  _POSIX_SOURCE
#include <limits.h>
#ifdef __sparc__
#include <fastmutex.h>
#endif
extern void _mcount();
#endif /* AMOEBA */

/*
 *	froms is actually a bunch of unsigned shorts indexing tos
 */
static int		profiling = 3;
static unsigned short	*froms;
static struct tostruct	*tos = 0;
static long		tolimit = 0;
static char		*s_lowpc = 0;
static char		*s_highpc = 0;
static unsigned long	s_textsize = 0;

static int	ssiz;
static char	*sbuf;
static int	s_scale;
    /* see profil(2) where this is describe (incorrectly) */
#define		SCALE_1_TO_1	0x10000L

#ifdef AMOEBA
#include <amoeba.h>
#include <module/mutex.h>

/* Unfortunately we need a lock to avoid problems with preemptively
 * scheduled programs.
 */
static mutex profile_lock;
#endif

/*
 * Control profiling
 *	profiling is what mcount checks to see if
 *	all the data structures are ready.
 */
void
moncontrol(mode)
    int mode;
{
    int ret;
    static int warned = 0;
#ifdef AMOEBA
    struct profile_parms parms;
#endif

    if (mode) {
	/* start */
#ifndef AMOEBA
	ret = profil(sbuf + sizeof(struct phdr), ssiz - sizeof(struct phdr),
		(int)s_lowpc, s_scale);
#else
	parms.prof_opcode = PROF_OPC_START;
	parms.prof_buf = sbuf + sizeof(struct phdr);
	parms.prof_bufsize = ssiz - sizeof(struct phdr);
	parms.prof_pc_low = s_lowpc;
	parms.prof_scale = SCALE_1_TO_1;
	parms.prof_rate = 20;
	if (sys_profil(&parms) != STD_OK) {
	    ret = -1;
	    errno = ENOSYS;
	}
	mu_init(&profile_lock);
#endif
	if (ret < 0 && errno == ENOSYS && !warned) {
#   define	PROFIL_WARN	"warning: kernel does not support profiling\n"
		write(2, PROFIL_WARN, sizeof(PROFIL_WARN));
		warned = 1;
	}
	profiling = 0;
    } else {
	/* stop */
#ifndef AMOEBA
	profil((char *)0, 0, 0, 0);
#else
	parms.prof_opcode = PROF_OPC_STOP;
	(void) sys_profil(&parms);
#endif
	profiling = 3;
    }
}

#define	MSG "No space for profiling buffer(s)\n"

void
monstartup(lowpc, highpc)
    char	*lowpc;
    char	*highpc;
{
    int			monsize;
    char		*buffer;
    register int	o;
    struct phdr 	*phdrp;
	/*
	 *	round lowpc and highpc to multiples of the density we're using
	 *	so the rest of the scaling (here and in gprof) stays in ints.
	 */
    lowpc = (char *)
	    ROUNDDOWN((unsigned)lowpc, HISTFRACTION*sizeof(HISTCOUNTER));
    s_lowpc = lowpc;
    highpc = (char *)
	    ROUNDUP((unsigned)highpc, HISTFRACTION*sizeof(HISTCOUNTER));
    s_highpc = highpc;
    s_textsize = highpc - lowpc;
    monsize = (s_textsize / HISTFRACTION) + sizeof(struct phdr);
#ifndef AMOEBA
    buffer = (char *) sbrk( monsize );
    if ( buffer == (char *) -1 ) {
	write( 2 , MSG , sizeof(MSG) );
	return;
    }
    froms = (unsigned short *) sbrk( s_textsize / HASHFRACTION );
    if ( froms == (unsigned short *) -1 ) {
	write( 2 , MSG , sizeof(MSG) );
	froms = 0;
	return;
    }
#else
    buffer = (char *) calloc( (size_t) monsize, (size_t) 1);
    if ( buffer == NULL ) {
	write( 2 , MSG , sizeof(MSG) );
	return;
    }
    froms = (unsigned short *) calloc((size_t) (s_textsize / HASHFRACTION),
				      (size_t) 1);
    if ( froms == NULL ) {
	write( 2 , MSG , sizeof(MSG) );
	return;
    }
#endif
    tolimit = s_textsize * ARCDENSITY / 100;
    if ( tolimit < MINARCS ) {
	tolimit = MINARCS;
    } else if ( tolimit > 65534 ) {
	tolimit = 65534;
    }
#ifndef AMOEBA
    tos = (struct tostruct *) sbrk( tolimit * sizeof( struct tostruct ) );
    if ( tos == (struct tostruct *) -1 ) {
#else
    tos = (struct tostruct *) calloc((size_t)(tolimit*sizeof(struct tostruct)),
				     (size_t) 1);
    if ( tos == NULL ) {
#endif
	write( 2 , MSG , sizeof(MSG) );
	froms = 0;
	tos = 0;
	return;
    }
#ifndef AMOEBA
    minbrk = (char *) sbrk(0);
#endif
    tos[0].link = 0;
    sbuf = buffer;
    ssiz = monsize;
    phdrp = (struct phdr *) buffer;
    phdrp -> lpc = lowpc;
    phdrp -> hpc = highpc;
    phdrp -> ncnt = ssiz;
    monsize -= sizeof(struct phdr);
    if ( monsize <= 0 )
	return;
    o = highpc - lowpc;
    if( monsize < o )
#ifndef hp300
	s_scale = ( (float) monsize / o ) * SCALE_1_TO_1;
#else /* avoid floating point */
    {
	int quot = o / monsize;

	if (quot >= 0x10000)
		s_scale = 1;
	else if (quot >= 0x100)
		s_scale = 0x10000 / quot;
	else if (o >= 0x800000)
		s_scale = 0x1000000 / (o / (monsize >> 8));
	else
		s_scale = 0x1000000 / ((o << 8) / monsize);
    }
#endif
    else
	s_scale = SCALE_1_TO_1;
    moncontrol(1);
}

void
_mcleanup()
{
    int			fd;
    int			fromindex;
    int			endfrom;
    char		*frompc;
    int			toindex;
    struct rawarc	rawarc;

    moncontrol(0);
#ifndef AMOEBA
    fd = creat( "gmon.out" , 0666 );
#else
    {
	char proffile[PATH_MAX];
	char *profdir;

	/* create separate profiles for parallel programs: */
	if ((profdir = getenv("PROFDIR")) != NULL) {
	    sprintf(proffile, "%s/%s.%d", profdir, "gmon.out", getpid());
	} else {
	    sprintf(proffile, "gmon.out");
	}
	fd = creat( proffile , 0666 );
    }
#endif
    if ( fd < 0 ) {
	perror( "mcount: gmon.out" );
	return;
    }
#   ifdef DEBUG
	fprintf( stderr , "[mcleanup] sbuf 0x%x ssiz %d\n" , sbuf , ssiz );
#   endif /* DEBUG */
    write( fd , sbuf , ssiz );
    endfrom = s_textsize / (HASHFRACTION * sizeof(*froms));
    for ( fromindex = 0 ; fromindex < endfrom ; fromindex++ ) {
	if ( froms[fromindex] == 0 ) {
	    continue;
	}
	frompc = s_lowpc + (fromindex * HASHFRACTION * sizeof(*froms));
	for (toindex=froms[fromindex]; toindex!=0; toindex=tos[toindex].link) {
#	    ifdef DEBUG
		fprintf( stderr ,
			"[mcleanup] frompc 0x%x selfpc 0x%x count %d\n" ,
			frompc , tos[toindex].selfpc , tos[toindex].count );
#	    endif /* DEBUG */
	    rawarc.raw_frompc = (unsigned long) frompc;
	    rawarc.raw_selfpc = (unsigned long) tos[toindex].selfpc;
	    rawarc.raw_count = tos[toindex].count;
	    write( fd , (char *) &rawarc , sizeof rawarc );
	}
    }
    close( fd );
}

#if defined(__sparc__)
/* Get the pc from the caller and its parent from the callers window
 * before invoking the real mcount.  Code borrowed from BSD4.4.
 */

__asm__ ("
	.seg	\"text\"
	.align  4
	.global mcount
mcount:
        add %i7, 8, %o0
	sethi %hi(__mcount), %o2
	jmpl %o2 + %lo(__mcount), %g0
	add %o7, 8, %o1

");
#endif /* __sparc__ */

#if defined(i80386) || defined(__i80386__)
/* extern void mcount() __asm__("mcount"); */

void mcount()
{
    int selfpc, frompcindex;

    /*
     * find the return address for mcount,
     * and the return address for mcount's caller.
     *
     * selfpc = pc pushed by mcount call
     */
    __asm__("movl 4(%%ebp),%0" : "=r" (selfpc));

    /*
     * frompcindex = pc pushed by jsr into self.
     * In GCC the caller's stack frame has already been built so we
     * have to chase a6 to find caller's raddr.
     */
    __asm__("movl (%%ebp),%0" : "=r" (frompcindex));
    frompcindex = ((int *)frompcindex)[1];
    _mcount(frompcindex, selfpc);
}
#endif

#if defined(__mc68000__)
extern void mcount() __asm__("mcount");

void mcount()
{
    int selfpc, frompcindex;

    __asm__("movl a6@(4),%0" : "=r" (selfpc));
    __asm__("movl a6@(0)@(4),%0" : "=r" (frompcindex));
    _mcount(frompcindex, selfpc);
}
#endif


void
_mcount(frompcindex, selfpc)
register unsigned short	*frompcindex;
register char		*selfpc;
{
	register struct tostruct	*top;
	register struct tostruct	*prevtop;
	register long			toindex;

	/*
	 *	check that we are profiling
	 *	and that we aren't recursively invoked.
	 */
#ifdef AMOEBA
#ifdef __sparc__
	mu_lock(&profile_lock);
#else
	while (mu_trylock(&profile_lock, -1L) < 0)
		;
#endif
#endif
	if (profiling) {
		goto out;
	}
	profiling++;
	/*
	 *	check that frompcindex is a reasonable pc value.
	 *	for example:	signal catchers get called from the stack,
	 *			not from text space.  too bad.
	 */
	frompcindex = (unsigned short *)((long)frompcindex - (long)s_lowpc);
	if ((unsigned long)frompcindex > s_textsize) {
		goto done;
	}
	frompcindex =
	    &froms[((long)frompcindex) / (HASHFRACTION * sizeof(*froms))];
	toindex = *frompcindex;
	if (toindex == 0) {
		/*
		 *	first time traversing this arc
		 */
		toindex = ++tos[0].link;
		if (toindex >= tolimit) {
			goto overflow;
		}
		*frompcindex = toindex;
		top = &tos[toindex];
		top->selfpc = selfpc;
		top->count = 1;
		top->link = 0;
		goto done;
	}
	top = &tos[toindex];
	if (top->selfpc == selfpc) {
		/*
		 *	arc at front of chain; usual case.
		 */
		top->count++;
		goto done;
	}
	/*
	 *	have to go looking down chain for it.
	 *	top points to what we are looking at,
	 *	prevtop points to previous top.
	 *	we know it is not at the head of the chain.
	 */
	for (; /* goto done */; ) {
		if (top->link == 0) {
			/*
			 *	top is end of the chain and none of the chain
			 *	had top->selfpc == selfpc.
			 *	so we allocate a new tostruct
			 *	and link it to the head of the chain.
			 */
			toindex = ++tos[0].link;
			if (toindex >= tolimit) {
				goto overflow;
			}
			top = &tos[toindex];
			top->selfpc = selfpc;
			top->count = 1;
			top->link = *frompcindex;
			*frompcindex = toindex;
			goto done;
		}
		/*
		 *	otherwise, check the next arc on the chain.
		 */
		prevtop = top;
		top = &tos[top->link];
		if (top->selfpc == selfpc) {
			/*
			 *	there it is.
			 *	increment its count
			 *	move it to the head of the chain.
			 */
			top->count++;
			toindex = prevtop->link;
			prevtop->link = top->link;
			top->link = *frompcindex;
			*frompcindex = toindex;
			goto done;
		}

	}
done:
	profiling--;
	/* and fall through */
out:
#ifdef AMOEBA
	mu_unlock(&profile_lock);
#endif
	return;		/* normal return restores saved registers */

overflow:
	profiling++; /* halt further profiling */
#   define	TOLIMIT	"mcount: tos overflow\n"
	write(2, TOLIMIT, sizeof(TOLIMIT));
	goto out;
}
