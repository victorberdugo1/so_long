/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 20:17:19 by victor            #+#    #+#             */
/*   Updated: 2024/10/17 20:20:02 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/* ************************************************************************** */
/* Updates the player position based on their destination if they are moving. */
/* It calculates the target position and updates the player's frame.          */
/* ************************************************************************** */
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

/* ************************************************************************** */
/* Updates the player's position towards the target coordinates.              */
/* Checks if the player can move to the target cell; if not, movement stops.  */
/* If the player is close enough to the target, their position is updated.    */
/* The move count is incremented and displayed when the player reaches the    */
/* target position. Otherwise, the player is moved incrementally towards the  */
/* target.                                                                    */
/* ************************************************************************** */
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

/* ************************************************************************** */
/* Moves the player incrementally towards the target position based on the    */
/* distance in both x and y directions. It determines the primary direction   */
/* of movement (x or y) by comparing the absolute distances. The player is    */
/* moved by a maximum of 8 units in the chosen direction, ensuring smooth     */
/* movement towards the target.                                               */
/* ************************************************************************** */
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

/* ************************************************************************** */
/* Checks if the player can move to a specified grid cell based on its        */
/* coordinates. Returns false if the cell is out of bounds or blocked by a    */
/* wall ('1'). If the cell contains an exit ('E') and all collectibles have   */
/* been collected, it updates the move count and closes the window.           */
/* Returns true if the move is valid.                                         */
/* ************************************************************************** */
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
