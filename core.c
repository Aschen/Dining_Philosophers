/*
** core.c for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Wed Mar 19 12:28:57 2014 brunne-r
** Last update Wed Mar 19 17:49:58 2014 brunne-r
*/

#include "philo.h"

static struct timeval dep;

void		set_dep(void)
{
  gettimeofday(&dep, NULL);
}

int		philo_think(t_list *list, t_conf *c)
{
  int		r;

  printf("[%d] : Thinking...\n", list->id);
  list->state = THINK;
  r = pthread_mutex_trylock(&(list->next->stick));
  usleep(c->thinktime);
  if (r != 0)
    pthread_mutex_trylock(&(list->next->stick));
  list->state = EAT;
  return 0;
}

int		philo_sleep(t_list *list, t_conf *c)
{
  int		loop;

  (void)c;
  loop = 1;
  printf("[%d] : Sleeping...\n", list->id);
  list->state = SLEEP;
  while (loop)
    {
      if (list->prev->state != THINK && list->next->state != THINK)
	{
	  pthread_mutex_lock(&(list->stick));
	  loop = 0;
	  list->state = THINK;
	}
      else
	usleep(MUSL);
    }
  return 0;
}

int		philo_eat(t_list *list, t_conf *c)
{
  printf("[%d] : Eat like a pig !\n", list->id);
  list->state = EAT;
  usleep(c->eattime);
  pthread_mutex_unlock(&(list->stick));
  pthread_mutex_unlock(&(list->next->stick));
  list->state = SLEEP;
  return 1;
}

void		*philo_life(void *arg)
{
  t_param	*param;
  t_list	*me;
  int		food;
  int		(*actions[3])(t_list*, t_conf*);

  actions[SLEEP] = &philo_sleep;
  actions[EAT] = &philo_eat;
  actions[THINK] = &philo_think;
  param = (t_param*)arg;
  me = param->list;
  food = param->conf->food;
  while (food)
    {
      food -= (actions[(int)me->state](me, param->conf));
      usleep(MUSL);
    }
    pthread_exit(0);
  return NULL;
}

