/*
** main.c for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 15:42:01 2014 brunne-r
** Last update Mon Mar 17 16:54:47 2014 brunne-r
*/

#include "philo.h"

static pthread_mutex_t  lock = PTHREAD_MUTEX_INITIALIZER;

void		*fct(void *arg)
{
  t_list	*me;
  int		food;
  char		last_state;

  me = (t_list*)arg;
  food = 1;
  last_state = 0;
  while (food)
    {
      if (me->stick == 1 && me->next->stick == 1)
	{
	  printf("Philo %d: I'm eating\n", me->id);
	  last_state = 2;
	}
      else if (me->stick == 0)
	{
	  printf("Philo %d: Time to sleep\n", me->id);
	  last_state = 0;
	}
      else if (me->stick == 2
    }
  pthread_mutex_lock(&lock);
  pthread_mutex_unlock(&lock);
  pthread_exit(0);
  return NULL;
}

int		main(void)
{
  t_list	*philo;
  t_list	*send;
  pthread_t	philos[7];
  int		i;

  i = -1;
  philo = NULL;
  while (++i < 7)
    push(&philo);
  i = -1;
  send = philo;
  while (++i < 7)
    {
      if (pthread_create(&philos[i], NULL, &fct, send) < 0)
	_error("pthread fail");
      send = send->next;
    }
  i = -1;
  while (++i < 7)
    pthread_join(philos[i], NULL);
  plist(philo);
  return 0;
}
