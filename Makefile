#*************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/14 16:20:05 by vberdugo          #+#    #+#              #
#    Updated: 2024/10/17 21:05:02 by victor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
NAME_BONUS = so_long_bonus

LIBFT = libft/libft.a
MINI = MLX42/build/libmlx42.a
MINI_BACKUP = $(MINI).backup

SRC = key_hook.c collect.c map_read.c player.c map_setup.c pixel_utils.c \
      map_tiles.c map_validate.c ft_render.c map_path.c ft_move.c\
      collect_utils.c resize_hook.c free.c so_long.c 

BONUS_SRC = bonus/so_long_bonus.c bonus/collect_bonus.c bonus/ft_render_bonus.c \
            bonus/map_path_bonus.c bonus/pixel_utils_bonus.c bonus/spike_bonus.c \
            bonus/collect_utils_bonus.c bonus/input_bonus.c bonus/map_read_bonus.c \
            bonus/player_bonus.c bonus/free2_bonus.c bonus/input_utils_bonus.c \
            bonus/map_utils_bonus.c bonus/free_bonus.c bonus/map_bonus.c \
            bonus/map_validate_bonus.c

OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:%.c=%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilibft -Iinc -g
LDFLAGS = $(LIBFT) $(MINI) -lglfw -lm

HBONUS = .bonus

all: libs mlx $(NAME)

libs:
	@make -C libft

mlx:
	@cmake MLX42 -B MLX42/build && make -C MLX42/build -j4

$(NAME): $(LIBFT) $(MINI) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(NAME_BONUS): $(LIBFT) $(MINI) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(NAME_BONUS) $(LDFLAGS)

$(LIBFT):
	@make -C libft

$(MINI):
	@cmake MLX42 -B MLX42/build && make -C MLX42/build -j4

%.o: %.c so_long.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

bonus/%.o: bonus/%.c bonus/so_long_bonus.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_BONUS)
	@if [ ! -f $(HBONUS) ] || \
		find $(BONUS_OBJ) -newer $(HBONUS) | grep -q .; then \
		$(MAKE) $(NAME_BONUS); \
		touch $(HBONUS); \
	else \
		echo "make bonus: Nothing to be done for 'bonus'."; \
	fi

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	@make -C libft clean
	@make -C MLX42/build clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) -C libft fclean
	rm -f $(MINI)

re: fclean all

.PHONY: all bonus clean fclean re
