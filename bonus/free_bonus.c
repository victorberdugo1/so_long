/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 07:50:05 by victor            #+#    #+#             */
/*   Updated: 2024/10/15 09:51:38 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_player(t_player *player, t_gdata *gd)
{
	int	i;

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
		player->image_p = NULL;
	}
	if (player->resize_p)
	{
		mlx_delete_image(gd->mlx, player->resize_p);
		player->resize_p = NULL;
	}
	if (player->texture_p)
	{
		mlx_delete_texture(player->texture_p);
		player->texture_p = NULL;
	}
}

void	free_collects(t_collect *collects, int coin_count, t_gdata *gd)
{
	int	i;

	i = 0;
	while (i < coin_count)
	{
		if (collects[i].image_c != NULL)
		{
			mlx_delete_image(gd->mlx, collects[i].image_c);
			collects[i].image_c = NULL;
		}
		if (collects[i].resize_c != NULL)
		{
			mlx_delete_image(gd->mlx, collects[i].resize_c);
			collects[i].resize_c = NULL;
		}
		if (collects[i].txt_c != NULL)
		{
			mlx_delete_texture(collects[i].txt_c);
			collects[i].txt_c = NULL;
		}
		i++;
	}
	free(collects);
	collects = NULL;
}

void	free_map(t_map *map, t_gdata *gd)
{
	int	i;

	if (map->full_m)
		mlx_delete_image(gd->mlx, map->full_m);
	if (map->resize_m)
		mlx_delete_image(gd->mlx, map->resize_m);
	if (map->tiles)
	{
		i = -1;
		while (++i < map->wdt * map->hgt)
			if (map->tiles[i])
				mlx_delete_image(gd->mlx, map->tiles[i]);
		free(map->tiles);
	}
	if (map->texture_m)
		mlx_delete_texture(map->texture_m);
	i = -1;
	while (++i < map->hgt)
		free(map->grid[i]);
	free(map->grid);
	map->grid = NULL;
	if (map->collectible_pos)
		free(map->collectible_pos);
	if (map->collects)
		free_collects(map->collects, gd->coins, gd);
}

void	free_resources(t_gdata *gamedata)
{
	if (gamedata->player)
	{
		free_player(gamedata->player, gamedata);
		gamedata->player = NULL;
	}
	if (gamedata->map)
	{
		free_map(gamedata->map, gamedata);
		free(gamedata->map);
		gamedata->map = NULL;
	}
	if (gamedata->mlx)
	{
		mlx_terminate(gamedata->mlx);
		gamedata->mlx = NULL;
	}
}
