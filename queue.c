/*
** queue.c - Queue management routines
**
** Copyright (c) 2016 Peter Eriksson <pen@lysator.liu.se>
*/

#include <stdio.h>
#include <stdlib.h>

#include "queue.h"


QUEUE *
queue_create(void)
{
    QUEUE *qp;

    qp = malloc(sizeof(*qp));
    if (!qp)
	return NULL;

    pthread_mutex_init(&qp->mtx, NULL);
    pthread_cond_init(&qp->cv, NULL);

    qp->head = qp->tail = NULL;
    return qp;
}


int
queue_put(QUEUE *qp, void *p)
{
    QENTRY *qep;


    if (!qp)
	return -1;
    
    qep = malloc(sizeof(*qep));
    if (!qep)
	return -1;

    qep->p = p;
    qep->next = NULL;
    
    pthread_mutex_lock(&qp->mtx);
    
    if (qp->tail)
    {
	qp->tail->next = qep;
	qp->tail = qep;
    }
    else
	qp->head = qp->tail = qep;

    pthread_cond_signal(&qp->cv);
    pthread_mutex_unlock(&qp->mtx);
    return 0;
}


void *
queue_get(QUEUE *qp)
{
    void *p;
    QENTRY *qep;
    

    if (!qp)
	return NULL;
    
    pthread_mutex_lock(&qp->mtx);
    while ((qep = qp->head) == NULL)
	pthread_cond_wait(&qp->cv, &qp->mtx);

    p = qep->p;
    qp->head = qep->next;
    if (qp->tail == qep)
	qp->tail = NULL;
    pthread_mutex_unlock(&qp->mtx);
    free(qep);

    return p;
}


void
queue_destroy(QUEUE *qp)
{
    QENTRY *qc, *qn;

    for (qc = qp->head; qc; qc = qn)
    {
	qn = qc->next;
	free(qc);
    }
    free(qp);
}
