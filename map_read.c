/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:22:38 by victor            #+#    #+#             */
/*   Updated: 2024/10/23 21:12:54 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* ************************************************************************** */
/* Verifies the file has .ber extension, gets map size, initializes and fills */
/* the map, then validates it. Frees resources if validation fails.           */
/* Returns the t_map pointer or NULL if an error occurs.                      */
/* ************************************************************************** */
t_map	*read_map(const char *filename)
{
	int		width;
	int		height;
	t_map	*map;
	int		len;
	int		i;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(&filename[len - 4], ".ber", 4) != 0)
		return (perror("Error\nFile extension must be .ber\nExit"), NULL);
	if (map_size(filename, &width, &height) < 0)
		return (NULL);
	map = init_map(width, height);
	if (!map)
		return (NULL);
	map = fill_map(filename, width, map);
	if (!validate_map(map))
	{
		i = -1;
		while (++i < height)
			if (map->grid[i])
				free(map->grid[i]);
		return (free(map->grid), free(map), NULL);
	}
	return (map);
}

/* ************************************************************************** */
/* Opens the .ber file, reads each line to determine the width and height of  */
/* the map. Ensures all lines have the same width. Returns 0 if successful,   */
/* or -1 on error, printing an error message.                                 */
/* ************************************************************************** */
int	map_size(const char *filename, int *width, int *height)
{
	int		file;
	char	*line;
	int		temp_width;

	*width = -1;
	*height = 0;
	file = open(filename, O_RDONLY);
	if (file < 0)
		return (perror("Error\nOpening the file"), -1);
	line = get_next_line(file);
	while (line != NULL)
	{
		if (*width == -1)
			*width = ft_strlen(line) -1;
		temp_width = ft_strlen(line) -1;
		if (temp_width != *width)
			return (ft_printf("Error\nBad line"), free(line), close(file), -1);
		(*height)++;
		free(line);
		line = get_next_line(file);
	}
	close(file);
	return (0);
}

/* ************************************************************************** */
/* Allocates memory for a t_map structure and initializes its fields,         */
/* including dimensions, player position, and status flags. Also allocates    */
/* memory for the map's grid. Returns a pointer to t_map or NULL if memory    */
/* allocation fails.                                                          */
/* ************************************************************************** */
t_map	*init_map(int width, int height)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
	{
		ft_printf("Error\nFailed to allocate memory for map.\n");
		return (NULL);
	}
	map->wdt = width;
	map->hgt = height;
	map->exit = 0;
	map->player = 0;
	map->valid = true;
	map->closed = false;
	map->collect_flag = false;
	map->grid = allocate_grid(width, height);
	if (!map->grid)
	{
		free(map);
		return (NULL);
	}
	map->player_pos.x = -1;
	map->player_pos.y = -1;
	return (map);
}

/* ************************************************************************** */
/* Allocates memory for a 2D array (grid) based on the specified width and    */
/* height. Returns a pointer to the allocated grid or NULL if memory          */
/* allocation fails, freeing previously allocated rows in case of failure.    */
/* ************************************************************************** */
char	**allocate_grid(int width, int height)
{
	char	**grid;
	int		i;

	grid = malloc(height * sizeof(char *));
	if (!grid)
	{
		ft_printf("Error\nFailed to allocate memory for grid.\n");
		return (NULL);
	}
	i = 0;
	while (i < height)
	{
		grid[i] = malloc(width * sizeof(char));
		if (!grid[i])
		{
			ft_printf("Error\nFailed to allocate memory for grid row.\n");
			while (i > 0)
				free(grid[--i]);
			free(grid);
			return (NULL);
		}
		i++;
	}
	return (grid);
}

/* ************************************************************************** */
/* Reads the map data from the specified file and fills the t_map structure's */
/* grid. It also updates the player's position when 'P' is encountered.       */
/* Returns the pointer to t_map or NULL if an error occurs.                   */
/* ************************************************************************** */
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
		while (++w < width && line[w] != '\0')
		{
			map->grid[h][w] = line[w];
			if (line[w] == 'P')
				map->player_pos = (t_coord){w, h};
		}
		free(line);
		h++;
		line = get_next_line(file);
	}
	close(file);
	return (map);
}
