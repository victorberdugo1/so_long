/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:31:26 by victor            #+#    #+#             */
/*   Updated: 2024/09/29 13:46:14 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	collect_color(t_collect *collect, float angle)
{
	uint32_t	i;
	uint8_t		yellow;
	uint8_t		color;

	i = 0;
	while (i < collect->image_c->width * collect->image_c->height)
	{
		yellow = collect->image_c->pixels[i * 4 + 2];
		if (yellow >= 17 && yellow <= 190)
		{
			color = (uint8_t)(180 + (75 * (sin(angle) + 1) / 2));
			collect->image_c->pixels[i * 4] = color;
			collect->image_c->pixels[i * 4 + 1] = color * 0.75;
			collect->image_c->pixels[i * 4 + 2] = 50;
		}
		i++;
	}
}

void	ft_randomize(void *param)
{
	t_gamedata		*gd;
	static float	angle = 0.0f;
	int				c_idx;
	t_collect		*collect;

	angle += 0.1f;
	gd = (t_gamedata *)param;
	c_idx = 0;
	while (c_idx < gd->coins)
	{
		collect = &gd->map->collects[c_idx];
		if (!collect->pick)
		{
			collect_color(collect, angle);
		}
		c_idx++;
	}
}

void	collect_init(t_collect *coll, int x, int y, mlx_t *mlx)
{
	coll->x = x;
	coll->y = y;
	coll->scale = 1.0f;
	coll->pick = false;
	coll->texture_c = mlx_load_png("textures/coin.png");
	if (!coll->texture_c)
	{
		mlx_close_window(mlx);
		return ;
	}
	//prptxt(&coll->image_c, coll->scale, mlx);
	if (!coll->image_c)
	{
		mlx_delete_texture(coll->texture_c);
		mlx_close_window(mlx);
		return ;
	}
	mlx_image_to_window(mlx, coll->image_c, coll->x, coll->y);
}
