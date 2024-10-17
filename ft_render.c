/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:29:25 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/17 20:43:16 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* ************************************************************************** */
/* Handles the rendering process of the game. Moves the player, and draws     */
/* the player, collectables, and the map on the screen, ensuring the scale    */
/* is sufficient for rendering.                                               */
/* ************************************************************************** */
void	ft_render(void *param)
{
	t_gdata	*gd;

	gd = (t_gdata *)param;
	if (gd->map->scale < 1)
		return ;
	ft_move(gd->player, gd);
	ft_draw(param);
	ft_draw_collectable(param);
	ft_draw_map(param);
}

/* ************************************************************************** */
/* Handles drawing the player on the screen by calculating the position       */
/* based on the window size and player scale. Then handles memory by scaling  */
/* the player's image and positioning it on the window.                       */
/* ************************************************************************** */
void	ft_draw(void *param)
{
	t_gdata		*gd;
	t_player	*pl;
	t_coord		pos;

	gd = (t_gdata *)param;
	pl = gd->player;
	pos.x = gd->window_width / 2 - (pl->scale * TILE_SIZE) / 2;
	pos.y = gd->window_height / 2 - (pl->scale * TILE_SIZE) / 2;
	scale_image(pl, pl->scale, pos, gd);
}

/* ************************************************************************** */
/* Handles drawing the map to the window by calculating the offsets based on  */
/* the player's position and scale. Updates the position of the map's resized */
/* image instance to render it correctly in the window.                       */
/* ************************************************************************** */
void	ft_draw_map(void *param)
{
	t_gdata	*gd;
	int		x_off;
	int		y_off;

	gd = (t_gdata *)param;
	x_off = (gd->window_width / 2) - (gd->player->xy_p.x * gd->player->scale);
	y_off = (gd->window_height / 2) - (gd->player->xy_p.y * gd->player->scale);
	if (gd->map->resize_m && gd->map->resize_m->count > 0)
	{
		gd->map->resize_m->instances[0].x = x_off;
		gd->map->resize_m->instances[0].y = y_off;
	}
}

/* ************************************************************************** */
/* Handles drawing the collectable items (coins) to the window. Calculates    */
/* the offsets for each collectable based on the player's position and scale, */
/* and updates their position to render them correctly in the window.         */
/* ************************************************************************** */
void	ft_draw_collectable(void *param)
{
	t_gdata		*gd;
	t_collect	*coin;
	int			x_off;
	int			y_off;
	int			idx;

	gd = (t_gdata *)param;
	if (!gd->map->resize_m->instances)
		return ;
	idx = -1;
	while (++idx < gd->coins)
	{
		coin = &gd->map->collects[idx];
		if (!coin->pick)
		{
			x_off = (gd->window_width / 2) - (
					(gd->player->xy_p.x - coin->xy_c.x * TILE_SIZE)
					* gd->player->scale);
			y_off = (gd->window_height / 2) -(
					(gd->player->xy_p.y - coin->xy_c.y * TILE_SIZE)
					* gd->player->scale);
			coin->resize_c->instances[0].x = x_off;
			coin->resize_c->instances[0].y = y_off;
		}
	}
}

/* ************************************************************************** */
/* Redraws the map by processing each tile and updating the graphical         */
/* representation based on the current state of the grid.                     */
/* Then handles memory for the tile images to ensure proper rendering.        */
/* ************************************************************************** */
void	redraw_map(t_map *map, mlx_t *mlx)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->hgt)
	{
		j = -1;
		while (++j < map->wdt)
		{
			if (map->grid[i][j] == 'E')
				process_door_tile(map, mlx, i, j);
		}
	}
	combine_tiles(map);
}
