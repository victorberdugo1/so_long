/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:31:26 by victor            #+#    #+#             */
/*   Updated: 2024/10/17 18:17:03 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* ************************************************************************** */
/* Initializes collectables from the map, sets player coordinates, counts the */
/* collectables, and allocates memory for them. Returns 1 on success, 0 on    */
/* failure. Handles memory allocation errors with an error message.           */
/* ************************************************************************** */
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

/* ************************************************************************** */
/* Counts the number of collectable items ('C') present in the map grid.      */
/* Iterates through the map's height and width to find and tally the items.   */
/* Returns the total count of collectables.                                   */
/* ************************************************************************** */
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

/* ************************************************************************** */
/* Initializes collectables by iterating through the map's grid, locating     */
/* each collectible ('C'), and storing its position. Allocates memory for     */
/* collectible positions and initializes each collectible. Exits on failure.  */
/* ************************************************************************** */
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

/* ************************************************************************** */
/* Initializes a collectable object by setting its position, scale, and       */
/* loading the associated texture and image. Manages memory allocation and    */
/* handles errors by freeing resources if necessary.                          */
/* ************************************************************************** */
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
