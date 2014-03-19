/*
** list.c for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 16:18:33 2014 brunne-r
** Last update Tue Mar 18 12:00:52 2014 brunne-r
*/

#include "philo.h"

void	_error(char *s)
{
  fprintf(stderr, "%s\n", s);
  exit(EXIT_FAILURE);
}

t_list	*last(t_list *list)
{
  if (list->next->id > list->id)
    return last(list->next);
  else
    return list;
}

void	plist(t_list *list)
{
  printf("Philo number %d\n", list->id);
  if (list->next->id > list->id)
    plist(list->next);
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
