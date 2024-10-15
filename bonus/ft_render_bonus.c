/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:29:25 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/15 09:51:38 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

bool	can_move_to(int x, int y, t_gdata *gd)
{
	if (x < 0 || x >= gd->map->wdt || y < 0 || y >= gd->map->hgt)
		return (false);
	if (gd->map->grid[y][x] == '1')
		return (false);
	if (gd->map->grid[y][x] == 'E' && gd->map->collect_flag)
	{
		gd->player->move_count += 1;
		ft_printf("Move count: %d\n", gd->player->move_count);
		ft_printf("Success! You've escaped!");
		mlx_close_window(gd->mlx);
		return (false);
	}
	return (true);
}

void	moving_pos(t_player *player, float dist_x, float dist_y)
{
	if (fabsf(dist_x) > fabsf(dist_y))
	{
		if (dist_x > 0)
			player->xy_p.x += fminf(8.0f, dist_x);
		else
			player->xy_p.x -= fminf(8.0f, -dist_x);
	}
	else
	{
		if (dist_y > 0)
			player->xy_p.y += fminf(8.0f, dist_y);
		else
			player->xy_p.y -= fminf(8.0f, -dist_y);
	}
}

void	update_pos(t_player *player, float tgt_x, float tgt_y, t_gdata *gd)
{
	float	dist_x;
	float	dist_y;
	int		target_cell_x;
	int		target_cell_y;

	dist_x = tgt_x - player->xy_p.x;
	dist_y = tgt_y - player->xy_p.y;
	target_cell_x = (int)(tgt_x / TILE_SIZE);
	target_cell_y = (int)(tgt_y / TILE_SIZE);
	if (!can_move_to(target_cell_x, target_cell_y, gd))
	{
		player->moving = false;
		return ;
	}
	if (fabsf(dist_x) < 1 && fabsf(dist_y) < 1)
	{
		player->xy_p.x = tgt_x;
		player->xy_p.y = tgt_y;
		player->moving = false;
		player->move_count += 1;
		ft_printf("Move count: %d\n", player->move_count);
	}
	else
		moving_pos(player, dist_x, dist_y);
}

void	ft_move(t_player *player, t_gdata *gd)
{
	float	target_x;
	float	target_y;

	if (!player->moving)
		return ;
	update_frame(player);
	target_x = (player->dest_p.x * TILE_SIZE) + 32;
	target_y = (player->dest_p.y * TILE_SIZE) + 32;
	update_pos(player, target_x, target_y, gd);
}

void	ft_render(void *param)
{
	t_gdata	*gd;

	gd = (t_gdata *)param;
	ft_move(gd->player, gd);
	ft_draw(param);
	ft_draw_collectable(param);
	ft_draw_map(param);
}
