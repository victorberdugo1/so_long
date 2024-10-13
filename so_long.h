/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:34 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/13 21:32:25 by victor           ###   ########.fr       */
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

typedef struct s_dim
{
	uint32_t	width;
	uint32_t	height;
}	t_dim;

typedef struct s_player
{
	mlx_image_t		**image_p;
	mlx_image_t		*resize_p;
	mlx_texture_t	*texture_p;
	float			scale;
	t_coord			xy_p;
	t_coord			dest_p;
	bool			win;
	int				current_frame;
	int				total_frames;
	int				move_count;
	float			animation_speed;
	float			frame_timer;
	bool			moving;
	float			speed;
}	t_player;

typedef struct s_collect
{
	mlx_image_t		*image_c;
	mlx_image_t		*resize_c;
	mlx_texture_t	*txt_c;
	float			scale_c;
	t_coord			xy_c;
	bool			pick;
}	t_collect;

typedef struct s_spike
{
	mlx_image_t		*image_s;
	mlx_image_t		*resize_s;
	float			scale_s;
	t_coord			xy_s;
}	t_spike;

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
	t_coord			xy_m;
	int				exit;
	int				player;
	t_collect		*collects;
	t_coord			player_pos;
	t_coord			*collectible_pos;
	bool			collect_flag;
	t_spike			*spikes;
	bool			valid;
	bool			closed;
}	t_map;

typedef struct s_gamedata
{
	mlx_t			*mlx;
	t_player		*player;
	int				coins;
	int				num_spikes;
	t_map			*map;
	int32_t			window_width;
	int32_t			window_height;
	mlx_image_t		*bg_image;
	mlx_image_t		*cover;
	mlx_texture_t	*txt_cover;
	mlx_image_t		*nbr;
	mlx_image_t		*msg;
	bool			is_msg;
	mlx_texture_t	*txt_s;
}	t_gdata;

void		player_init(t_player *player, mlx_t *mlx);
void		ft_hook(mlx_key_data_t keydata, void *param);
void		free_resources(t_gdata *gamedata);
void		free_2(t_gdata *gamedata);
void		resize_hook(int32_t width, int32_t height, void *param);
uint32_t	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
t_map		*init_map(int width, int height);
t_map		*read_map(const char *filename);
int			map_size(const char *filename, int *width, int *height);
t_map		*fill_map(const char *filename, int width, t_map *map);
void		collect_init(t_collect *coll, int x, int y, mlx_t *mlx);
void		map_start(t_map *map, mlx_t *mlx);
void		sclmap(mlx_image_t **im, mlx_image_t **siz, float scl, t_gdata *gd);
void		bgclean(t_gdata *gd, int32_t width, int32_t height);
int			all_collected(t_map *map);
uint32_t	get_pixel(uint8_t *pixels, int32_t src_x, int32_t src_y, int width);
t_coord		get_border_sprite(t_map *map, int coord_y, int coord_x);
uint32_t	convert_pixel(uint32_t px);
void		pxls_subim(mlx_image_t *sbim, mlx_texture_t *txt, int spx, int spy);
t_coord		get_inner_sprite(t_map *mp, int y, int x);
void		process_tile(t_map *map, mlx_t *mlx, int i, int j);
void		ft_draw(void *param);
void		ft_draw_coll(void *param);
void		ft_draw_map(void *param);
void		ft_render(void *param);
void		combine_tiles(t_map *map);
int			count_collectables(t_map *map);
void		process_door_tile(t_map *map, mlx_t *mlx, int i, int j);
void		free_collects(t_collect *collects, int coin_count, t_gdata *gd);
int			init_collectables_from_map(t_gdata *gamedata);
bool		validate_map(t_map *map);
void		ft_move(t_player *player, t_gdata *gd);
bool		can_move_to(int x, int y, t_gdata *gd);
void		update_frame(t_player *player);
void		scale_image(t_player *player, float scl, t_coord pos, t_gdata *gd);
void		scale_pxl(mlx_image_t *img, mlx_image_t *src, int32_t w, int32_t h);
void		update_frame(t_player *player);
void		scale_image_coins(t_gdata *gd);
void		collect_pickup(t_gdata *gd);
void		copy_text_c(mlx_image_t *image, mlx_texture_t *texture);
void		ft_draw_collectable(void *param);
void		redraw_map(t_map *map, mlx_t *mlx);
bool		path_valid(t_map *map);
int			init_spikes(t_gdata *gd, int num_spikes);
void		check_spike_collision(void *param);
void		spike_init(t_gdata *gd, int x, int y, mlx_t *mlx);
void		draw_spikes(void *param);
#endif 
