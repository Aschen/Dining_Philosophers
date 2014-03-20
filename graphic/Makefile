##
## Makefile for  in /home/brunne_r/Public/PSU_2013_philo
##
## Made by Romain Brunner
## Login   <brunne_r@epitech.net>
##
## Started on  Mon 17/03/2014 00:00
##

CC	=	clang

SRCS	=	main.c \
		list.c \
		sdl_init.c \
		sdl_event.c \
		misc.c \

CFLAGS	=	-W -Wall -Wextra

CFLAGS +=	`sdl-config --cflags`

OBJS	=	$(SRCS:.c=.o)

NAME	=	test

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) `sdl-config --libs` -o $(NAME) $(OBJS) -lpthread -lSDL_gfx -lSDL_image

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all
