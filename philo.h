/*
** philo.h for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 16:18:46 2014 brunne-r
** Last update Mon Mar 17 16:41:17 2014 brunne-r
*/

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

typedef		struct s_list	t_list;

struct		s_list
{
  char		id;
  char		stick;
  t_list	*next;
};

void	plist(t_list *list);
void	push(t_list **list);
void	_error(char *s);

#endif /* !PHILO_H */
