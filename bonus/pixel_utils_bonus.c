/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:53:43 by victor            #+#    #+#             */
/*   Updated: 2024/10/15 09:51:38 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

uint32_t	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

uint32_t	get_pixel(uint8_t *pixels, int32_t src_x, int32_t src_y, int width)
{
	int			pixel_index;
	uint32_t	px;

	pixel_index = (src_y * width + src_x) * 4;
	px = *(uint32_t *)&pixels[pixel_index];
	return (px);
}

uint32_t	convert_pixel(uint32_t px)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	alpha;

	red = (px >> 16) & 0xFF;
	green = (px >> 8) & 0xFF;
	blue = px & 0xFF;
	alpha = (px >> 24) & 0xFF;
	return (ft_pixel(blue, green, red, alpha));
}

void	scale_pxl(mlx_image_t *img, mlx_image_t *src, int32_t w, int32_t h)
{
	int32_t		x;
	int32_t		y;
	uint32_t	src_x;
	uint32_t	src_y;
	uint32_t	pixel;

	y = -1;
	while (++y < h)
	{
		x = -1;
		while (++x < w)
		{
			src_x = (x * src->width) / w;
			src_y = (y * src->height) / h;
			pixel = get_pixel(src->pixels, src_x, src_y, src->width);
			pixel = convert_pixel(pixel);
			mlx_put_pixel(img, x, y, pixel);
		}
	}
}

void	bgclean(t_gdata *gd, int32_t width, int32_t height)
{
	uint32_t	color;
	int32_t		j;
	int32_t		i;

	color = ft_pixel(0, 122, 51, 255);
	if (gd->bg_image != NULL)
		mlx_delete_image(gd->mlx, gd->bg_image);
	gd->bg_image = mlx_new_image(gd->mlx, width, height);
	if (!gd->bg_image)
		return ;
	j = -1;
	while (++j < height)
	{
		i = -1;
		while (++i < width)
		{
			mlx_put_pixel(gd->bg_image, i, j, color);
		}
	}
	mlx_image_to_window(gd->mlx, gd->bg_image, 0, 0);
}
