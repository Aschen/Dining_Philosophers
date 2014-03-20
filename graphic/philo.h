/*
** philo.h for - in /home/brunne_r/Links/philosophes
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Mon Mar 17 16:18:46 2014 brunne-r
** Last update Wed Mar 19 11:35:12 2014 brunne-r
*/

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>

# define SLEEP		0
# define THINK		1
# define EAT		2

# define MUTH		200000
# define MUEAT		(MUTH / 2)
# define MUSL		1000

# define NPHIL		7
# define FOOD		5

# define QUIT		0
# define CONTINUE	1
# define X		0
# define Y		1

typedef struct s_list	t_list;
typedef struct s_sdl	t_sdl;

struct			s_list
{
  char			id;
  pthread_mutex_t	stick;
  char			state;
  t_list		*prev;
  t_list		*next;
};

struct			s_sdl
{
  SDL_Surface		*screen;
  SDL_Surface		*background;
  SDL_Surface		*images[3];
  char			*file;
  int			size[2];
  t_list		*philos;
  int			*pos;
};

void			init_sdl(t_sdl *game, t_list *philos);
void			*sdl_loop(void *game);
void			plist(t_list *list);
int			lenght(t_list *list);
void			push(t_list **list);
void			free_sdl(t_sdl *game);
void			_error(char *s);

#endif /* !PHILO_H */
