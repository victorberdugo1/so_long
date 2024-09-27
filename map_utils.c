/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 21:56:07 by victor            #+#    #+#             */
/*   Updated: 2024/09/27 21:57:42 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	all_collected(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->exit_count)
	{
		if (!map->collects[i].pick)
			return (0);
		i++;
	}
	return (1);
}

t_coord	get_border_sprite(t_map *map, int coord_y, int coord_x)
{
	if (coord_y == 0)
	{
		if (coord_x == 0)
			return ((t_coord){0, 0});
		else if (coord_x == map->width - 1)
			return ((t_coord){2, 0});
		else
			return ((t_coord){1, 0});
	}
	else if (coord_y == map->height - 1)
	{
		if (coord_x == 0)
			return ((t_coord){3, 0});
		else if (coord_x == map->width - 1)
			return ((t_coord){1, 1});
		else
			return ((t_coord){0, 1});
	}
	if (coord_x == 0)
		return ((t_coord){2, 1});
	return ((t_coord){3, 1});
}

t_coord	get_inner_sprite(t_map *mp, int y, int x)
{
	if (mp->grid[y][x] == '0' || mp->grid[y][x] == 'P' || mp->grid[y][x] == 'C')
	{
		if ((rand() % 3) == 0)
			return ((t_coord){0, 2});
		else if ((rand() % 3) == 1)
			return ((t_coord){1, 2});
		return ((t_coord){2, 2});
	}
	else if (mp->grid[y][x] == '1')
	{
		if ((rand() % 3) == 0)
			return ((t_coord){3, 2});
		else if ((rand() % 3) == 1)
			return ((t_coord){0, 3});
		return ((t_coord){1, 3});
	}
	else if (mp->grid[y][x] == 'E')
	{
		if (all_collected(mp))
			return ((t_coord){3, 3});
		return ((t_coord){2, 3});
	}
	return ((t_coord){-1, -1});
}
