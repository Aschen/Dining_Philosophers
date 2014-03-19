/*
** pars.c for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Wed Mar 19 11:48:14 2014 brunne-r
** Last update Wed Mar 19 12:28:10 2014 brunne-r
*/

#include "philo.h"

FILE	*open_file(char *file)
{
  FILE	*f;

  f = fopen(file, "r");
  if (!f)
    _error("Cannot open configuration file.\n");
  return f;
}

void		fill_token(char *s, t_conf *conf)
{
  char		*tab[5];
  int		*itab[4];
  int		i;

  tab[4] = 0;
  tab[0] = "number:";
  tab[1] = "food:";
  tab[2] = "eattime:";
  tab[3] = "thinktime:";
  itab[0] = &(conf->number);
  itab[1] = &(conf->food);
  itab[2] = &(conf->eattime);
  itab[3] = &(conf->thinktime);
  i = -1;
  while (tab[++i])
    {
      if (strncmp(tab[i], s, strlen(tab[i])) == 0)
	*(itab[i]) = atoi(&s[strlen(tab[i])]);
    }
}

void		check(t_conf *c)
{
  if (c->number <= 1)
    _error("Philosophes need to be at least 2");
  if (c->food <= 0)
    _error("An empty plate is not very nutritive");
  if (c->eattime < 500 || c->thinktime < 500)
    _error("Time for actions must be superior or equal than 500");
}

void		init(t_conf *c)
{
  c->number = NPHIL;
  c->food = 1;
  c->eattime = MUEAT;
  c->thinktime = MUTH;
}

void		fill_conf(t_conf *conf, char *file)
{
  char		*line;
  size_t	n;
  FILE		*f;

  f = open_file(file);
  while (getline(&line, &n, f) > 0)
    {
      fill_token(line, conf);
    }
  check(conf);
  printf("Conf for %s:\n", file);
  printf("Philosophes: %d\n", conf->number);
  printf("Food: %d\n", conf->food);
  printf("Time to eat: %d\n", conf->eattime);
  printf("Time to think: %d\n", conf->thinktime);
}
