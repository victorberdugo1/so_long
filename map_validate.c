/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:05:41 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/23 21:11:50 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* ************************************************************************** */
/* Validates the map structure by checking dimensions, characters, wall       */
/* integrity, and the presence of collectibles and player position. Returns   */
/* true if valid, false otherwise, printing specific error messages.          */
/* ************************************************************************** */
bool	validate_map(t_map *map)
{
	int		y;
	int		x;
	int		cnt;

	cnt = 0;
	y = -1;
	while (++y < map->hgt)
	{
		x = -1;
		while (++x < (int)ft_strlen(map->grid[y]))
			if (!validate_ch(map, (int)x, y, &cnt))
				return (false);
	}
	if (!validate_walls(map))
		return (false);
	if (cnt < 1)
		ft_printf("Error\nThe map must contain at least one collectible.\n");
	if (map->player != 1)
		ft_printf("Error\nThe map must contain exactly one player position.\n");
	if (map->exit != 1)
		ft_printf("Error\nThe map must contain exactly one exit.\n");
	return (cnt >= 1 && map->exit == 1 && map->player == 1 && path_valid(map));
}

/* ************************************************************************** */
/* Checks if the character at the specified coordinates is valid according to */
/* the defined valid characters. Updates the collectible and exit counts, and */
/* player position if applicable. Prints error messages for invalid character.*/
/* Returns true if valid, false otherwise.                                    */
/* ************************************************************************** */
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
	}
	else if (ch == 'P')
	{
		map->player++;
		map->player_pos.x = x;
		map->player_pos.y = y;
	}
	return (true);
}

/* ************************************************************************** */
/* Checks if the map is properly enclosed by walls (represented by '1') on    */
/* all sides. Returns true if valid, false otherwise, printing error messages */
/* if the walls are not correctly positioned or if the map is empty.          */
/* ************************************************************************** */
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
		if (map->grid[y][0] != '1' || map->grid[y][map->wdt - 1] != '1')
		{
			ft_printf("Error\nThe map must be closed by walls.\n");
			return (false);
		}
	}
	return (true);
}
