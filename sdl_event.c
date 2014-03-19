/*
** philo.h for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 16:18:46 2014 brunne-r
** Last update Wed Mar 19 11:35:12 2014 brunne-r
*/

#include "philo.h"

static int	hook_event(SDL_Event *event, t_sdl *game)
{
  (void)game;
  if (event->type == SDL_QUIT || event->type == SDL_KEYDOWN)
    return (QUIT);
  return (CONTINUE);
}

static void	update_state(t_sdl *game, t_list *philos)
{
  SDL_Rect	p;

  p.x = game->pos[philos->id * 2];
  p.y = game->pos[philos->id * 2 + 1];
  if (SDL_BlitSurface(game->images[(int)philos->state], NULL, game->screen, &p) < 0)
    _error(strdup("update_state() : BlitSurface"));
  if (philos->next->id > philos->id)
    update_state(game, philos->next);
}

void		*sdl_loop(void *arg)
{
  SDL_Rect	p;
  t_sdl		*game;
  SDL_Event	event;
  int		flag;

  flag = 1;
  p.x = 0;
  p.y = 0;
  game = (t_sdl*)arg;
  while (flag)
    {
      if (SDL_PollEvent(&event))
	flag = hook_event(&event, game);
      if (SDL_BlitSurface(game->background, NULL, game->screen, &p) < 0)
	_error(strdup("sld_loop() : BlitSurface"));
      update_state(game, game->philos);
      SDL_Flip(game->screen);
      usleep(1000);
    }
  return (0);
}
