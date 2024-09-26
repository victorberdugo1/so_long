/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:26:04 by victor            #+#    #+#             */
/*   Updated: 2024/09/26 11:41:33 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	ft_prt(gd->player->texture_p, &gd->player->image_p, fminf(x, y), gd->mlx);
	new_x = (width - gd->player->image_p->width) / 2;
	new_y = (height - gd->player->image_p->height) / 2;
	mlx_image_to_window(gd->mlx, gd->player->image_p, new_x, new_y);
}

void	free_resources(t_gamedata *gamedata)
{
	int			i;
	t_collect	*collect;

	if (gamedata->player->texture_p)
		mlx_delete_texture(gamedata->player->texture_p);
	if (gamedata->player->image_p)
		mlx_delete_image(gamedata->mlx, gamedata->player->image_p);
	if (gamedata->map)
	{
		i = -1;
		while (++i < gamedata->map->height)
			free(gamedata->map->grid[i]);
		free(gamedata->map->grid);
		i = -1;
		while (++i < gamedata->coins)
		{
			collect = &gamedata->map->collects[i];
			if (collect->image_c)
				mlx_delete_image(gamedata->mlx, collect->image_c);
			if (collect->texture_c)
				mlx_delete_texture(collect->texture_c);
		}
		free(gamedata->map->collects);
		free(gamedata->map);
	}
}

void	ft_hook(void *param)
{
	t_gamedata	*gamedata;
	mlx_t		*mlx;
	t_player	*player;
	mlx_image_t	*image;

	gamedata = (t_gamedata *)param;
	mlx = gamedata->mlx;
	player = gamedata->player;
	image = player->image_p;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP) || mlx_is_key_down(mlx, MLX_KEY_W))
		player->y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN) || mlx_is_key_down(mlx, MLX_KEY_S))
		player->y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT) || mlx_is_key_down(mlx, MLX_KEY_A))
		player->x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT) || mlx_is_key_down(mlx, MLX_KEY_D))
		player->x += 5;
	image->instances[0].x = player->x;
	image->instances[0].y = player->y;
}
