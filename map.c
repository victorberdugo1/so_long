/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:55:39 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/08 20:34:49 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	draw_tile(t_map *map, int i, int j)
{
	int			offset_x;
	int			offset_y;
	int			y;
	int			x;
	uint32_t	px;

	offset_x = j * TILE_SIZE;
	offset_y = i * TILE_SIZE;
	if (map->tiles[i * map->wdt + j])
	{
		y = -1;
		while (++y < TILE_SIZE)
		{
			x = -1;
			while (++x < TILE_SIZE)
			{
				px = get_pixel(map->tiles[i * map->wdt + j]->pixels, x, y, 64);
				px = convert_pixel(px);
				mlx_put_pixel(map->full_m, offset_x + x, offset_y + y, px);
				mlx_put_pixel(map->resize_m, offset_x + x, offset_y + y, px);
			}
		}
	}
}

void	combine_tiles(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->hgt)
	{
		j = -1;
		while (++j < map->wdt)
		{
			draw_tile(map, i, j);
		}
	}
}

void	draw_map(t_map *map, mlx_t *mlx)
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
