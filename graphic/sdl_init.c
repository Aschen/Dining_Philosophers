/*
** philo.h for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 16:18:46 2014 brunne-r
** Last update Fri Mar 21 15:22:23 2014 brunne-r
*/

#include "philo.h"

static void	load_images(t_sdl *game)
{
  if ((game->images[SLEEP] = IMG_Load("images/sleep.png")) == NULL)
    _error("load_images : IMGLoad");
  if ((game->images[THINK] = IMG_Load("images/think.png")) == NULL)
    _error("load_images : IMGLoad");
  if ((game->images[EAT] = IMG_Load("images/eat.png")) == NULL)
    _error("load_images : IMGLoad");
}

static void	load_background(t_sdl *game)
{
  SDL_Rect	p;

  p.x = 0;
  p.y = 0;
  if ((game->background = IMG_Load(game->file)) == NULL)
    _error("load_background : IMGLoad");
  if (SDL_BlitSurface(game->background, NULL, game->screen, &p) < 0)
    _error("load_background : BlitSurface");
  SDL_Flip(game->screen);
}

static void	init_game(t_sdl *game)
{
  int		i = 0;

  game->file = strdup("images/table7.png");
  game->size[X] = 600;
  game->size[Y] = 600;
  if ((game->pos = malloc(sizeof(int) * lenght(game->philos) * 2)) == NULL)
    _error("init_game() : Malloc");
  game->pos[i++] = 420;
  game->pos[i++] = 20;
  game->pos[i++] = 500;
  game->pos[i++] = 140;
  game->pos[i++] = 500;
  game->pos[i++] = 370;
  game->pos[i++] = 320;
  game->pos[i++] = 490;
  game->pos[i++] = 20;
  game->pos[i++] = 330;
  game->pos[i++] = 30;
  game->pos[i++] = 130;
  game->pos[i++] = 160;
  game->pos[i++] = 10;
}

void		init_sdl(t_sdl *game, t_list *philos, pthread_t *threads)
{
  game->threads = threads;
  game->philos = philos;
  init_game(game);
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
    _error("init_sdl : Init");
  if (!(game->screen = SDL_SetVideoMode(game->size[X], game->size[Y]
					, 32, SDL_HWSURFACE)))
    _error("init_sdl : SetVideoMode");
  SDL_WM_SetCaption("Philosophes", NULL);
  load_images(game);
  load_background(game);
  if (pthread_create(&threads[NPHIL], NULL, &sdl_loop, game) < 0)
    _error("main() : phtread_create");
}

