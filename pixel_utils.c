/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:53:43 by victor            #+#    #+#             */
/*   Updated: 2024/09/27 23:25:13 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

uint32_t	pixel_texture(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	uint32_t	index;
	uint8_t		*pixel;

	index = (y * texture->width + x) * 4;
	pixel = &texture->pixels[index];
	return (ft_pixel(pixel[0], pixel[1], pixel[2], pixel[3]));
}
