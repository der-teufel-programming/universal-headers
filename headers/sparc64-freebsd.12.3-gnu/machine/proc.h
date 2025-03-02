/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1991 Regents of the University of California.
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
 * 3. Neither the name of the University nor the names of its contributors
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
 *
 *      from: @(#)proc.h        7.1 (Berkeley) 5/15/91
 *	from: FreeBSD: src/sys/i386/include/proc.h,v 1.11 2001/06/29
 * $FreeBSD: releng/12.3/sys/sparc64/include/proc.h 326023 2017-11-20 19:43:44Z pfg $
 */

#ifndef	_MACHINE_PROC_H_
#define	_MACHINE_PROC_H_

#include <machine/utrap.h>

struct md_utrap {
	utrap_entry_t *ut_precise[UT_MAX];	/* must be first */
	int	ut_refcnt;
};

struct mdthread {
	int	md_spinlock_count;	/* (k) */
	register_t md_saved_pil;	/* (k) */
};

struct mdproc {
	struct	md_utrap *md_utrap;
	void	*md_sigtramp;
};

#define	KINFO_PROC_SIZE 1088

struct syscall_args {
	u_int code;
	struct sysent *callp;
	register_t args[8];
	int narg;
};

#ifdef _KERNEL

#include <machine/pcb.h>

/* Get the current kernel thread stack usage. */
#define	GET_STACK_USAGE(total, used) do {				\
	struct thread *td = curthread;					\
	(total) = td->td_kstack_pages * PAGE_SIZE - sizeof(struct pcb);	\
	(used) = (char *)td->td_kstack +				\
	    td->td_kstack_pages * PAGE_SIZE -				\
	    (char *)&td;						\
} while (0)

#endif

#endif /* !_MACHINE_PROC_H_ */
