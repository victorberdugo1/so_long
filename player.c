/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:43:15 by victor            #+#    #+#             */
/*   Updated: 2024/10/13 14:24:45 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_frame(t_player *player)
{
	static float	last_frame_time = 0;
	float			current_time;
	float			delta_time;

	current_time = mlx_get_time();
	delta_time = current_time - last_frame_time;
	last_frame_time = current_time;
	player->frame_timer += delta_time;
	if (player->frame_timer >= player->animation_speed)
	{
		player->frame_timer -= player->animation_speed;
		if (player->current_frame >= 0 && player->current_frame <= 3)
			player->current_frame = (player->current_frame + 1) % 4;
		else if (player->current_frame >= 8 && player->current_frame <= 11)
			player->current_frame = (player->current_frame + 1) % 4 + 8;
		else if (player->current_frame >= 4 && player->current_frame <= 7)
			player->current_frame = (player->current_frame + 1) % 4 + 4;
		else if (player->current_frame >= 12 && player->current_frame <= 15)
			player->current_frame = (player->current_frame + 1) % 4 + 12;
	}
}

void	scale_image(t_player *player, float scl, t_coord pos, t_gdata *gd)
{
	mlx_image_t	**im;
	mlx_image_t	**siz;
	int32_t		new_w;
	int32_t		new_h;

	im = &player->image_p[player->current_frame];
	siz = &player->resize_p;
	if (!im || !*im || scl <= 0)
		return ;
	new_w = (int32_t)((*im)->width * scl);
	new_h = (int32_t)((*im)->height * scl);
	if (siz != NULL)
		mlx_delete_image(gd->mlx, *siz);
	*siz = mlx_new_image(gd->mlx, new_w, new_h);
	if (!*siz)
		return ;
	scale_pxl(*siz, *im, new_w, new_h);
	mlx_image_to_window(gd->mlx, *siz, pos.x, pos.y);
}

void	copy_text(mlx_image_t *sub, mlx_texture_t *txt, int x_fset, int y_fset)
{
	int			x;
	int			y;
	uint32_t	pxl;
	uint32_t	src_x;
	uint32_t	src_y;

	y = -1;
	while (++y < TILE_SIZE)
	{
		x = -1;
		while (++x < TILE_SIZE)
		{
			src_x = x_fset + x;
			src_y = y_fset + y;
			if (src_x < txt->width && src_y < txt->height)
			{
				pxl = get_pixel(txt->pixels, src_x, src_y, txt->width);
				pxl = convert_pixel(pxl);
				mlx_put_pixel(sub, x, y, pxl);
			}
		}
	}
}

void	process_player_tile(t_player *player, mlx_t *mlx, int frame_index)
{
	mlx_image_t	*subimage;
	int32_t		x_offset;
	int32_t		y_offset;
	int			frames_per_row;
	int			frame_width;

	frames_per_row = 4;
	frame_width = TILE_SIZE;
	if (frame_index < 0 || frame_index >= player->total_frames)
		return ;
	x_offset = (frame_index % frames_per_row) * frame_width;
	y_offset = (frame_index / frames_per_row) * TILE_SIZE;
	subimage = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	if (!subimage)
	{
		mlx_delete_texture(player->texture_p);
		return ;
	}
	copy_text(subimage, player->texture_p, x_offset, y_offset);
	player->image_p[frame_index] = subimage;
}

void	player_init(t_player *player, mlx_t *mlx)
{
	mlx_texture_t	*texture;
	int				i;

	texture = mlx_load_png("./textures/player.png");
	if (!texture)
		return (mlx_close_window(mlx));
	player->texture_p = texture;
	player->speed = 1;
	player->dest_p = player->xy_p;
	player->moving = false;
	player->win = false;
	player->animation_speed = 0.1f;
	player->frame_timer = 0.0f;
	player->current_frame = 0;
	player->move_count = 0;
	player->total_frames = 16;
	player->image_p = malloc(sizeof(mlx_image_t *) * player->total_frames);
	if (!player->image_p)
		return (mlx_delete_texture(texture), mlx_close_window(mlx));
	i = -1;
	while (++i < player->total_frames)
		process_player_tile(player, mlx, i);
}
