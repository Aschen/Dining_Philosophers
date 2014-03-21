/*
** quit.c for - in /home/brunne_r/Links/philosophes/graphic
**
** Made by brunne-r
** Login   <brunne-r@epitech.net>
**
** Started on  Fri Mar 21 15:32:03 2014 brunne-r
** Last update Fri Mar 21 15:37:05 2014 brunne-r
*/

#include "philo.h"

void	quitth(int sig)
{
  if (sig == SIGUSR1)
    {
      pthread_exit(0);
    }
}
