/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:55:39 by vberdugo          #+#    #+#             */
/*   Updated: 2024/09/27 23:54:52 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

	if (i == 0 || i == map->height - 1 || j == 0 || j == map->width - 1)
		coords = get_border_sprite(map, i, j);
	else
		coords = get_inner_sprite(map, i, j);
	subimage = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
	if (!subimage)
	{
		mlx_delete_texture(map->texture_m);
		return (mlx_close_window(mlx), free(map->images_m));
	}
	pxls_subim(subimage, map->texture_m, coords.x, coords.y);
	map->images_m[i * map->width + j] = subimage;
	mlx_image_to_window(mlx, subimage, j * TILE_SIZE, i * TILE_SIZE);
}

void	draw_map(t_map *map, mlx_t *mlx)
{
	int	i;
	int	j;

	i = 0;
	map->images_m = malloc(map->width * map->height * sizeof(mlx_image_t *));
	if (!map->images_m)
		return ;
	map->texture_m = mlx_load_png("textures/map.png");
	if (!map->texture_m)
		return (free(map->images_m), mlx_close_window(mlx));
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			process_tile(map, mlx, i, j);
			j++;
		}
		i++;
	}
}
