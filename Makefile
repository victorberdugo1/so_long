#*************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/14 16:20:05 by vberdugo          #+#    #+#              #
#    Updated: 2024/10/13 21:34:48 by victor           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
NAME_BONUS = so_long_bonus

LIBFT = libft/libft.a

HBONUS = .bonus

MINI = MLX42/build/libmlx42.a
MINI_BACKUP = $(MINI).backup

INCLUDE = libft/libft.h so_long.h

SRC = input.c collect.c map_read.c player.c map.c pixel_utils.c \
	  map_utils.c map_validate.c ft_render.c map_path.c \
	  collect_utils.c input_utils.c spike.c free.c free_2.c

BONUS_SRC = so_long_bonus.c #free_bonus.c #print_bonus.c

OBJ = $(SRC:.c=.o)

BONUS_OBJ = $(BONUS_SRC:%.c=%.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -Ilibft -Iinc #-fsanitize=address,undefined -g

LDFLAGS = $(LIBFT) $(MINI) -lglfw -lm

all: $(NAME)

HBONUS = .bonus

$(NAME): $(LIBFT) $(MINI) $(OBJ) so_long.o 
	$(CC) $(CFLAGS) $(OBJ) so_long.o -o $(NAME) $(LDFLAGS)

$(NAME_BONUS): $(LIBFT) $(MINI) $(OBJ) $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(BONUS_OBJ) -o $(NAME_BONUS) $(LDFLAGS)

$(LIBFT):
	@make -C libft

$(MINI):
	@cmake MLX42 -B MLX42/build && make -C MLX42/build -j4

%.o: %.c so_long.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ): $(BONUS_SRC) so_long.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

so_long.o: so_long.c so_long.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME_BONUS)
	@if [ ! -f $(HBONUS) ] || \
		find $(BONUS_OBJ) -newer $(HBONUS) | grep -q .; then \
		touch $(HBONUS); \
	else \
		echo "make bonus: Nothing to be done for 'bonus'."; \
	fi

clean:
	rm -f $(OBJ) $(BONUS_OBJ) so_long.o
	@cp $(MINI) $(MINI_BACKUP)
	@make -C libft clean
	@make -C MLX42/build clean
	@mv $(MINI_BACKUP) $(MINI)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) -C libft fclean
	rm -f $(MINI)

re: fclean all

.PHONY: all clean fclean re test
