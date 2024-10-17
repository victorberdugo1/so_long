/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:53:43 by victor            #+#    #+#             */
/*   Updated: 2024/10/17 20:29:40 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* ************************************************************************** */
/* Retrieves the pixel color from the given pixel data at specified           */
/* coordinates (src_x, src_y) and width. Returns the pixel color as a         */
/* uint32_t value.                                                            */
/* ************************************************************************** */
uint32_t	get_pixel(uint8_t *pixels, int32_t src_x, int32_t src_y, int width)
{
	int			pixel_index;
	uint32_t	px;

	pixel_index = (src_y * width + src_x) * 4;
	px = *(uint32_t *)&pixels[pixel_index];
	return (px);
}

/* ************************************************************************** */
/* Converts a pixel color value to a format suitable for rendering in the     */
/* graphical context. Returns the converted pixel color as a uint32_t value. */
/* ************************************************************************** */
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

/* ************************************************************************** */
/* Creates a pixel value in a specific format using the provided color        */
/* components (blue, green, red, alpha). This function packs the individual   */
/* color components into a single 32-bit integer suitable for use in image    */
/* rendering or manipulation.                                                 */
/* ************************************************************************** */
uint32_t	ft_pixel(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

/* ************************************************************************** */
/* Scales the pixel data from the source image to fit the new dimensions.     */
/* Then handles memory for the resized image by copying the pixel data.       */
/* ************************************************************************** */
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

/* ************************************************************************** */
/* Creates a new background image filled with a solid color to cover the      */
/* window. Deletes the previous background image if it exists, allocates      */
/* a new image, and fills it with the specified color. Finally, it draws the  */
/* background image to the window.                                            */
/* ************************************************************************** */
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
