/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:34 by vberdugo          #+#    #+#             */
/*   Updated: 2024/09/22 14:07:11 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# define LONG_MAX 2147483647L
# define LONG_MIN -2147483648L
# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define WIDTH 512
# define HEIGHT 512

typedef struct s_player
{
	mlx_image_t		*image_p;
	mlx_texture_t	*texture_p;
	float			scale;			
	int				x;
	int				y;
	bool			win;
}	t_player;

typedef struct s_map
{
	int				nbr;
	int				index;
	int				push_cost;
	bool			above_half;
	bool			cheapest;
	struct s_lst	*target_node;
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_map;

typedef struct s_gamedata
{
	mlx_t		*mlx;
	t_player	*player;
	t_map		*map;
	int32_t		window_width;
	int32_t		window_height;
}	t_gamedata;

#endif
