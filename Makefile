# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 11:26:42 by nrenz             #+#    #+#              #
#    Updated: 2022/11/02 14:37:48 by nrenz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	path_handling.c \
		pipex_main.c \
		error_handling.c \

OBJS = $(SRCS:.c=.o)

LIBFTDIR = ./libft/
LIBFT = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I libft

NAME = pipex

libft_make: 
	@make -C $(LIBFTDIR) 	

all: libft_make $(NAME)

$(NAME): $(OBJS)
	@cp $(LIBFTDIR)$(LIBFT) $(LIBFT)
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) -o $(NAME)

$(LIBFT):
	make all -C $(LIBFTDIR)

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re