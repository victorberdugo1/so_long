/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:31:26 by victor            #+#    #+#             */
/*   Updated: 2024/10/03 22:07:40 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	copy_text_c(mlx_image_t *image, mlx_texture_t *texture)
{
	uint32_t			x, y;
	uint32_t	pxl;

	for (y = 0; y < texture->height; y++)
	{
		for (x = 0; x < texture->width; x++)
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

    coll->texture_c = mlx_load_png("textures/coin.png");
    if (!coll->texture_c)
        return;
    coll->image_c = mlx_new_image(mlx, coll->texture_c->width, coll->texture_c->height);
    if (!coll->image_c)
    {
        mlx_delete_texture(coll->texture_c);
        return;
    }
    copy_text_c(coll->image_c, coll->texture_c);
}
