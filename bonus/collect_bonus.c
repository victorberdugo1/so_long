/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:31:26 by victor            #+#    #+#             */
/*   Updated: 2024/10/15 09:51:38 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	count_collectables(t_map *map)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < map->hgt)
	{
		x = 0;
		while (x < map->wdt)
		{
			if (map->grid[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	init_collectables(t_gdata *gd)
{
	int	x;
	int	y;
	int	idx;

	idx = 0;
	y = 0;
	gd->map->collectible_pos = malloc(gd->coins * sizeof(t_coord));
	if (!gd->map->collectible_pos)
		exit(EXIT_FAILURE);
	while (y < gd->map->hgt)
	{
		x = 0;
		while (x < gd->map->wdt)
		{
			if (gd->map->grid[y][x] == 'C')
			{
				collect_init(&gd->map->collects[idx], x, y, gd->mlx);
				gd->map->collectible_pos[idx].x = x;
				gd->map->collectible_pos[idx].y = y;
				idx++;
			}
			x++;
		}
		y++;
	}
}

int	init_collectables_from_map(t_gdata *gamedata)
{
	gamedata->player->xy_p.x = gamedata->map->player_pos.x * TILE_SIZE + 32;
	gamedata->player->xy_p.y = gamedata->map->player_pos.y * TILE_SIZE + 32;
	gamedata->coins = count_collectables(gamedata->map);
	gamedata->map->collects = malloc(sizeof(t_collect) * gamedata->coins);
	if (!gamedata->map->collects)
	{
		ft_printf("Error\nFailed to allocate memory for collectables\n");
		return (0);
	}
	init_collectables(gamedata);
	return (1);
}

void	collect_init(t_collect *coll, int x, int y, mlx_t *mlx)
{
	coll->xy_c.x = x;
	coll->xy_c.y = y;
	coll->scale_c = 1.0f;
	coll->pick = false;
	coll->txt_c = mlx_load_png("textures/coin.png");
	if (!coll->txt_c)
		return ;
	coll->image_c = mlx_new_image(mlx, coll->txt_c->width, coll->txt_c->height);
	if (!coll->image_c)
	{
		mlx_delete_texture(coll->txt_c);
		return ;
	}
	coll->image_c = mlx_texture_to_image(mlx, coll->txt_c);
}
