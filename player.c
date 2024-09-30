/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:43:15 by victor            #+#    #+#             */
/*   Updated: 2024/09/30 13:17:56 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void copy_text(mlx_image_t *subimage, mlx_texture_t *texture, int x_offset, int y_offset)
{
	int x, y;
	uint32_t pxl;
	uint32_t src_x;
	uint32_t src_y;

	for (y = 0; y < TILE_SIZE; y++)
	{
		for (x = 0; x < TILE_SIZE; x++)
		{
			src_x = x_offset + x; 
			src_y = y_offset + y;
			if (src_x < texture->width && src_y < texture->height)
			{
				pxl = get_pixel(texture->pixels, src_x, src_y, texture->width);
				pxl = convert_pixel(pxl);
				mlx_put_pixel(subimage, x, y, pxl);
			}
		}
	}
}

void process_player_tile(t_player *player, mlx_t *mlx, int frame_index)
{
	mlx_image_t *subimage;
	int32_t x_offset;
	int32_t y_offset;
	int frames_per_row = 4;
	int frame_width = TILE_SIZE;

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

void player_init(t_player *player, mlx_t *mlx)
{
	float scale;
	mlx_texture_t *texture;

	scale = 1.5f;
	texture = mlx_load_png("./textures/player.png");
	if (!texture)
	{
		mlx_close_window(mlx);
		return;
	}
	player->texture_p = texture;
	player->scale = scale;
	player->xy_p.x = 0;
	player->xy_p.y = 0;
	player->win = false;
	player->animation_speed = 1.0f;
	player->frame_timer = 0.0f;
	player->current_frame = 0;
	player->total_frames = 16;
	player->image_p = malloc(sizeof(mlx_image_t *) * player->total_frames);
	if (!player->image_p)
	{
		mlx_delete_texture(texture);
		mlx_close_window(mlx);
		return;
	}
	for (int i = 0; i < player->total_frames; i++)
	{
		process_player_tile(player, mlx, i);
	}
}
