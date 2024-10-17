/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:05:41 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/17 02:25:32 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

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

bool	validate_ch(t_map *map, int x, int y, int *cnt)
{
	const char	*valid_chars = "01CE\nP";
	char		ch;

	ch = map->grid[y][x];
	if (!ft_strchr(valid_chars, ch))
		return (ft_printf("Error\nInvalid character '%c'.\n", ch), false);
	if (ch == 'C')
		(*cnt)++;
	else if (ch == 'E')
	{
		map->exit++;
		map->exit_pos.x = x;
		map->exit_pos.y = y;
		if (map->exit > 1)
			ft_printf("Error\nThe map must contain exactly one exit.\n");
	}
	else if (ch == 'P')
	{
		map->player++;
		map->player_pos.x = x;
		map->player_pos.y = y;
	}
	return (true);
}

bool	validate_walls(t_map *map)
{
	int	y;
	int	x;

	if (map->hgt == 0 || map->wdt == 0)
		return (ft_printf("Error\nThe map cannot be empty.\n"), false);
	x = -1;
	while (++x < map->wdt - 1)
	{
		if (map->grid[0][x] != '1' || map->grid[map->hgt - 1][x] != '1')
		{
			ft_printf("Error\nThe map must be closed by walls.\n");
			return (false);
		}
	}
	y = -1;
	while (++y < map->hgt)
	{
		if (map->grid[y][0] != '1' || map->grid[y][map->wdt - 2] != '1')
		{
			ft_printf("Error\nThe map must be closed by walls.\n");
			return (false);
		}
	}
	return (true);
}

bool	validate_map(t_map *map)
{
	int		y;
	size_t	x;
	int		cnt;
	size_t	row_length;

	cnt = 0;
	y = -1;
	while (++y < map->hgt)
	{
		row_length = ft_strlen(map->grid[y]);
		if (row_length != (size_t)map->wdt)
			return (ft_printf("Error\nNot rectangular map.\n"), false);
		x = -1;
		while (++x < row_length)
			if (!validate_ch(map, (int)x, y, &cnt))
				return (false);
	}
	if (!validate_walls(map))
		return (false);
	if (cnt < 1)
		ft_printf("Error\nThe map must contain at least one collectible.\n");
	if (map->player != 1)
		ft_printf("Error\nThe map must contain exactly one player position.\n");
	return (cnt >= 1 && map->exit == 1 && map->player == 1 && path_valid(map));
}
