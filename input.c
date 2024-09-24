/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:26:04 by victor            #+#    #+#             */
/*   Updated: 2024/09/24 10:27:38 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		player->y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		player->y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->x += 5;
	image->instances[0].x = player->x;
	image->instances[0].y = player->y;
}
