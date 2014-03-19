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
		pars.c \
		core.c \

CFLAGS	=	-W -Wall -Wextra

OBJS	=	$(SRCS:.c=.o)

NAME	=	philo

all:	$(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS) -lpthread

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re: fclean all
