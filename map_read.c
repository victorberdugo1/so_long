/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:22:38 by victor            #+#    #+#             */
/*   Updated: 2024/10/08 13:36:19 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	validate_map(t_map *map)
{
	int		collectible_count;
	int		exit_count;
	int		player_count;
	int		y;
	int		x;
	char	cell;

	collectible_count = 0;
	exit_count = 0;
	player_count = 0;
	y = 0;
	while (y < map->hgt)
	{
		x = 0;
		while (x < map->wdt)
		{
			cell = map->grid[y][x];
			if (cell != '0' && cell != '1' && cell != 'C' && cell != 'E' && cell != 'P' && cell != '\n')
			{
				printf("Error\nInvalid character '%c' in the map at (%d, %d).\n", cell, y, x);
				return (false);
			}
			if (cell == 'C')
				collectible_count++;
			else if (cell == 'E')
				exit_count++;
			else if (cell == 'P')
			{
				player_count++;
				map->player_pos.x = x;
				map->player_pos.y = y;
			}
			x++;
		}
		if ((size_t)ft_strlen(map->grid[y]) != (size_t)map->wdt)
		{
			printf("Error\nThe map is not rectangular.\n");
			return (false);
		}
		y++;
	}
	if (collectible_count < 1)
	{
		printf("Error\nThe map must contain at least one collectible.\n");
		return (false);
	}
	if (exit_count < 1)
	{
		printf("Error\nThe map must contain at least one exit.\n");
		return (false);
	}
	if (player_count != 1)
	{
		printf("Error\nThe map must contain exactly one player position.\n");
		return (false);
	}
	return (true);
}

t_map	*read_map(const char *filename)
{
	int		width;
	int		height;
	t_map	*map;

	if (map_size(filename, &width, &height) < 0)
		return (NULL);
	map = init_map(width, height);
	if (!map)
		return (NULL);
	if (map_size(filename, &width, &height) < 0)
		return (NULL);
	map = fill_map(filename, width, map);
	if (!validate_map(map))
		return (free(map), NULL);
	return (map);
}

int	map_size(const char *filename, int *width, int *height)
{
	int		file;
	char	*line;
	int		temp_width;

	*width = 0;
	*height = 0;
	file = open(filename, O_RDONLY);
	if (file < 0)
		return (-1);
	line = get_next_line(file);
	while (line != NULL)
	{
		if (*width == 0)
			*width = ft_strlen(line);
		temp_width = ft_strlen(line);
		if (temp_width != *width)
			return (free(line), close(file), -1);
		(*height)++;
		free(line);
		line = get_next_line(file);
	}
	close(file);
	return (0);
}

t_map	*fill_map(const char *filename, int width, t_map *map)
{
	int			file;
	int			h;
	int			w;
	char		*line;

	file = open(filename, O_RDONLY);
	if (file < 0)
		return (free(map), NULL);
	h = 0;
	line = get_next_line(file);
	while (line != NULL)
	{
		w = -1;
		while (++w < width)
		{
			map->grid[h][w] = line[w];
			if (line[w] == 'P')
				map->player_pos = (t_coord){w, h};
		}
		free(line);
		h++;
		line = get_next_line(file);
	}
	return (close(file), map);
}

char	**allocate_grid(int width, int height)
{
	char	**grid;
	int		i;

	grid = malloc(height * sizeof(char *));
	if (!grid)
		return (NULL);
	i = 0;
	while (i < height)
	{
		grid[i] = malloc(width * sizeof(char));
		if (!grid[i])
		{
			while (i > 0)
				free(grid[--i]);
			return (free(grid), NULL);
		}
		i++;
	}
	return (grid);
}

t_map	*init_map(int width, int height)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->wdt = width;
	map->hgt = height;
	map->exit_count = 0;
	map->player_count = 0;
	map->valid = true;
	map->closed = false;
	map->grid = allocate_grid(width, height);
	if (!map->grid)
		return (free(map), NULL);
	map->player_pos.x = -1;
	map->player_pos.y = -1;
	return (map);
}
