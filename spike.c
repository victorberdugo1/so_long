/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spike.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:20:07 by victor            #+#    #+#             */
/*   Updated: 2024/10/13 21:24:46 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

double random_double(void)
{
    return (fmod(mlx_get_time(), 1.0));
}

void check_spike_collision(void *param)
{
    t_gdata *gd = (t_gdata *)param;
    int player_x = gd->player->xy_p.x / TILE_SIZE;
    int player_y = gd->player->xy_p.y / TILE_SIZE;

    for (int idx = 0; idx < gd->num_spikes; idx++)
    {
        t_spike *spike = &gd->map->spikes[idx];
        if (player_x == spike->xy_s.x && player_y == spike->xy_s.y)
        {
            ft_printf("Game Over\n");
            exit(EXIT_FAILURE);
        }
    }
}

void draw_spikes(void *param)
{
    t_gdata *gd = (t_gdata *)param;
    for (int i = 0; i < gd->num_spikes; i++)
    {
        mlx_image_to_window(gd->mlx, gd->map->spikes[i].image_s, gd->map->spikes[i].xy_s.x * TILE_SIZE, gd->map->spikes[i].xy_s.y * TILE_SIZE);
    }
}

void spike_init(t_gdata *gd, int x, int y, mlx_t *mlx)
{
    t_spike *spike = &gd->map->spikes[0];
    spike->xy_s.x = x;
    spike->xy_s.y = y;
    spike->scale_s = 1.0f;
    spike->image_s = mlx_new_image(mlx, gd->txt_s->width, gd->txt_s->height);
    if (!spike->image_s){
        exit(EXIT_FAILURE);}
	spike->image_s = mlx_texture_to_image(mlx, gd->txt_s);
}

int init_spikes(t_gdata *gd, int num_spikes)
{
    int x = 0;
    int y = 0;

    gd->map->spikes = malloc((num_spikes)  * sizeof(t_spike));
	gd->num_spikes = num_spikes;
    if (!gd->map->spikes)
        exit(EXIT_FAILURE);
    for (int i = 0; i < num_spikes; i++)
        spike_init(gd, x, y, gd->mlx);
    return (1);
}
