/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:56:07 by victor            #+#    #+#             */
/*   Updated: 2024/10/17 14:33:22 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* ************************************************************************** */
/* Iterates through the map's grid and draws each tile at its corresponding   */
/* position on the full image. This function ensures that all tiles are       */
/* rendered correctly based on the map's layout.                              */
/* ************************************************************************** */
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

/* ************************************************************************** */
/* Draws a single tile on the full map image by retrieving pixel data from    */
/* the tile's image and placing it at the correct position based on the       */
/* specified coordinates (i, j). This function updates both the full and      */
/* resized images.                                                            */
/* ************************************************************************** */
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

/* ************************************************************************** */
/* Copies a subimage of pixels from a texture to a specified image. It takes  */
/* the source pixel coordinates from the texture, retrieves the pixel data,   */
/* converts it, and places it onto the subimage at the given coordinates.     */
/* This function iterates over the tile dimensions and handles boundary       */
/* checks to ensure that the source coordinates are within the texture bounds.*/
/* ************************************************************************** */
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
