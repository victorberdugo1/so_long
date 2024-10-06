/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:56:07 by victor            #+#    #+#             */
/*   Updated: 2024/10/06 23:19:46 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void process_door_tile(t_map *map, mlx_t *mlx, int i, int j)
{
    mlx_image_t *subimage;
    t_coord coords;

    if (map->grid[i][j] != 'E')
        return;

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

void	pxls_subim(mlx_image_t *sbim, mlx_texture_t *txt, int spx, int spy)
{
	int			x;
	int			y;
	uint32_t	src_x;
	uint32_t	src_y;
	uint32_t	pxl;

	y = 0;
	while (y < TILE_SIZE)
	{
		x = 0;
		while (x < TILE_SIZE)
		{
			src_x = spx * TILE_SIZE + x;
			src_y = spy * TILE_SIZE + y;
			if (src_x < txt->width && src_y < txt->height)
			{
				pxl = get_pixel(txt->pixels, src_x, src_y, txt->width);
				pxl = convert_pixel(pxl);
				mlx_put_pixel(sbim, x, y, pxl);
			}
			x++;
		}
		y++;
	}
}

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

int all_collected(t_map *m)
{
    int total;
    int collected = 0;
    int i = 0;

    if (m->collects == NULL)
        return 0;
    total = count_collectables(m);
    while (i < total)
    {
        if (m->collects[i].pick)
            collected++;
        i++;
    }
    if (collected == total)
        return 1;
    else
        return 0;
}

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
		//if (all_collected(mp))
		//	return ((t_coord){3, 3});
		return ((t_coord){2, 3});
	}
	return ((t_coord){-1, -1});
}
