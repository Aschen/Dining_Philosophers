/*
** list.c for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 16:18:33 2014 brunne-r
** Last update Fri Mar 21 15:21:01 2014 brunne-r
*/

#include "philo.h"

void		_error(char *s)
{
  if (s)
    fprintf(stderr, "%s\n", s);
  else
    fprintf(stderr, "An error has occured\n");
  exit(EXIT_FAILURE);
}

static void	free_list(t_list *list)
{
  if (list->next->id > list->id)
    free_list(list->next);
  free(list);
}

void		free_sdl(t_sdl *game)
{
  int		i;

  i = -1;
  if (game->background)
    SDL_FreeSurface(game->background);
  while (++i < 3)
    if (game->images[i])
      SDL_FreeSurface(game->images[i]);
  if (game->file)
    free(game->file);
  if (game->pos)
    free(game->pos);
  if (game->philos)
    free_list(game->philos);
}
