/*
** philo.h for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 16:18:46 2014 brunne-r
** Last update Wed Mar 19 12:30:16 2014 brunne-r
*/

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>

# define SLEEP		0
# define THINK		1
# define EAT		2

# define MUTH		200000
# define MUEAT		(MUTH / 2)
# define MUSL		1000

# define NPHIL		5

typedef			struct s_list	t_list;

struct			s_list
{
  char			id;
  pthread_mutex_t	stick;
  char			state;
  t_list		*prev;
  t_list		*next;
};

typedef struct		s_conf
{
  int			number;
  int			food;
  int			eattime;
  int			thinktime;
}			t_conf;

void			fill_conf(t_conf *conf, char *file);
void			plist(t_list *list);
void			push(t_list **list);
void			_error(char *s);
int			launch(t_conf *c);
#endif /* !PHILO_H */
