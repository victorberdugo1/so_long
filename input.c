/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:26:04 by victor            #+#    #+#             */
/*   Updated: 2024/10/09 17:14:08 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	bgclean(mlx_t *mlx, int32_t width, int32_t height)
{
	mlx_image_t	*bg_image;
	int32_t		j;
	int32_t		i;
	uint32_t	color;

	bg_image = NULL;
	color = ft_pixel(0, 122, 51, 255);
	if (bg_image != NULL)
		mlx_delete_image(mlx, bg_image);
	bg_image = mlx_new_image(mlx, width, height);
	if (!bg_image)
		return ;
	j = -1;
	while (++j < height)
	{
		i = -1;
		while (++i < width)
			mlx_put_pixel(bg_image, i, j, color);
	}
	mlx_image_to_window(mlx, bg_image, 0, 0);
}

void	scl_img_map(mlx_image_t **im, mlx_image_t **siz, float scl, t_gdata *gd)
{
	uint32_t	new_w;
	uint32_t	new_h;
	int32_t		x;
	int32_t		y;
	uint32_t	src_x;
	uint32_t	src_y;
	uint32_t	pixel;
	int			map_x_offset;
	int			map_y_offset;

	if (!im || !*im || scl <= 0)
		return ;
	map_x_offset = (gd->window_width / 2) - ((gd->player->xy_p.x) + (gd->player->scale * TILE_SIZE) / 2);
	map_y_offset = (gd->window_height / 2) - ((gd->player->xy_p.y) + (gd->player->scale * TILE_SIZE) / 2);
	new_w = (uint32_t)((*im)->width * scl);
	new_h = (uint32_t)((*im)->height * scl);
	*siz = mlx_new_image(gd->mlx, new_w, new_h);
	if (!*siz)
		return ;
	y = -1;
	while (++y < (int32_t)new_h)
	{
		x = -1;
		while (++x < (int32_t)new_w)
		{
			src_x = (x * (*im)->width) / new_w;
			src_y = (y * (*im)->height) / new_h;
			pixel = get_pixel((*im)->pixels, src_x, src_y, (*im)->width);
			pixel = convert_pixel(pixel);
			mlx_put_pixel(*siz, x, y, pixel);
		}
	}
	mlx_image_to_window(gd->mlx, gd->map->resize_m, map_x_offset, map_y_offset);
}

void ft_draw(void *param)
{
	t_gdata		*gd;
	t_player	*pl;
	t_coord		pos;

	gd = (t_gdata *)param;
	pl = gd->player;
	pos.x = gd->window_width / 2 - (pl->scale * TILE_SIZE) / 2;
	pos.y = gd->window_height / 2 - (pl->scale * TILE_SIZE) / 2;
	scale_image(pl, pl->scale, pos, gd);
}

void	scl_img_coins(t_gdata *gd)
{
	uint32_t	new_w;
	uint32_t	new_h;
	uint32_t	x;
	uint32_t	y;
	uint32_t	src_x;
	uint32_t	src_y;
	uint32_t	pixel;
	t_collect	*coin;
	int			idx;
	int			x_set;
	int			y_set;

	idx = -1;
	while (++idx < gd->coins)
	{
		coin = &gd->map->collects[idx];
		if (!coin->resize_c)
		{
			coin->resize_c = mlx_new_image(gd->mlx, coin->image_c->width, coin->image_c->height);
			if (!coin->resize_c)
				continue ;
		}
		new_w = (uint32_t)(coin->image_c->width * gd->map->scale);
		new_h = (uint32_t)(coin->image_c->height * gd->map->scale);
		mlx_delete_image(gd->mlx, coin->resize_c);
		coin->resize_c = mlx_new_image(gd->mlx, new_w, new_h);
		if (!coin->resize_c)
			continue ;
		y = -1;
		while (++y < new_h)
		{
			x = -1;
			while (++x < new_w)
			{
				src_x = (x * coin->image_c->width) / new_w;
				src_y = (y * coin->image_c->height) / new_h;
				pixel = get_pixel(coin->image_c->pixels, src_x, src_y, coin->image_c->width);
				pixel = convert_pixel(pixel);
				mlx_put_pixel(coin->resize_c, x, y, pixel);
			}
		}
		x_set = (gd->window_width / 2) - ((gd->player->xy_p.x - coin->xy_c.x * TILE_SIZE) + (gd->player->scale * TILE_SIZE) / 2);
		y_set = (gd->window_height / 2) - ((gd->player->xy_p.y - coin->xy_c.y * TILE_SIZE) + (gd->player->scale * TILE_SIZE) / 2);
		mlx_image_to_window(gd->mlx, coin->resize_c, x_set, y_set);
	}
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_gdata			*gd;
	float				x;
	float				y;

	gd = (t_gdata *)param;
	if (!gd || !gd->player)
		return ;
	gd->window_width = width;
	gd->window_height = height;
	bgclean(gd->mlx, width, height);
	x = (float)width / (float)gd->map->full_m->width;
	y = (float)height / (float)gd->map->full_m->height;
	gd->map->scale = fmaxf(x, y);
	gd->player->scale = fmaxf(x, y);
	scl_img_map(&gd->map->full_m, &gd->map->resize_m, fmaxf(x, y), gd);
	scl_img_coins(gd);
}

void	ft_draw_map(void *param)
{
	t_gdata	*gd;
	int			x_off;
	int			y_off;

	gd = (t_gdata *)param;
	x_off = (gd->window_width / 2) - (gd->player->xy_p.x * gd->player->scale);
	y_off = (gd->window_height / 2) - (gd->player->xy_p.y * gd->player->scale);
	if (gd->map->resize_m && gd->map->resize_m->count > 0)
	{
		gd->map->resize_m->instances[0].x = x_off;
		gd->map->resize_m->instances[0].y = y_off;
	}
}

void	ft_draw_coll(void *param)
{
	t_gdata	*gd;
	t_collect	*coin;
	int			x_off;
	int			y_off;
	int			idx;

	gd = (t_gdata *)param;
	if (!gd->map->resize_m->instances)
		return ;
	idx = -1;
	while (++idx < gd->coins)
	{
		coin = &gd->map->collects[idx];
		if (!coin->pick)
		{
			x_off = (gd->window_width / 2) - ((gd->player->xy_p.x - coin->xy_c.x * TILE_SIZE) * gd->player->scale);
			y_off = (gd->window_height / 2) - ((gd->player->xy_p.y - coin->xy_c.y * TILE_SIZE) * gd->player->scale);
			coin->resize_c->instances[0].x = x_off;
			coin->resize_c->instances[0].y = y_off;
		}
	}
}

void	redraw_map(t_map *map, mlx_t *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->hgt)
	{
		j = -1;
		while (++j < map->wdt)
		{
			if (map->grid[i][j] == 'E')
				process_door_tile(map, mlx, i, j);
		}
	}
	combine_tiles(map);
}

void	collect_pickup(t_gdata *gd)
{
	int			pickup_range;	
	float		player_real_x;
	float		player_real_y;
	int			idx;
	t_collect	*coin;
	float		coin_real_x;
	float		coin_real_y;

	pickup_range = 64;
	player_real_x = gd->player->xy_p.x;
	player_real_y = gd->player->xy_p.y;
	idx = -1;
	while (++idx < gd->coins)
	{
		coin = &gd->map->collects[idx];
		if (!coin->pick)
		{
			coin_real_x = coin->xy_c.x * TILE_SIZE + TILE_SIZE / 2;
			coin_real_y = coin->xy_c.y * TILE_SIZE + TILE_SIZE / 2;
			if (player_real_x >= (coin_real_x - pickup_range / 2)
				&& player_real_x <= (coin_real_x + pickup_range / 2)
				&& player_real_y >= (coin_real_y - pickup_range / 2)
				&& player_real_y <= (coin_real_y + pickup_range / 2))
			{
				coin->pick = true;
				coin->xy_c.x = -1000;
				coin->xy_c.y = -1000;
				if (all_collected(gd->map) && !gd->map->collect_flag)
				{
					gd->map->collect_flag = true;
					redraw_map(gd->map, gd->mlx);
					resize_hook(gd->window_width, gd->window_height, gd);
				}
				break ;
			}
		}
	}
}

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_gdata	*gd;
	t_player	*player;
	int			frame_offset;

	gd = (t_gdata *)param;
	player = gd->player;
	if (mlx_is_key_down(gd->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(gd->mlx);
	frame_offset = -1;
	if (!player->moving)
	{
		player->dest_p.x = (int)(player->xy_p.x / TILE_SIZE);
		player->dest_p.y = (int)(player->xy_p.y / TILE_SIZE);
	}
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
	{
		if (!player->moving)
		{
			player->dest_p.y -= 1;
			player->moving = true;
			frame_offset = 8;
		}
	}
	else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
	{
		if (!player->moving)
		{
			player->dest_p.y += 1;
			player->moving = true;
			frame_offset = 0;
		}
	}
	else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
	{
		if (!player->moving)
		{
			player->dest_p.x -= 1;
			player->moving = true;
			frame_offset = 4;
		}
	}
	else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
	{
		if (!player->moving)
		{
			player->dest_p.x += 1;
			player->moving = true;
			frame_offset = 12;
		}
	}
	if (frame_offset >= 0)
	{
		player->current_frame = (player->current_frame + 1) % 4 + frame_offset;
		collect_pickup(gd);
	}
}
