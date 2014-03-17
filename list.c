/*
** list.c for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 16:18:33 2014 brunne-r
** Last update Mon Mar 17 16:59:21 2014 brunne-r
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
  printf("Philo number %d has %d sticks\n", list->id, list->stick);
  if (list->next->id > list->id)
    plist(list->next);
}

void	push(t_list **list)
{
  t_list	*elem;
  t_list	*before;

  if (!(elem = malloc(sizeof(t_list))))
      _error("not enough memory");
  elem->stick = 1;
  elem->state = SLEEP;
  if (*list)
    {
      before = last(*list);
      elem->next = before->next;
      elem->id = before->id + 1;
      before->next = elem;
    }
  else
    {
      *list = elem;
      elem->next = elem;
      elem->id = 0;
    }
}
