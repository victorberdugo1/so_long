/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spike_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:20:07 by victor            #+#    #+#             */
/*   Updated: 2024/10/15 15:02:12 by vberdugo         ###   ########.fr       */
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

void	spike_collision(void *param)
{
	t_gdata *gd = (t_gdata *)param;
	int player_x = gd->player->xy_p.x;
	int player_y = gd->player->xy_p.y;
	t_spike *spike = &gd->spike;
	int collision_radius = 32; 
	int player_radius = 32;
	int offset_left_x = 1300;//900;// * gd->map->scale; 
	int offset_left_y = 600;//200;//  *  gd->map->scale;
	int offset_right_x = 1250;//850;// *  gd->map->scale;
	int offset_right_y = 400;//100;//  *  gd->map->scale;
	printf("escala: %f w%d h%d \n",  gd->map->scale,gd->window_width,gd->window_height);

	{
		int adjusted_spike_x = spike->xy_s.x - offset_left_x;
		int adjusted_spike_y = spike->xy_s.y - offset_left_y;
		int delta_x = player_x - adjusted_spike_x;
		int delta_y = player_y - adjusted_spike_y;
		float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
		printf("Left/Up Delta X: %d, Delta Y: %d, Distance: %.2f\n", delta_x, delta_y, distance);
		printf("Collision Threshold (Left/Up): %d\n", (collision_radius + player_radius));
		if (distance < (collision_radius + player_radius))
		{
			printf("Collision detected with Spike! Game Over\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("No Collision detected (Left/Up).\n");
		}
	}
	{
		int adjusted_spike_x = spike->xy_s.x - offset_right_x;
		int adjusted_spike_y = spike->xy_s.y - offset_right_y;
		int delta_x = player_x - adjusted_spike_x;
		int delta_y = player_y - adjusted_spike_y;
		float distance = sqrt(delta_x * delta_x + delta_y * delta_y);
		printf("Right/Down Delta X: %d, Delta Y: %d, Distance: %.2f\n", delta_x, delta_y, distance);
		printf("Collision Threshold (Right/Down): %d\n", (collision_radius + player_radius));
		if (distance < (collision_radius + player_radius))
		{
			printf("Collision detected with Spike! Game Over\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			printf("No Collision detected (Right/Down).\n");
		}
	}
}
