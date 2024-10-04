/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:31:26 by victor            #+#    #+#             */
/*   Updated: 2024/10/04 10:22:47 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	copy_text_c(mlx_image_t *image, mlx_texture_t *texture)
{
	uint32_t	x;
	uint32_t	y;
	uint32_t	pxl;

	y = -1;
	while (++y < texture->height)
	{
		x = -1;
		while (++x < texture->width)
		{
			pxl = get_pixel(texture->pixels, x, y, texture->width);
			pxl = convert_pixel(pxl);
			mlx_put_pixel(image, x, y, pxl);
		}
	}
}

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
	copy_text_c(coll->image_c, coll->txt_c);
}
