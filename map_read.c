/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:22:38 by victor            #+#    #+#             */
/*   Updated: 2024/10/16 18:41:05 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_map	*read_map(const char *filename)
{
	int		width;
	int		height;
	t_map	*map;
	int		len;
	int	i;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(&filename[len - 4], ".ber", 4) != 0)
	{
		perror("Error\nFile extension must be .ber");
		return (NULL);
	}
	if (map_size(filename, &width, &height) < 0)
		return (NULL);
	map = init_map(width, height);
	if (!map)
		return (NULL);
	map = fill_map(filename, width, map);
	i = -1;
	if (!validate_map(map)){
	while (++i < map->hgt){
		if (map->grid[i])
			free(map->grid[i]);}
		return (free(map), NULL);}
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
		return (perror("Error\nFile"), -1);
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
	if (line)
		free(line);
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
		return (perror("Error\nFile"), free(map), NULL);
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
	if (line)
		free(line);
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
	map->exit = 0;
	map->player = 0;
	map->valid = true;
	map->closed = false;
	map->collect_flag = false;
	map->grid = allocate_grid(width, height);
	if (!map->grid)
		return (free(map), NULL);
	map->player_pos.x = -1;
	map->player_pos.y = -1;
	return (map);
}
