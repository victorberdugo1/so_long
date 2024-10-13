/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:05:41 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/13 14:32:27 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_coord	get_border_sprite(t_map *map, int coord_y, int coord_x)
{
	if (coord_y == 0)
	{
		if (coord_x == 0)
			return ((t_coord){0, 0});
		else if (coord_x == map->wdt - 1)
			return ((t_coord){2, 0});
		else
			return ((t_coord){1, 0});
	}
	else if (coord_y == map->hgt - 1)
	{
		if (coord_x == 0)
			return ((t_coord){3, 0});
		else if (coord_x == map->wdt - 1)
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
		return ((t_coord){2, 3});
	}
	return ((t_coord){-1, -1});
}

bool	validate(t_map *map, int x, int y, int *cnt)
{
	const char	*valid_chars = "01CE\nP";
	char		ch;

	ch = map->grid[y][x];
	if (!ft_strchr(valid_chars, ch))
	{
		ft_printf("Error\nInvalid character '%c' in the map.\n", ch);
		return (false);
	}
	if (ch == 'C')
		(*cnt)++;
	else if (ch == 'E')
		map->exit++;
	else if (ch == 'P')
	{
		map->player++;
		map->player_pos.x = x;
		map->player_pos.y = y;
	}
	return (true);
}

bool	validate_map(t_map *map)
{
	int	y;
	int	x;
	int	cnt;

	cnt = 0;
	y = -1;
	while (++y < map->hgt)
	{
		x = -1;
		while (++x < map->wdt)
			if (!validate(map, x, y, &cnt))
				return (false);
		if ((size_t)ft_strlen(map->grid[y]) != (size_t)map->wdt)
			return (ft_printf("Error\nThe map is not rectangular.\n"), false);
	}
	if (cnt < 1)
		ft_printf("Error\nThe map must contain at least one collectible.\n");
	else if (map->exit < 1)
		ft_printf("Error\nThe map must contain at least one exit.\n");
	else if (map->player != 1)
		ft_printf("Error\nThe map must contain exactly one player position.\n");
	return (cnt >= 1 && map->exit >= 1 && map->player == 1 && path_valid(map));
}
