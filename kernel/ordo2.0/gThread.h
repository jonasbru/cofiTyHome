#ifndef GTHREAD_H_
#define GTHREAD_H_

#include "gSetJmp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

#define TRUE 1
#define FALSE 0

/* machine context data structure */
/* save machine context */
#define mctx_save(mctx) gSetJmp((mctx)->jb)

/* restore machine context */
#define mctx_restore(mctx) gLongJmp((mctx)->jb, 1)

/* switch machine context */
#define mctx_switch(mctx_old,mctx_new)  \
	if (gSetJmp((mctx_old)->jb) == 0)  \
		gLongJmp((mctx_new)->jb, 1)

typedef struct mctx_st
{
	gBuffer jb;
        int toDelete;
}mctx_t;


void mctx_create(mctx_t *mctx, void (*sf_addr)(void*),
		void *sf_arg, void *sk_addr, size_t sk_size);


void yield();

#endif /* GTHREAD_H_ */
