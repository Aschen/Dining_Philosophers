/*
** core.c for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Wed Mar 19 12:28:57 2014 brunne-r
** Last update Thu Mar 20 14:41:15 2014 brunne-r
*/

#include "philo.h"

int		philo_think(t_list *list, t_conf *c)
{
  int		r;

  printf("[%d] : Thinking...\n", list->id);
  list->state = THINK;
  if ((r = pthread_mutex_trylock(&(list->next->stick))) < 0)
    _error("philo_think() : trylock");
  usleep(c->thinktime);
  if (r != 0)
    if (pthread_mutex_trylock(&(list->next->stick)) < 0)
      _error("philo_think() : trylock");
  printf("[%d] : Prepare to eat\n", list->id);
  list->state = EAT;
  return 0;
}

int		philo_sleep(t_list *list, t_conf *c)
{
  int		loop;

  (void)c;
  loop = 1;
  list->state = SLEEP;
  printf("[%d] : Sleeping...\n", list->id);
  while (loop)
    {
      if (list->prev->state != THINK && list->next->state != THINK)
	{
	  if (pthread_mutex_lock(&(list->stick)) < 0)
	    _error("philo_sleep() : lock");
	  list->state = THINK;
	  printf("[%d] : Start thinking\n", list->id);
	  loop = 0;
	}
      else
	usleep(MUSL);
    }
  return 0;
}

int		philo_eat(t_list *list, t_conf *c)
{
  list->state = EAT;
  printf("[%d] : Eat like a pig !\n", list->id);
  usleep(c->eattime);
  if (pthread_mutex_unlock(&(list->stick)) < 0)
    _error("philo_sleep() : unlock");
  if (pthread_mutex_unlock(&(list->next->stick)) < 0)
    _error("philo_sleep() : unlock");
  list->state = SLEEP;
  printf("[%d] : Fall asleep...\n", list->id);
  return 1;
}

void		*philo_life(void *arg)
{
  t_param	*param;
  t_list	*me;
  int		food;
  int		(*actions[3])(t_list*, t_conf*);

  param = (t_param*)arg;
  me = param->list;
  food = param->conf->food;
  actions[SLEEP] = &philo_sleep;
  actions[EAT] = &philo_eat;
  actions[THINK] = &philo_think;
  while (food)
    {
      food -= (actions[(int)me->state](me, param->conf));
      usleep(MUSL);
    }
  pthread_exit(0);
  return NULL;
}

