/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:44:01 by victor            #+#    #+#             */
/*   Updated: 2024/10/17 20:30:05 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* ************************************************************************** */
/* Handles window resizing by adjusting the game elements' scales to fit      */
/* the new dimensions. Updates the map and player scales, resizes the         */
/* background, and ensures collectables are also resized.                     */
/* ************************************************************************** */
void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_gdata			*gd;
	float			x;
	float			y;

	gd = (t_gdata *)param;
	if (!gd || !gd->player)
		return ;
	gd->window_width = width;
	gd->window_height = height;
	bgclean(gd, width, height);
	x = (float)width / (float)gd->map->full_m->width;
	y = (float)height / (float)gd->map->full_m->height;
	gd->map->scale = fmaxf(x, y);
	gd->player->scale = gd->map->scale;
	sclmap(&gd->map->full_m, &gd->map->resize_m, gd->map->scale, gd);
	scale_image_coins(gd);
}

void	scl_m(mlx_image_t *im, mlx_image_t **siz, t_dim n_size, t_gdata *gd);

/* ************************************************************************** */
/* Scales the given image and its corresponding size based on the specified   */
/* scale factor. It calculates the new size for the image, applies the        */
/* scaling, and positions the scaled image in the window based on the         */
/* player's position. This ensures that the map is centered around the        */
/* player's current location. Draws the map after the scale.                  */
/* ************************************************************************** */
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

/* ************************************************************************** */
/* Resizes the given image to the new dimensions by sampling pixels from      */
/* the original image, updating the resized image with the new pixel values.  */
/* Then handles memory for the resized image.                                 */
/* ************************************************************************** */
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

bool	update_coin_image(t_gdata *gd, t_collect *coin);

/* ************************************************************************** */
/* Iterates through each collectible coin and updates its image according to  */
/* the current player position and scale. Then paints the coin images on the  */
/* screen at the correct positions based on the player's view.                */
/* ************************************************************************** */
void	scale_image_coins(t_gdata *gd)
{
	int			idx;
	int			x_set;
	int			y_set;
	t_collect	*coin;

	idx = -1;
	while (++idx < gd->coins)
	{
		coin = &gd->map->collects[idx];
		if (!update_coin_image(gd, coin))
			continue ;
		x_set = (gd->window_width / 2) - (
				(gd->player->xy_p.x - coin->xy_c.x * TILE_SIZE)
				+ (gd->player->scale * TILE_SIZE) / 2);
		y_set = (gd->window_height / 2) - (
				(gd->player->xy_p.y - coin->xy_c.y * TILE_SIZE)
				+ (gd->player->scale * TILE_SIZE) / 2);
		mlx_image_to_window(gd->mlx, coin->resize_c, x_set, y_set);
	}
}

/* ************************************************************************** */
/* Updates the image of a collectible coin by resizing it according to the    */
/* current scale. Then handles memory for the resized image and returns true  */
/* if successful, or false if an error occurs during the process.             */
/* ************************************************************************** */
bool	update_coin_image(t_gdata *gd, t_collect *coin)
{
	uint32_t	new_w;
	uint32_t	new_h;

	new_w = (uint32_t)(coin->image_c->width * gd->map->scale);
	new_h = (uint32_t)(coin->image_c->height * gd->map->scale);
	if (!coin->resize_c)
	{
		coin->resize_c = mlx_new_image(gd->mlx,
				coin->image_c->width, coin->image_c->height);
		if (!coin->resize_c)
			return (false);
	}
	mlx_delete_image(gd->mlx, coin->resize_c);
	coin->resize_c = mlx_new_image(gd->mlx, new_w, new_h);
	if (!coin->resize_c)
		return (false);
	scale_pxl(coin->resize_c, coin->image_c, new_w, new_h);
	return (true);
}
