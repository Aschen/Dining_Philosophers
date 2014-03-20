/*
** main.c for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 15:42:01 2014 brunne-r
** Last update Thu Mar 20 14:50:56 2014 brunne-r
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
  _error("A thread is unreachable");
}

void		*xmalloc(size_t size)
{
  void		*buf;

  buf =	malloc(size);
  if (!buf)
    _error("Not enough memory");
  return buf;
}

t_list		*create_list(int number)
{
  int		i;
  t_list	*philo;

  i = -1;
  philo = NULL;
  while (++i < number)
    push(&philo);
  return philo;
}

void		launch(t_conf *c)
{
  t_list	*philos;
  t_param	param;
  pthread_t	*ths;
  int		i;

  i = -1;
  philos = create_list(c->number);
  ths = xmalloc(sizeof(pthread_t) * c->number);
  param.list = philos;
  param.conf = c;
  while (++i < c->number)
    {
      if (pthread_create(&ths[i], NULL, &philo_life, &param) < 0)
	_error("Can't create more threads");
      usleep(MUSL);
      param.list = param.list->next;
      philos = param.list;
    }
  i = -1;
  while (++i < c->number)
    {
      if (pthread_join(ths[i], NULL) != 0)
	kill_threads(ths, c->number);
    }
  free(ths);
}

int		main(int ac, char **av)
{
  t_conf	conf;

  init(&conf);
  if (ac == 2)
    fill_conf(&conf, av[1]);
  printf("###########################\n");
  printf("## CONF     : %10s ##\n", (ac == 2) ? (av[1]) : ("(empty)"));
  printf("## philos   : %10d ##\n", conf.number);
  printf("## food     : %10d ##\n", conf.food);
  printf("## eat(us)  : %10d ##\n", conf.eattime);
  printf("## think(us): %10d ##\n", conf.thinktime);
  printf("###########################\n");
  launch(&conf);
  return (EXIT_SUCCESS);
}
