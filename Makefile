# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/14 16:20:05 by vberdugo          #+#    #+#              #
#    Updated: 2024/09/19 12:27:57 by vberdugo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

LIBFT = libft/libft.a

MINI = MLX42/build/libmlx42.a

INCLUDE = libft/libft.h lib/so_long.h

SRC = so_long.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -Ilibft -Iinc

LDFLAGS = $(LIBFT) $(MINI) -lglfw

all: $(NAME)

$(NAME): $(LIBFT) $(MINI) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	@make -C libft

$(MINI):
	@make -C MLX42/build 

%.o: %.c inc/so_long.h 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ)
	$(MAKE) -C libft clean
	$(MAKE) -C MLX42/build clean

fclean: clean
	rm -f $(NAME) 
	$(MAKE) -C libft fclean
	rm -f $(MINI_LIB)

re: fclean all

.PHONY: all clean fclean re test
