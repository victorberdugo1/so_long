/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:44:01 by victor            #+#    #+#             */
/*   Updated: 2024/10/14 20:52:28 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_draw(void *param)
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

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_gdata			*gd;
	float			x;
	float			y;

	gd = (t_gdata *)param;
	if (!gd || !gd->player)
		return ;
	gd->window_width = width;
	gd->window_height = height;
	bgclean(gd, width, height);
	x = (float)width / (float)gd->map->full_m->width;
	y = (float)height / (float)gd->map->full_m->height;
	gd->map->scale = fmaxf(x, y);
	gd->player->scale = gd->map->scale;
	sclmap(&gd->map->full_m, &gd->map->resize_m, gd->map->scale, gd);
	scale_image_coins(gd);
	gd->is_msg = false;
}

void	ft_draw_map(void *param)
{
	t_gdata	*gd;
	int		x_off;
	int		y_off;

	gd = (t_gdata *)param;
	x_off = (gd->window_width / 2) - (gd->player->xy_p.x * gd->player->scale);
	y_off = (gd->window_height / 2) - (gd->player->xy_p.y * gd->player->scale);
	if (gd->map->resize_m && gd->map->resize_m->count > 0)
	{
		gd->map->resize_m->instances[0].x = x_off;
		gd->map->resize_m->instances[0].y = y_off;
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
