/*
** main.c for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 15:42:01 2014 brunne-r
** Last update Fri Mar 21 15:36:30 2014 brunne-r
*/

#include "philo.h"

int		philo_think(t_list *list)
{
  int		r;

  list->state = THINK;
  if ((r = pthread_mutex_trylock(&(list->next->stick))) < 0)
    _error("philo_think() : trylock");
  usleep(MUTH);
  if (r != 0)
    if (pthread_mutex_trylock(&(list->next->stick)) < 0)
      _error("philo_think() : trylock");
  list->state = EAT;
  return (0);
}

int		philo_sleep(t_list *list)
{
  int		loop;

  loop = 1;
  list->state = SLEEP;
  while (loop)
    {
      if (list->prev->state != THINK && list->next->state != THINK)
	{
	  if (pthread_mutex_lock(&(list->stick)) < 0)
	    _error("philo_sleep() : lock");
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
  list->state = EAT;
  usleep(MUEAT);
  if (pthread_mutex_unlock(&(list->stick)) < 0)
    _error("philo_eat() : unlock");
  if (pthread_mutex_unlock(&(list->next->stick)) < 0)
    _error("philo_eat() : unlock");
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
      sleep(1);
    }
  pthread_exit(0);
  return (NULL);
}

int		main(void)
{
  t_list	*philos;
  t_list	*send;
  t_sdl		game;
  pthread_t	threads[NPHIL + 1];
  int		i;

  i = -1;
  philos = NULL;
  while (++i < NPHIL)
    push(&philos);
  init_sdl(&game, philos, threads);
  i = -1;
  send = philos;
  while (++i < NPHIL)
    {
      if (pthread_create(&threads[i], NULL, &fct, send) < 0)
  	_error("pthread fail");
      usleep(MUSL);
      send = send->next;
    }
  i = -1;
  while (++i < NPHIL + 1)
    if (pthread_join(threads[i], NULL) < 0)
      _error("main() : join fail");
  free_sdl(&game);
  return (0);
}
