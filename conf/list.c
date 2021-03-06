/*
** list.c for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 16:18:33 2014 brunne-r
** Last update Wed Mar 19 17:58:29 2014 brunne-r
*/

#include "philo.h"

void		_error(char *s)
{
  fprintf(stderr, "%s\n", s);
  exit(EXIT_FAILURE);
}

t_list	*last(t_list *list)
{
  return (list->next->id > list->id) ? last(list->next) : list;
}

void	push(t_list **list)
{
  t_list	*elem;
  t_list	*before;

  if (!(elem = malloc(sizeof(t_list))))
      _error("not enough memory");
  elem->state = SLEEP;
  pthread_mutex_init(&(elem->stick), NULL);
  if (*list)
    {
      before = last(*list);
      elem->next = before->next;
      elem->prev = before;
      elem->next->prev = elem;
      elem->id = before->id + 1;
      before->next = elem;
    }
  else
    {
      *list = elem;
      elem->next = elem;
      elem->prev = elem;
      elem->id = 0;
    }
}
