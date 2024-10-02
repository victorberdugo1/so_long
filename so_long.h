/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:34 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/02 23:02:41 by victor           ###   ########.fr       */
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
# define TILE_SIZE 64

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_player
{
	mlx_image_t		**image_p;
	mlx_image_t		*resize_p;
	mlx_texture_t	*texture_p;
	float			scale;
	t_coord			xy_p;
	bool			win;
	int				current_frame;
	int				total_frames;
	float			animation_speed;
	float			frame_timer;
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
	mlx_image_t		**image_c;
	mlx_image_t		*resize_c;
	mlx_texture_t	*texture_c;
	float			scale_c;
	int				x;
	int				y;
	bool			pick;
	int				current_frame;   // Frame actual
	int				total_frames;    // Total de frames de animación
	float			animation_speed; // Velocidad de animación
	float			frame_timer;
}	t_collect;

typedef struct s_map
{
	mlx_image_t		*full_m;
	mlx_image_t		*resize_m;
	mlx_image_t		**tiles;
	mlx_texture_t	*texture_m;
	char			**grid;
	float			scale;
	int				wdt;
	int				hgt;
	int				orient;
	t_coord			xy_m;
	int				exit_count;
	int				player_count;
	t_collect		*collects;
	t_coord        player_pos;         // Posición del jugador
	t_coord        *collectible_pos;
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
void		ft_hook(mlx_key_data_t keydata, void *param);
void		free_resources(t_gamedata *gamedata);
void		resize_hook(int32_t width, int32_t height, void *param);
uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
t_map		*init_map(int width, int height);
t_map		*read_map(const char *filename);
int			map_size(const char *filename, int *width, int *height);
t_map		*fill_map(const char *filename, int width, t_map *map);
void		collect_init(t_collect *coll, int x, int y, mlx_t *mlx);
void		ft_randomize(void *param);
void		draw_map(t_map *map, mlx_t *mlx);
int			all_collected(t_map *map);
uint32_t	get_pixel(uint8_t *pixels, int32_t src_x, int32_t src_y, int width);
t_coord		get_border_sprite(t_map *map, int coord_y, int coord_x);
uint32_t	convert_pixel(uint32_t px);
void		pxls_subim(mlx_image_t *sbim, mlx_texture_t *txt, int spx, int spy);
t_coord		get_inner_sprite(t_map *mp, int y, int x);
void		process_tile(t_map *map, mlx_t *mlx, int i, int j);
uint32_t	pixel_texture(mlx_texture_t *texture, uint32_t x, uint32_t y);
void		ft_draw(void *param);
void		ft_draw_coll(void *param);

#endif 
