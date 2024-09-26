/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:34 by vberdugo          #+#    #+#             */
/*   Updated: 2024/09/26 16:21:14 by vberdugo         ###   ########.fr       */
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

typedef struct s_enemy
{
	mlx_image_t		*image_e;
	mlx_texture_t	*texture_e;
	float			scale;
	int				x;
	int				y;
	int				health;
}	t_enemy;

typedef struct s_collect
{
	mlx_image_t		*image_c;
	mlx_texture_t	*texture_c;
	float			scale;
	int				x;
	int				y;
	bool			pick;
}	t_collect;

typedef struct s_map
{
	mlx_image_t		*image_m;
	mlx_texture_t	*texture_m;
	char			**grid;
	float			scale;		
	int				width;
	int				height;
	int				exit_count;
	int				player_count;
	t_collect		*collects;
	bool			valid;
	bool			closed;
}	t_map;

typedef struct s_gamedata
{
	mlx_t		*mlx;
	t_player	*player;
	t_enemy		*enemy;
	int			coins;
	t_map		*map;
	int32_t		window_width;
	int32_t		window_height;
}	t_gamedata;

void		player_init(t_player *player, mlx_t *mlx);
void		ft_hook(void *param);
void		free_resources(t_gamedata *gamedata);
void		resize_hook(int32_t width, int32_t height, void *param);
void		ft_prt(mlx_texture_t *tex, mlx_image_t **im, float scl, mlx_t *mlx);
uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
t_map		*init_map(int width, int height);
t_map		*read_map(const char *filename);
int			map_size(const char *filename, int *width, int *height);
t_map		*fill_map(const char *filename, int width, t_map *map);
void		collect_init(t_collect *coll, int x, int y, mlx_t *mlx);
void		ft_randomize(void *param);
void		draw_map(t_map *map, int x, int y, mlx_t *mlx);

#endif 
