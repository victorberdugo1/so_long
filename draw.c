/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:55:39 by vberdugo          #+#    #+#             */
/*   Updated: 2024/09/26 16:28:11 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_map *map, int x, int y, mlx_t *mlx)
{
	map->scale = 2.0f;
	map->texture_m = mlx_load_png("textures/01.png");
	if (!map->texture_m)
	{
		mlx_close_window(mlx);
		return ;
	}
	ft_prt(map->texture_m, &map->image_m, map->scale, mlx);
	if (!map->image_m)
	{
		mlx_delete_texture(map->texture_m);
		mlx_close_window(mlx);
		return ;
	}
	mlx_image_to_window(mlx, map->image_m, x, y);
}
