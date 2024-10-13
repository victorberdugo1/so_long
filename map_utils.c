/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:56:07 by victor            #+#    #+#             */
/*   Updated: 2024/10/13 21:18:48 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	scl_m(mlx_image_t *im, mlx_image_t **siz, t_dim n_size, t_gdata *gd)
{
	int32_t		x;
	int32_t		y;
	uint32_t	src_x;
	uint32_t	src_y;
	uint32_t	pixel;

	*siz = mlx_new_image(gd->mlx, n_size.width, n_size.height);
	if (!*siz)
		return ;
	y = -1;
	while (++y < (int32_t)n_size.height)
	{
		x = -1;
		while (++x < (int32_t)n_size.width)
		{
			src_x = (x * im->width) / n_size.width;
			src_y = (y * im->height) / n_size.height;
			pixel = get_pixel(im->pixels, src_x, src_y, im->width);
			pixel = convert_pixel(pixel);
			mlx_put_pixel(*siz, x, y, pixel);
		}
	}
}

void	sclmap(mlx_image_t **im, mlx_image_t **siz, float scl, t_gdata *gd)
{
	t_dim	new_size;
	int		map_x_offset;
	int		map_y_offset;

	if (!im || !*im || scl <= 0)
		return ;
	map_x_offset = (gd->window_width / 2) - (
			(gd->player->xy_p.x) + (gd->player->scale * TILE_SIZE) / 2);
	map_y_offset = (gd->window_height / 2) - (
			(gd->player->xy_p.y) + (gd->player->scale * TILE_SIZE) / 2);
	new_size.width = (uint32_t)((*im)->width * scl);
	new_size.height = (uint32_t)((*im)->height * scl);
	scl_m(*im, siz, new_size, gd);
	mlx_image_to_window(gd->mlx, gd->map->resize_m, map_x_offset, map_y_offset);
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
