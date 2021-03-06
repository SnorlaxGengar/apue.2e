#include "apue.h"
#include <errno.h>
#include "stropts.h"

#define	BUFFSIZE	4096

/* Copyright (C) 1998 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

int __set_errno(int n)
{
    errno = n;
    return -1;
}

int
getmsg (fildes, ctlptr, dataptr, flagsp)
     int fildes;
     struct strbuf *ctlptr;
     struct strbuf *dataptr;
     int *flagsp;
{
  __set_errno (ENOSYS);
  return -1;
}

int
main(void)
{
	int				n, flag;
	char			ctlbuf[BUFFSIZE], datbuf[BUFFSIZE];
	struct strbuf	ctl, dat;

	ctl.buf = ctlbuf;
	ctl.maxlen = BUFFSIZE;
	dat.buf = datbuf;
	dat.maxlen = BUFFSIZE;
	for ( ; ; ) {
		flag = 0;		/* return any message */
		if ((n = getmsg(STDIN_FILENO, &ctl, &dat, &flag)) < 0)
			err_sys("getmsg error");
		fprintf(stderr, "flag = %d, ctl.len = %d, dat.len = %d\n",
		  flag, ctl.len, dat.len);
		if (dat.len == 0)
			exit(0);
		else if (dat.len > 0)
			if (write(STDOUT_FILENO, dat.buf, dat.len) != dat.len)
				err_sys("write error");
	}
}

