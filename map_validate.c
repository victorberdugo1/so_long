/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:05:41 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/09 15:05:58 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
		map->exit_count++;
	else if (ch == 'P')
	{
		map->player_count++;
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
	else if (map->exit_count < 1)
		ft_printf("Error\nThe map must contain at least one exit.\n");
	else if (map->player_count != 1)
		ft_printf("Error\nThe map must contain exactly one player position.\n");
	else
		return (true);
	return (false);
}
