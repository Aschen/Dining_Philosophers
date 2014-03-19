/*
** main.c for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 15:42:01 2014 brunne-r
** Last update Wed Mar 19 14:02:04 2014 brunne-r
*/

#include "philo.h"

void		kill_threads(pthread_t *th, int size)
{
  int		i;

  i = 0;
  while (i < size)
    {
      pthread_kill(th[i], SIGKILL);
      ++i;
    }
  _error("Few threads are unreachable");
}

int		launch(t_conf *c)
{
  t_list	*philo;
  t_list	*send;
  pthread_t	philos[7];
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
	_error("Can't create more threads");
      send = send->next;
    }
  i = -1;
  while (++i < NPHIL)
    {
      if (pthread_join(philos[i], NULL) != 0)
	kill_threads();
    }
  return 0;
}


int		main(int ac, char **av)
{
  t_conf	conf;

  init(&conf);
  if (ac == 2)
    fill_conf(&conf, av[1]);
  launch(&conf);
}
