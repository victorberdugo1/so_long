/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:26:04 by victor            #+#    #+#             */
/*   Updated: 2024/10/13 17:47:28 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_player_destination(t_player *pl, int *offset, int direction)
{
	if (direction == 1)
	{
		pl->dest_p.y -= 1;
		pl->moving = true;
		*offset = 8;
	}
	else if (direction == 2)
	{
		pl->dest_p.y += 1;
		pl->moving = true;
		*offset = 0;
	}
	else if (direction == 3)
	{
		pl->dest_p.x -= 1;
		pl->moving = true;
		*offset = 4;
	}
	else if (direction == 4)
	{
		pl->dest_p.x += 1;
		pl->moving = true;
		*offset = 12;
	}
}

void	player_movement(t_player *pl, mlx_key_data_t keydata, int *offset)
{
	int	direction;

	direction = 0;
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
		direction = 1;
	else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
		direction = 2;
	else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
		direction = 3;
	else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
		direction = 4;
	if (direction && !pl->moving)
		set_player_destination(pl, offset, direction);
}

void	update_player_frame(t_player *pl, int offset)
{
	if (offset >= 0)
	{
		pl->current_frame = (pl->current_frame + 1) % 4 + offset;
	}
}

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_gdata		*gd;
	t_player	*player;
	int			frame_offset;

	gd = (t_gdata *)param;
	player = gd->player;
	frame_offset = -1;
	if (mlx_is_key_down(gd->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(gd->mlx);
	if (!player->moving)
	{
		player->dest_p.x = (int)(player->xy_p.x / TILE_SIZE);
		player->dest_p.y = (int)(player->xy_p.y / TILE_SIZE);
	}
	player_movement(player, keydata, &frame_offset);
	update_player_frame(player, frame_offset);
	collect_pickup(gd);
}
