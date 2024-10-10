/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:57:47 by victor            #+#    #+#             */
/*   Updated: 2024/10/10 12:25:01 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_draw_collectable(void *param)
{
	t_gdata		*gd;
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
			x_off = (gd->window_width / 2) - (
					(gd->player->xy_p.x - coin->xy_c.x * TILE_SIZE)
					* gd->player->scale);
			y_off = (gd->window_height / 2) -(
					(gd->player->xy_p.y - coin->xy_c.y * TILE_SIZE)
					* gd->player->scale);
			coin->resize_c->instances[0].x = x_off;
			coin->resize_c->instances[0].y = y_off;
		}
	}
}

bool	try_pickup(t_player *player, t_collect *coin, int range)
{
	float	player_real_x;
	float	player_real_y;
	float	coin_real_x;
	float	coin_real_y;

	player_real_x = player->xy_p.x;
	player_real_y = player->xy_p.y;
	coin_real_x = coin->xy_c.x * TILE_SIZE + TILE_SIZE / 2;
	coin_real_y = coin->xy_c.y * TILE_SIZE + TILE_SIZE / 2;
	if (player_real_x >= (coin_real_x - range / 2)
		&& player_real_x <= (coin_real_x + range / 2)
		&& player_real_y >= (coin_real_y - range / 2)
		&& player_real_y <= (coin_real_y + range / 2))
	{
		coin->pick = true;
		coin->xy_c.x = -1000;
		coin->xy_c.y = -1000;
		return (true);
	}
	return (false);
}

void	collect_pickup(t_gdata *gd)
{
	int			idx;
	int			pickup_range;
	t_collect	*coin;

	pickup_range = 64;
	idx = -1;
	while (++idx < gd->coins)
	{
		coin = &gd->map->collects[idx];
		if (!coin->pick && try_pickup(gd->player, coin, pickup_range))
		{
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

bool	update_coin_image(t_gdata *gd, t_collect *coin)
{
	uint32_t	new_w;
	uint32_t	new_h;

	new_w = (uint32_t)(coin->image_c->width * gd->map->scale);
	new_h = (uint32_t)(coin->image_c->height * gd->map->scale);
	if (!coin->resize_c)
	{
		coin->resize_c = mlx_new_image(gd->mlx,
				coin->image_c->width, coin->image_c->height);
		if (!coin->resize_c)
			return (false);
	}
	mlx_delete_image(gd->mlx, coin->resize_c);
	coin->resize_c = mlx_new_image(gd->mlx, new_w, new_h);
	if (!coin->resize_c)
		return (false);
	scale_pxl(coin->resize_c, coin->image_c, new_w, new_h);
	return (true);
}

void	scale_image_coins(t_gdata *gd)
{
	int			idx;
	int			x_set;
	int			y_set;
	t_collect	*coin;

	idx = -1;
	while (++idx < gd->coins)
	{
		coin = &gd->map->collects[idx];
		if (!update_coin_image(gd, coin))
			continue ;
		x_set = (gd->window_width / 2) - (
				(gd->player->xy_p.x - coin->xy_c.x * TILE_SIZE)
				+ (gd->player->scale * TILE_SIZE) / 2);
		y_set = (gd->window_height / 2) - (
				(gd->player->xy_p.y - coin->xy_c.y * TILE_SIZE)
				+ (gd->player->scale * TILE_SIZE) / 2);
		mlx_image_to_window(gd->mlx, coin->resize_c, x_set, y_set);
	}
}
