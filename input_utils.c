/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:44:01 by victor            #+#    #+#             */
/*   Updated: 2024/10/12 18:48:27 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
/*
void	ft_draw(void *param)
{
	t_gdata		*gd;
	t_player	*pl;
	t_coord		pos;

	gd = (t_gdata *)param;
	pl = gd->player;
	pos.x = gd->window_width / 2 - (pl->scale * TILE_SIZE) / 2;
	pos.y = gd->window_height / 2 - (pl->scale * TILE_SIZE) / 2;


	t_gdata *game = (t_gdata *)param;
    int32_t width = 50;
    int32_t height = 20;
    //uint32_t color = ft_pixel(0, 122, 51, 255);
//uint32_t color = ft_pixel(rand() % 256, rand() % 256, rand() % 256, 255);


    if (game->cover == NULL)
    {
		mlx_delete_image(game->mlx, game->cover);
        game->cover = mlx_new_image(game->mlx, width, height);
        if (!game->cover)
            return;

        // Rellena la nueva imagen de cover con el color de fondo
        for (int32_t j = 0; j < height; j++)
        {
            for (int32_t i = 0; i < width; i++)
            {
                mlx_put_pixel(game->cover, i, j, color);
            }
        }
        //mlx_image_to_window(game->mlx, game->cover, rand() % 250 +  150, 10);

		if (gd->cover != NULL)
		{
			mlx_image_to_window(game->mlx, game->cover, rand() % 250 +  150, 10);
		}
		scale_image(pl, pl->scale, pos, gd);

    }
	//pos.x = pos.y;


}
*/
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

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_gdata			*gd;
	float			x;
	float			y;

	gd = (t_gdata *)param;
	if (!gd || !gd->player)
		return ;
	gd->window_width = width;
	gd->window_height = height;
	bgclean(gd, width, height);
	x = (float)width / (float)gd->map->full_m->width;
	y = (float)height / (float)gd->map->full_m->height;
	gd->map->scale = fmaxf(x, y);
	gd->player->scale = fmaxf(x, y);
	sclmap(&gd->map->full_m, &gd->map->resize_m, fmaxf(x, y), gd);
	scale_image_coins(gd);
	gd->is_msg = false;
}

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
