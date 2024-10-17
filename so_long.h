/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:34 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/17 20:57:09 by victor           ###   ########.fr       */
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
# define WIDTH 800
# define HEIGHT 600
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
	bool			valid;
	bool			closed;
	t_coord			exit_pos;
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
}	t_gdata;

//Map Validation and Initialization
bool		path_valid(t_map *map);
t_map		*read_map(const char *filename);
int			map_size(const char *filename, int *width, int *height);
t_map		*init_map(int width, int height);
char		**allocate_grid(int width, int height);
t_map		*fill_map(const char *filename, int width, t_map *map);
bool		validate_map(t_map *map);
bool		validate_ch(t_map *map, int x, int y, int *cnt);
bool		validate_walls(t_map *map);
bool		path_valid(t_map *map);
char		**create_visited_array(int height, int width);
bool		dfs(t_map *map, int x, int y, char **visited);
bool		is_valid_move(t_map *map, int x, int y, char **visited);
//Map Rendering and Image Setup
void		map_start(t_map *map, mlx_t *mlx);
void		create_full_image(t_map *map, mlx_t *mlx);
void		process_tile(t_map *map, mlx_t *mlx, int i, int j);
t_coord		get_border_sprite(t_map *map, int coord_y, int coord_x);
t_coord		get_inner_sprite(t_map *mp, int y, int x);
void		combine_tiles(t_map *map);
void		draw_tile(t_map *map, int i, int j);
void		pxls_subim(mlx_image_t *sbim, mlx_texture_t *txt, int spx, int spy);
//Player Initialization
void		player_init(t_player *player, mlx_t *mlx);
void		process_player_tile(t_player *player, mlx_t *mlx, int frame_index);
void		cp_tx(mlx_image_t *sub, mlx_texture_t *txt, int x_fset, int y_fset);
//Collectables Initialization
int			init_collectables_from_map(t_gdata *gamedata);
int			count_collectables(t_map *map);
void		init_collectables(t_gdata *gd);
void		collect_init(t_collect *coll, int x, int y, mlx_t *mlx);
//Rezise hook
void		resize_hook(int32_t width, int32_t height, void *param);
void		bgclean(t_gdata *gd, int32_t width, int32_t height);
void		sclmap(mlx_image_t **im, mlx_image_t **siz, float scl, t_gdata *gd);
void		scale_image_coins(t_gdata *gd);
//Key hook
void		ft_hook(mlx_key_data_t keydata, void *param);
void		collect_pickup(t_gdata *gd);
int			all_collected(t_map *map);
void		redraw_map(t_map *map, mlx_t *mlx);
void		process_door_tile(t_map *map, mlx_t *mlx, int i, int j);
//Loop hook
void		ft_render(void *param);
void		ft_move(t_player *player, t_gdata *gd);
void		update_frame(t_player *player);
void		update_pos(t_player *player, float tgt_x, float tgt_y, t_gdata *gd);
void		moving_pos(t_player *player, float dist_x, float dist_y);
bool		can_move_to(int x, int y, t_gdata *gd);
void		ft_draw(void *param);
void		scale_image(t_player *player, float scl, t_coord pos, t_gdata *gd);
void		ft_draw_map(void *param);
void		ft_draw_collectable(void *param);
//Free
void		free_resources(t_gdata *gamedata);
void		free_collects(t_collect *collects, int coin_count, t_gdata *gd);
//Pixel Modification
uint32_t	get_pixel(uint8_t *pixels, int32_t src_x, int32_t src_y, int width);
uint32_t	convert_pixel(uint32_t px);
uint32_t	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
void		scale_pxl(mlx_image_t *img, mlx_image_t *src, int32_t w, int32_t h);
#endif 
