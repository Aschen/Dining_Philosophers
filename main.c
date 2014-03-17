/*
** main.c for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 15:42:01 2014 brunne-r
** Last update Mon Mar 17 16:46:41 2014 brunne-r
*/

#include "philo.h"

static pthread_mutex_t  lock = PTHREAD_MUTEX_INITIALIZER;

void		*fct(void *arg)
{
  t_list	*me;

  me = (t_list*)arg;
  pthread_mutex_lock(&lock);
  printf("I'm philo %d with %d sticks\n", me->id, me->stick);
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
