/*
 * CS170: Operating Systems
 * 	adapted from CS460: Operating Systems
 * 	Jim Plank
 * dphil_5.c -- Dining philosophers solution
 * the book's solution
 */


#include <stdio.h>
#include <pthread.h>
#include "dphil.h"


#define THINKING 0
#define HUNGRY 1
#define EATING 2

typedef struct {
  pthread_mutex_t *mon;
  pthread_cond_t *cv[MAXTHREADS];
  int state[MAXTHREADS];
  int phil_count;
} Phil;


void pickup(Phil_struct *ps)
{
  Phil *pp;
  int phil_count;

  pp = (Phil *) ps->v;
  phil_count = pp->phil_count;
  
  pthread_mutex_lock(pp->mon); //WHAT IS MON AND WHY MUST IT BE ON CS????
  pp->state[ps->id] = HUNGRY;
  while (pp->state[(ps->id + (phil_count-1))%phil_count] == EATING || //WAITS WHILE LEFT AND RIGHT ARE EATONG?
         pp->state[(ps->id + 1)% phil_count] == EATING) {
    pthread_cond_wait(pp->cv[ps->id], pp->mon);
  }
  pp->state[ps->id] = EATING; //WHERES THE SIGNAL
  pthread_mutex_unlock(pp->mon);
}

void putdown(Phil_struct *ps)
{
  Phil *pp;
  int phil_count;

  pp = (Phil *) ps->v;
  phil_count = pp->phil_count;

  pthread_mutex_lock(pp->mon);
  pp->state[ps->id] = THINKING;
  if (pp->state[(ps->id+(phil_count-1))%phil_count] == HUNGRY) {      ///IF LEFT HUNGRY SIGNAL
    pthread_cond_signal(pp->cv[(ps->id+(phil_count-1))%phil_count]);
  }
  if (pp->state[(ps->id+1)%phil_count] == HUNGRY) { 				///IF RIGHT HUNGRY SIGNAL
    pthread_cond_signal(pp->cv[(ps->id+1)%phil_count]);
  }													//IS THIS LACK OF PREFERENCE OF WHO GETS SIGNALED FIRST WHAT CAUSES STARVATION????????
  pthread_mutex_unlock(pp->mon);					//WOULD CHOOSING RIGHT IF TO GO FIRST CHANGE ANYTHING????????
}

void *initialize_state(int phil_count)
{
  Phil *pp;
  int i;

  pp = (Phil *) malloc(sizeof(Phil)*phil_count);
  pp->phil_count = phil_count;
  pp->mon = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t)); ///???????
  pthread_mutex_init(pp->mon, NULL);
  for (i = 0; i < phil_count; i++) {
    pp->cv[i] = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
    pthread_cond_init(pp->cv[i], NULL);
    pp->state[i] = THINKING; //WHY MUST INITIALIZE STATE TO THINKING WHERE OTHER SOLS DONT?
  }

  return (void *) pp;
}