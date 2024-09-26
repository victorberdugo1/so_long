/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:43:15 by victor            #+#    #+#             */
/*   Updated: 2024/09/26 09:59:35 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

uint32_t	pixel_texture(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	uint32_t	index;
	uint8_t		*pixel;

	index = (y * texture->width + x) * 4;
	pixel = &texture->pixels[index];
	return (ft_pixel(pixel[0], pixel[1], pixel[2], pixel[3]));
}

void	ft_prt(mlx_texture_t *tex, mlx_image_t **im, float scl, mlx_t *mlx)
{
	int32_t		new_w;
	int32_t		new_h;
	int32_t		i;
	uint32_t	s_x;
	uint32_t	s_y;

	if (!tex || !im || scl <= 0)
		return ;
	new_w = (int32_t)(tex->width * scl);
	new_h = (int32_t)(tex->height * scl);
	if (*im != NULL)
		mlx_delete_image(mlx, *im);
	*im = mlx_new_image(mlx, new_w, new_h);
	if (!*im)
		return ;
	i = 0;
	while (i < new_w * new_h)
	{
		s_x = (i % new_w * tex->width) / new_w;
		s_y = (i / new_w * tex->height) / new_h;
		mlx_put_pixel(*im, i % new_w, i / new_w, pixel_texture(tex, s_x, s_y));
		i++;
	}
}

void	player_init(t_player *player, mlx_t *mlx)
{
	float			scale;
	mlx_image_t		*image;
	mlx_texture_t	*texture;

	scale = 1.5f;
	image = NULL;
	texture = mlx_load_png("./textures/player.png");
	if (!texture)
	{
		mlx_close_window(mlx);
		return ;
	}
	ft_prt(texture, &image, scale, mlx);
	if (!image)
	{
		mlx_close_window(mlx);
		return ;
	}
	player->texture_p = texture;
	player->image_p = image;
	player->scale = scale;
	player->x = 0;
	player->y = 0;
	player->win = false;
	mlx_image_to_window(mlx, image, player->x, player->y);
}
