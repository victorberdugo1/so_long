#*************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/14 16:20:05 by vberdugo          #+#    #+#              #
#    Updated: 2024/10/23 17:31:03 by vberdugo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
NAME_BONUS = so_long_bonus

LIBFT = libft/libft.a
MINI = MLX42/build/libmlx42.a
MINI_BACKUP = $(MINI).backup

OBJ_DIR = ./obj
OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

SRC = key_hook.c collect.c map_read.c player.c map_setup.c pixel_utils.c \
      map_tiles.c map_validate.c ft_render.c map_path.c ft_move.c\
      collect_utils.c resize_hook.c free.c so_long.c 

BONUS_SRC = bonus/so_long_bonus.c bonus/collect_bonus.c bonus/ft_render_bonus.c \
            bonus/map_path_bonus.c bonus/pixel_utils_bonus.c bonus/spike_bonus.c \
            bonus/collect_utils_bonus.c bonus/input_bonus.c bonus/map_read_bonus.c \
            bonus/player_bonus.c bonus/free2_bonus.c bonus/input_utils_bonus.c \
            bonus/map_utils_bonus.c bonus/free_bonus.c bonus/map_bonus.c \
            bonus/map_validate_bonus.c

BONUS_OBJ = $(BONUS_SRC:%.c=%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -Ilibft -Iinc  #-g -fsanitize=address

LDFLAGS = $(LIBFT) $(MINI) -lglfw -lm

HBONUS = .bonus

all: libs mlx $(NAME)

xGREEN_DARK = \033[0;32m	# Verde oscuro
WHITE = \033[0m				# Blanco
RED = \033[0;91m			# Rojo
RESET = \033[0m				# Reiniciar color

libs:
	@make -C libft

mlx:
	@cmake MLX42 -B MLX42/build && make -C MLX42/build -j4

$(NAME): $(LIBFT) $(MINI) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN_DARK)Executable $(NAME) created successfully!$(RESET)"

$(NAME_BONUS): $(LIBFT) $(MINI) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(NAME_BONUS) $(LDFLAGS)

$(LIBFT):
	@make -C libft

$(MINI):
	@cmake MLX42 -B MLX42/build && make -C MLX42/build -j4

$(OBJ_DIR)/%.o: %.c so_long.h Makefile
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN_DARK)Compiled: $<$(RESET)"


bonus/%.o: bonus/%.c bonus/so_long_bonus.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

bonus: libs mlx $(NAME_BONUS)
	@if [ ! -f $(HBONUS) ] || \
		find $(BONUS_OBJ) -newer $(HBONUS) | grep -q .; then \
		$(MAKE) $(NAME_BONUS); \
		touch $(HBONUS); \
	else \
		echo "make bonus: Nothing to be done for 'bonus'."; \
	fi

clean:
	@make -C libft clean
	@make -C MLX42/build clean
	rm -rf $(OBJ_DIR) $(BONUS_OBJ)
	@echo "$(RED)Cleaned up object files.$(RESET)"


fclean: clean
	@make -C libft fclean
	rm -f $(MINI)
	rm -f $(NAME) $(NAME_BONUS)
	@echo "$(RED)Executable $(NAME) removed.$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
