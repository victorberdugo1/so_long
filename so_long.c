/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:27 by vberdugo          #+#    #+#             */
/*   Updated: 2024/09/24 15:43:51 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "so_long.h"

uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	ft_randomize(void *param)
{
	t_gamedata		*gd;
	uint32_t		i;
	static float	angle;
	uint8_t			yellow;
	uint8_t			color;

	angle += 0.1f;
	i = 0;
	gd = (t_gamedata *)param;
	while (i < gd->player->image_p->width * gd->player->image_p->height)
	{
		yellow = gd->player->image_p->pixels[i * 4 + 2];
		if (yellow >= 30 && yellow <= 90)
		{
			color = (uint8_t)(180 + (75 * (sin(angle) + 1) / 2));
			gd->player->image_p->pixels[i * 4] = color;
			gd->player->image_p->pixels[i * 4 + 1] = color * 0.75;
			gd->player->image_p->pixels[i * 4 + 2] = 70;
		}
		i++;
	}
}

uint32_t	pixel_texture(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	uint32_t	index;
	uint8_t		*pixel;

	index = (y * texture->width + x) * 4;
	pixel = &texture->pixels[index];
	return (ft_pixel(pixel[0], pixel[1], pixel[2], pixel[3]));
}

void	ft_print(mlx_texture_t *tex, mlx_image_t **ima, float scale, mlx_t *mlx)
{
	int32_t		new_w;
	int32_t		new_h;
	int32_t		i;
	uint32_t	s_x;
	uint32_t	s_y;

	if (!tex || !ima || scale <= 0)
		return ;
	new_w = (int32_t)(tex->width * scale);
	new_h = (int32_t)(tex->height * scale);
	if (*ima != NULL)
		mlx_delete_image(mlx, *ima);
	*ima = mlx_new_image(mlx, new_w, new_h);
	if (!*ima)
		return ;
	i = 0;
	while (i < new_w * new_h)
	{
		s_x = (i % new_w * tex->width) / new_w;
		s_y = (i / new_w * tex->height) / new_h;
		mlx_put_pixel(*ima, i % new_w, i / new_w, pixel_texture(tex, s_x, s_y));
		i++;
	}
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_gamedata	*gd;
	float		x;
	float		y;
	int			new_x;
	int			new_y;

	gd = (t_gamedata *)param;
	if (!gd || !gd->player)
		return ;
	x = (float)width / (float)gd->player->texture_p->width;
	y = (float)height / (float)gd->player->texture_p->height;
	ft_print(gd->player->texture_p, &gd->player->image_p, fminf(x, y), gd->mlx);
	new_x = (width - gd->player->image_p->width) / 2;
	new_y = (height - gd->player->image_p->height) / 2;
	mlx_image_to_window(gd->mlx, gd->player->image_p, new_x, new_y);
}

void	player_init(t_player *player, mlx_t *mlx)
{
	float			scale;
	mlx_image_t		*image;
	mlx_texture_t	*texture;

	scale = 1.5f;
	image = NULL;
	texture = mlx_load_png("./textures/coin.png");
	if (!texture)
	{
		mlx_close_window(mlx);
		return ;
	}
	ft_print(texture, &image, scale, mlx);
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

int	main(void)
{
	mlx_t		*mlx;
	t_player	player;
	t_gamedata	gamedata;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		return (EXIT_FAILURE);
	player_init(&player, mlx);
	gamedata.mlx = mlx;
	gamedata.player = &player;
	mlx_resize_hook(gamedata.mlx, resize_hook, &gamedata);
	mlx_loop_hook(gamedata.mlx, ft_hook, &gamedata);
	mlx_loop_hook(gamedata.mlx, ft_randomize, &gamedata);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
