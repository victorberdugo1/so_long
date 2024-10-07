#*************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/14 16:20:05 by vberdugo          #+#    #+#              #
#    Updated: 2024/10/07 17:28:13 by vberdugo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

LIBFT = libft/libft.a

MINI = MLX42/build/libmlx42.a
MINI_BACKUP = $(MINI).backup

INCLUDE = libft/libft.h lib/so_long.h

SRC = so_long.c input.c collect.c map_read.c player.c map.c pixel_utils.c \
	  map_utils.c free.c

OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Ilibft -Iinc -g #-fsanitize=address,undefined -g

LDFLAGS = $(LIBFT) $(MINI) -lglfw -lm

all: $(NAME)

$(NAME): $(LIBFT) $(MINI) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(LIBFT):
	@make -C libft

$(MINI):
	@cmake MLX42 -B MLX42/build && make -C MLX42/build -j4

%.o: %.c so_long.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TEST_OBJ)
	@cp $(MINI) $(MINI_BACKUP)
	@make -C libft clean
	@make -C MLX42/build clean
	@mv $(MINI_BACKUP) $(MINI)

fclean: clean
	rm -f $(NAME) 
	$(MAKE) -C libft fclean
	rm -f $(MINI)

re: fclean all

.PHONY: all clean fclean re test
