/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 07:50:05 by victor            #+#    #+#             */
/*   Updated: 2024/10/01 07:51:27 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_player(t_player *player, t_gamedata *gd)
{
	int i;

	if (player->image_p)
	{
		i = 0;
		while (i < player->total_frames)
		{
			if (player->image_p[i])
				mlx_delete_image(gd->mlx, player->image_p[i]);
			i++;
		}
		free(player->image_p);
	}

	if (player->resize_p)
		mlx_delete_image(gd->mlx, player->resize_p);

	if (player->texture_p)
		mlx_delete_texture(player->texture_p);
}

void	free_collects(t_collect *collects, int coin_count, t_gamedata *gd)
{
	int i;
	t_collect *collect;

	i = 0;
	while (i < coin_count)
	{
		collect = &collects[i];

		if (collect->image_c)
		{
			int j = 0;
			while (collect->image_c[j])
			{
				mlx_delete_image(gd->mlx, collect->image_c[j]);
				j++;
			}
			free(collect->image_c);
		}

		if (collect->resize_c)
			mlx_delete_image(gd->mlx, collect->resize_c);

		if (collect->texture_c)
			mlx_delete_texture(collect->texture_c);
		free(collect);
		i++;
	}
}
void	free_map(t_map *map, t_gamedata *gd)
{
	int i;

	if (map->full_m)
		mlx_delete_image(gd->mlx, map->full_m);

	if (map->resize_m)
		mlx_delete_image(gd->mlx, map->resize_m);

	if (map->tiles)
	{
		i = 0;
		while (i < map->wdt * map->hgt)
		{
			if (map->tiles[i])
				mlx_delete_image(gd->mlx, map->tiles[i]);
			i++;
		}
		free(map->tiles);
	}

	if (map->texture_m)
		mlx_delete_texture(map->texture_m);

	i = 0;
	while (i < map->hgt)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);

	if (map->collects)
		free_collects(map->collects, gd->coins, gd);
}

void	free_resources(t_gamedata *gamedata)
{
	if (gamedata->player)
		free_player(gamedata->player, gamedata);
	if (gamedata->map)
		free_map(gamedata->map, gamedata);
	free(gamedata->map);
}
