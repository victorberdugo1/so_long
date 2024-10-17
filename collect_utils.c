/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:57:47 by victor            #+#    #+#             */
/*   Updated: 2024/10/17 20:54:55 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	try_pickup(t_player *player, t_collect *coin, int range);

/* ************************************************************************** */
/* Checks if the player can collect any nearby items and updates their state. */
/* Then handles memory for the collected items and redraws the map if all     */
/* items have been collected.                                                 */
/* ************************************************************************** */
void	collect_pickup(t_gdata *gd)
{
	int			idx;
	int			pickup_range;
	t_collect	*coin;

	pickup_range = 1;
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

/* ************************************************************************** */
/* Checks if the player is within the pickup range of a collectible item.     */
/* If the player can pick it up, updates the collectible's state and          */
/* position. Returns true if the item was picked up, false otherwise.         */
/* ************************************************************************** */
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

/* ************************************************************************** */
/* Checks if all collectible items in the map have been picked up by the      */
/* player. Counts the total collectibles and compares it to the number        */
/* of items that have been collected. Returns 1 if all are collected,         */
/* otherwise returns 0.                                                       */
/* ************************************************************************** */
int	all_collected(t_map *m)
{
	int	total;
	int	collected;
	int	i;

	collected = 0;
	i = 0;
	if (m->collects == NULL)
		return (0);
	total = count_collectables(m);
	while (i < total)
	{
		if (m->collects[i].pick)
			collected++;
		i++;
	}
	if (collected == total)
		return (1);
	else
		return (0);
}

/* ************************************************************************** */
/* Processes a door tile on the map. Creates a subimage for the door based    */
/* on its position and assigns it to the map tile grid. If subimage creation  */
/* fails, frees map textures and closes the window.                           */
/* ************************************************************************** */
void	process_door_tile(t_map *map, mlx_t *mlx, int i, int j)
{
	mlx_image_t	*subimage;
	t_coord		coords;

	if (map->grid[i][j] != 'E')
		return ;
	coords = (t_coord){3, 3};
	subimage = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	if (!subimage)
	{
		mlx_delete_texture(map->texture_m);
		return (mlx_close_window(mlx), free(map->tiles));
	}
	pxls_subim(subimage, map->texture_m, coords.x, coords.y);
	map->tiles[i * map->wdt + j] = subimage;
}
