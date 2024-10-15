/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spike_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:20:07 by victor            #+#    #+#             */
/*   Updated: 2024/10/15 21:56:53 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	move_spike(void *param)
{
	t_gdata			*gd;
	static float	angle = 0.0f;
	float			radius;
	float			center_x;
	float			center_y;

	gd = (t_gdata *)param;
	if (gd->spike.image_s->instances == NULL)
		return ;
	radius = 64.0f * gd->map->scale;
	center_x = (gd->window_width / 2) - (gd->player->xy_p.x * gd->map->scale)
		+ (TILE_SIZE * gd->map->scale) / 256
		+ (gd->map->exit_pos.x * gd->map->scale * TILE_SIZE);
	center_y = (gd->window_height / 2) - (gd->player->xy_p.y * gd->map->scale)
		+ (TILE_SIZE * gd->map->scale) / 256
		+ (gd->map->exit_pos.y * gd->map->scale * TILE_SIZE);
	gd->spike.image_s->instances[gd->spike.inst].x = center_x
		+ (int)(radius * cos(angle));
	gd->spike.image_s->instances[gd->spike.inst].y = center_y
		+ (int)(radius * sin(angle));
	angle += 0.1f;
	if (angle >= 2 * M_PI)
		angle = 0.0f;
	gd->spike.xy_s.x = center_x + (int)(radius * cos(angle));
	gd->spike.xy_s.y = center_y + (int)(radius * sin(angle));
}

void	spike_init(t_gdata *gd)
{
	t_spike	*spike;

	spike = &gd->spike;
	spike->xy_s.x = 0;
	spike->xy_s.y = 0;
	spike->inst = -1;
	spike->image_s = mlx_new_image(gd->mlx,
			gd->txt_s->width, gd->txt_s->height);
	if (!spike->image_s)
	{
		exit(EXIT_FAILURE);
	}
	spike->image_s = mlx_texture_to_image(gd->mlx, gd->txt_s);
}

void	calculate_spike_pos(t_gdata *gd, float angle, t_coord *spike_pos)
{
	float	radius;

	radius = 64.0f * gd->map->scale;
	spike_pos->x = (gd->window_width / 2)
		- (gd->player->xy_p.x * gd->map->scale)
		+ (TILE_SIZE * gd->map->scale) / 2
		+ (gd->map->exit_pos.x * gd->map->scale * TILE_SIZE)
		+ (int)(radius * cos(angle));
	spike_pos->y = (gd->window_height / 2)
		- (gd->player->xy_p.y * gd->map->scale)
		+ (TILE_SIZE * gd->map->scale) / 2
		+ (gd->map->exit_pos.y * gd->map->scale * TILE_SIZE)
		+ (int)(radius * sin(angle));
}

void	spike_collision(void *param)
{
	t_gdata			*gd;
	static float	angle = 0.0f;
	t_coord			spike_pos;
	int				delta_x;
	int				delta_y;

	gd = (t_gdata *)param;
	if (gd->spike.image_s->instances == NULL)
		return ;
	calculate_spike_pos(gd, angle, &spike_pos);
	delta_x = spike_pos.x - (gd->window_width / 2);
	delta_y = spike_pos.y - (gd->window_height / 2);
	if (sqrt(delta_x * delta_x + delta_y * delta_y) < (8 * gd->map->scale))
	{
		ft_printf("Ouch! The spike got you!\n Game Over.\n");
		exit(EXIT_FAILURE);
	}
	angle += 0.1f;
	if (angle >= 2 * M_PI)
		angle = 0.0f;
}
