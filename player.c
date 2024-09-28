/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:43:15 by victor            #+#    #+#             */
/*   Updated: 2024/09/28 12:47:19 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	prptxt(mlx_texture_t *tex, mlx_image_t **im, float scl, mlx_t *mlx)
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
	prptxt(texture, &image, scale, mlx);
	if (!image)
	{
		mlx_close_window(mlx);
		return ;
	}
	player->texture_p = texture;
	//player->image_p = image;
	player->scale = scale;
	player->x = 0;
	player->y = 0;
	player->win = false;
	//mlx_image_to_window(mlx, image, player->x, player->y);
}
