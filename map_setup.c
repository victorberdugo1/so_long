/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:55:39 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/17 14:04:06 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* ************************************************************************** */
/* Initializes the full map image, allocates memory for tiles, loads the      */
/* map texture, creates the full image, processes each tile, and combines     */
/* them into the final rendering.                                             */
/* ************************************************************************** */
void	map_start(t_map *map, mlx_t *mlx)
{
	int	i;
	int	j;

	map->full_m = mlx_new_image(mlx, map->wdt * 64, map->hgt * 64);
	if (!map->full_m)
		return ;
	map->tiles = malloc(map->wdt * map->hgt * sizeof(mlx_image_t *));
	if (!map->tiles)
		return (mlx_delete_image(mlx, map->full_m));
	map->texture_m = mlx_load_png("textures/map.png");
	if (!map->texture_m)
		return (free(map->tiles), mlx_delete_image(mlx, map->full_m));
	create_full_image(map, mlx);
	i = -1;
	while (++i < map->hgt)
	{
		j = -1;
		while (++j < map->wdt)
			process_tile(map, mlx, i, j);
	}
	combine_tiles(map);
}

/* ************************************************************************** */
/* Creates the full image and resized image for the map. Handles memory       */
/* allocation and resource management. Closes window on allocation failure.   */
/* ************************************************************************** */
void	create_full_image(t_map *map, mlx_t *mlx)
{
	map->full_m = mlx_new_image(mlx, map->wdt * 64, map->hgt * 64);
	if (!map->full_m)
	{
		mlx_delete_texture(map->texture_m);
		free(map->tiles);
		mlx_close_window(mlx);
		return ;
	}
	map->resize_m = mlx_new_image(mlx, map->wdt * 64, map->hgt * 64);
	if (!map->resize_m)
	{
		mlx_delete_texture(map->texture_m);
		mlx_delete_image(mlx, map->full_m);
		free(map->tiles);
		mlx_close_window(mlx);
		return ;
	}
}

/* ************************************************************************** */
/* Processes an individual tile in the map, creating a subimage for the tile  */
/* based on its position (border or inner). Allocates memory for the tile     */
/* image and fills it with pixel data from the main texture.                  */
/* ************************************************************************** */
void	process_tile(t_map *map, mlx_t *mlx, int i, int j)
{
	mlx_image_t	*subimage;
	t_coord		coords;

	if (i == 0 || i == map->hgt - 1 || j == 0 || j == map->wdt - 1)
		coords = get_border_sprite(map, i, j);
	else
		coords = get_inner_sprite(map, i, j);
	subimage = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	if (!subimage)
	{
		mlx_delete_texture(map->texture_m);
		return (mlx_close_window(mlx), free(map->tiles));
	}
	pxls_subim(subimage, map->texture_m, coords.x, coords.y);
	map->tiles[i * map->wdt + j] = subimage;
}

/* ************************************************************************** */
/* Retrieves the coordinates of the border sprite based on the tile's         */
/* position in the map. Returns the corresponding sprite coordinates for the  */
/* specified border tile.                                                     */
/* ************************************************************************** */
t_coord	get_border_sprite(t_map *map, int coord_y, int coord_x)
{
	if (coord_y == 0)
	{
		if (coord_x == 0)
			return ((t_coord){0, 0});
		else if (coord_x == map->wdt - 1)
			return ((t_coord){2, 0});
		else
			return ((t_coord){1, 0});
	}
	else if (coord_y == map->hgt - 1)
	{
		if (coord_x == 0)
			return ((t_coord){3, 0});
		else if (coord_x == map->wdt - 1)
			return ((t_coord){1, 1});
		else
			return ((t_coord){0, 1});
	}
	if (coord_x == 0)
		return ((t_coord){2, 1});
	return ((t_coord){3, 1});
}

/* ************************************************************************** */
/* Retrieves the coordinates of the inner sprite based on the tile's type in  */
/* the map. Returns the corresponding sprite coordinates for the specified    */
/* tile, which can be a player, collectible, or wall tile.                    */
/* ************************************************************************** */
t_coord	get_inner_sprite(t_map *mp, int y, int x)
{
	if (mp->grid[y][x] == '0' || mp->grid[y][x] == 'P' || mp->grid[y][x] == 'C')
	{
		if ((rand() % 3) == 0)
			return ((t_coord){0, 2});
		else if ((rand() % 3) == 1)
			return ((t_coord){1, 2});
		return ((t_coord){2, 2});
	}
	else if (mp->grid[y][x] == '1')
	{
		if ((rand() % 3) == 0)
			return ((t_coord){3, 2});
		else if ((rand() % 3) == 1)
			return ((t_coord){0, 3});
		return ((t_coord){1, 3});
	}
	else if (mp->grid[y][x] == 'E')
	{
		return ((t_coord){2, 3});
	}
	return ((t_coord){-1, -1});
}
