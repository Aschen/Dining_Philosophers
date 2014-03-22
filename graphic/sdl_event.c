/*
** philo.h for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 16:18:46 2014 brunne-r
** Last update Fri Mar 21 15:43:57 2014 brunne-r
*/

#include "philo.h"

static int	hook_event(SDL_Event *event)
{
  if (event->type == SDL_QUIT || event->type == SDL_KEYDOWN)
    return (QUIT);
  return (CONTINUE);
}

static int	update_state(t_sdl *game, t_list *philos)
{
  SDL_Rect	p;
  int		end;

  end = (philos->state == SLEEP) ? 0 : 1;
  p.x = game->pos[philos->id * 2];
  p.y = game->pos[philos->id * 2 + 1];
  if (SDL_BlitSurface(game->images[(int)philos->state]
		      , NULL, game->screen, &p) < 0)
    _error("update_state() : BlitSurface");
  if (philos->next->id > philos->id)
    return (end + update_state(game, philos->next));
  return (end);
}

void		*sdl_loop(void *arg)
{
  SDL_Rect	p;
  t_sdl		*game;
  SDL_Event	event;
  int		flag;
  int		i;

  i = -1;
  flag = 1;
  p.x = 0;
  p.y = 0;
  game = (t_sdl*)arg;
  while (flag)
    {
      if (SDL_BlitSurface(game->background, NULL, game->screen, &p) < 0)
	_error("sld_loop() : BlitSurface");
      flag = update_state(game, game->philos);
      if (SDL_PollEvent(&event) && flag)
	flag = hook_event(&event);
      SDL_Flip(game->screen);
      usleep(1000);
    }
  while (++i < NPHIL)
    if (pthread_kill(game->threads[i], SIGUSR1) < 0)
      _error("sld_loop() : kill");
  pthread_exit(0);
  return (NULL);
}
