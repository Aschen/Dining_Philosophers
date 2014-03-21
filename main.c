/*
** main.c for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 15:42:01 2014 brunne-r
** Last update Fri Mar 21 15:42:30 2014 brunne-r
*/

#include "philo.h"

int		philo_think(t_list *list)
{
  int		r;

  printf("[%d] : Thinking...\n", list->id);
  list->state = THINK;
  r = pthread_mutex_trylock(&(list->next->stick));
  usleep(MUTH);
  if (r != 0)
    pthread_mutex_trylock(&(list->next->stick));
  list->state = EAT;
  return (0);
}

int		philo_sleep(t_list *list)
{
  int		loop;

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
  return (0);
}

int		philo_eat(t_list *list)
{
  printf("[%d] : Eat like a pig !\n", list->id);
  list->state = EAT;
  usleep(MUEAT);
  pthread_mutex_unlock(&(list->stick));
  pthread_mutex_unlock(&(list->next->stick));
  list->state = SLEEP;
  return (1);
}

void		*fct(void *arg)
{
  t_list	*me;
  int		food;
  int		(*actions[3])(t_list*);

  me = (t_list*)arg;
  actions[SLEEP] = &philo_sleep;
  actions[EAT] = &philo_eat;
  actions[THINK] = &philo_think;
  food = 1;
  while (food)
    {
      food -= (actions[(int)me->state](me));
      usleep(MUSL);
    }
  pthread_exit(0);
  return (NULL);
}

int		main(void)
{
  t_list	*philo;
  t_list	*send;
  pthread_t	philos[NPHIL];
  int		i;

  i = -1;
  philo = NULL;
  while (++i < NPHIL)
    push(&philo);
  i = -1;
  send = philo;
  while (++i < NPHIL)
    {
      if (pthread_create(&philos[i], NULL, &fct, send) < 0)
	_error("pthread fail");
      send = send->next;
      usleep(MUSL);
    }
  i = -1;
  while (++i < NPHIL)
    pthread_join(philos[i], NULL);
  return (0);
}
