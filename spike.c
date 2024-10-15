/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spike.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:20:07 by victor            #+#    #+#             */
/*   Updated: 2024/10/15 02:21:41 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

double random_double(void)
{
    return (fmod(mlx_get_time(), 1.0));
}

void move_spike(void *param)
{
	t_gdata *gd = (t_gdata *)param;
    if (gd->spike.image_s->instances == NULL)
        return;


    static float angle = 0.0f;
    float radius = 64.0f * gd->map->scale;
    float center_x = (gd->window_width / 2) - (gd->player->xy_p.x * gd->map->scale)
		+ (TILE_SIZE * gd->map->scale) /256 + (gd->map->exit_pos.x * gd->map->scale * TILE_SIZE);
    float center_y = (gd->window_height / 2) - (gd->player->xy_p.y * gd->map->scale)
		+ (TILE_SIZE * gd->map->scale) / 256 + (gd->map->exit_pos.y * gd->map->scale * TILE_SIZE);
    gd->spike.image_s->instances[gd->spike.inst].x = center_x + (int)(radius * cos(angle));
    gd->spike.image_s->instances[gd->spike.inst].y = center_y + (int)(radius * sin(angle));
    angle += 0.1f; 
	if (angle >= 2 * M_PI) // Resetea el ángulo si excede 2*PI
        angle = 0.0f;

	/*/ Calcular la posición central (x_offset y y_offset)
    int x_offset = (gd->window_width / 2) - (gd->player->xy_p.x * gd->map->scale)
                 + (TILE_SIZE * gd->map->scale) 
                 + (gd->map->exit_pos.x * gd->map->scale * TILE_SIZE);
    int y_offset = (gd->window_height / 2) - (gd->player->xy_p.y * gd->map->scale)
                 + (TILE_SIZE * gd->map->scale) 
                 + (gd->map->exit_pos.y * gd->map->scale * TILE_SIZE);
*/
    //int x_off = (int)(cos(angle));
    //int y_off = (int)(sin(angle));

    // Actualizar la posición del spike alrededor del punto central
    //gd->spike.image_s->instances[gd->spike.inst].x = x_offset + x_off;
    //gd->spike.image_s->instances[gd->spike.inst].y = y_offset + y_off;

	gd->spike.xy_s.x = center_x + (int)(radius * cos(angle));
	gd->spike.xy_s.y = center_y + (int)(radius * sin(angle));

}

void spike_init(t_gdata *gd)
{
    t_spike *spike = &gd->spike;
    spike->xy_s.x = 0;
	spike->xy_s.y = 0;
	spike->inst	= -1;
    spike->image_s = mlx_new_image(gd->mlx, gd->txt_s->width, gd->txt_s->height);
    if (!spike->image_s)
	{
        exit(EXIT_FAILURE);
	}
	spike->image_s = mlx_texture_to_image(gd->mlx, gd->txt_s);
}

void spike_collision(void *param)
{
    t_gdata *gd = (t_gdata *)param;
    int player_x = gd->player->xy_p.x;
    int player_y = gd->player->xy_p.y;
    t_spike *spike = &gd->spike;

    printf("Player Position: (%d, %d)\n", player_x, player_y);
    printf("Spike Position: (%d, %d)\n", spike->xy_s.x, spike->xy_s.y);
    printf("Exit Position: (%d, %d)\n", gd->map->exit_pos.x * TILE_SIZE, gd->map->exit_pos.y * TILE_SIZE);

    int collision_radius = 32; 
    int player_radius = 32;

    // Offset para la detección a la izquierda y arriba
    int offset_left_x = 900;  
    int offset_left_y = 200;  

    // Offset para la detección a la derecha y abajo
    int offset_right_x = 850;  
    int offset_right_y = 100;  

    // Verificación para la izquierda y arriba
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

    // Verificación para la derecha y abajo
    {
        int adjusted_spike_x = spike->xy_s.x - offset_right_x;  // Restar el offset
        int adjusted_spike_y = spike->xy_s.y - offset_right_y;  // Restar el offset

        int delta_x = player_x - adjusted_spike_x;  // Resta para delta
        int delta_y = player_y - adjusted_spike_y;  // Resta para delta

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

