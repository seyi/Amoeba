/*	@(#)popen.c	1.2	94/02/09 13:59:54 */
/*
 * (c) copyright 1987 by the Vrije Universiteit, Amsterdam, The Netherlands.
 * See the copyright notice in the ACK home directory, in the file "Copyright".
 */

#define _POSIX_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

static int pids[20];

FILE *
popen(command, type)
	char *command, *type;
{
	int piped[2];
	int Xtype = *type == 'r' ? 0 : *type == 'w' ? 1 : 2;
	int pid;

	if (Xtype == 2 ||
	    pipe(piped) < 0 ||
	    (pid = fork()) < 0) return 0;
	
	if (pid == 0) {
		/* child */
		register int *p;

		for (p = pids; p < &pids[20]; p++) {
			if (*p) close(p - pids);
		}
		close(piped[Xtype]);
		dup2(piped[!Xtype], !Xtype);
		close(piped[!Xtype]);
		execl("/bin/sh", "sh", "-c", command, (char *) 0);
		_exit(127);	/* like system() ??? */
	}

	pids[piped[Xtype]] = pid;
	close(piped[!Xtype]);
	return fdopen(piped[Xtype], type);
}

pclose(iop)
	FILE *iop;
{
	int fd = fileno(iop);
	int status, wret;
	void (*intsave)() = signal(SIGINT, SIG_IGN);
	void (*quitsave)() = signal(SIGQUIT, SIG_IGN);

	fclose(iop);
	while ((wret = wait(&status)) != -1) {
		if (wret == pids[fd]) break;
	}
	if (wret == -1) status = -1;
	signal(SIGINT, intsave);
	signal(SIGQUIT, quitsave);
	pids[fd] = 0;
	return status;
}
