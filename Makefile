# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nrenz <nrenz@student.42wolfsburg.de>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/31 11:26:42 by nrenz             #+#    #+#              #
#    Updated: 2022/11/04 15:58:23 by nrenz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	main.c \
		path_handling.c \
		files_init.c \
		error_handling.c \

OBJS = $(SRCS:.c=.o)

LIBFTDIR = ./libft/
LIBFT = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I libft

NAME = pipex

all: libft_make $(NAME)

libft_make: 
	@make -C $(LIBFTDIR) 	


$(NAME): $(OBJS) $(LIBFT)
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

re: fclean all

.PHONY: all clean fclean re