/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:30:41 by victor            #+#    #+#             */
/*   Updated: 2024/10/16 09:04:16 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

bool	is_valid_move(t_map *map, int x, int y, char **visited)
{
	return (x >= 0 && x < map->wdt && y >= 0 && y < map->hgt
		&& (map->grid[y][x] == '0' || map->grid[y][x] == 'E'
		|| map->grid[y][x] == 'C')
		&& !visited[y][x]);
}

bool	dfs(t_map *map, int x, int y, char **visited)
{
	if (map->grid[y][x] == 'E')
		return (true);
	visited[y][x] = 1;
	if (is_valid_move(map, x, y - 1, visited) && dfs(map, x, y - 1, visited))
		return (true);
	if (is_valid_move(map, x, y + 1, visited) && dfs(map, x, y + 1, visited))
		return (true);
	if (is_valid_move(map, x - 1, y, visited) && dfs(map, x - 1, y, visited))
		return (true);
	if (is_valid_move(map, x + 1, y, visited) && dfs(map, x + 1, y, visited))
		return (true);
	return (false);
}

char	**create_visited_array(int height, int width)
{
	char	**visited;
	int		i;

	visited = malloc(sizeof(char *) * height);
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = malloc(sizeof(char) * width);
		if (!visited[i])
		{
			while (i > 0)
			{
				i--;
				free(visited[i]);
			}
			free(visited);
			return (NULL);
		}
		memset(visited[i], 0, width);
		i++;
	}
	return (visited);
}

void	free_visited_array(char **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

bool	path_valid(t_map *map)
{
	char	**visited;
	bool	path_exists;

	visited = create_visited_array(map->hgt, map->wdt);
	if (!visited)
		return (false);
	path_exists = dfs(map, map->player_pos.x, map->player_pos.y, visited);
	free_visited_array(visited, map->hgt);
	if (!path_exists)
		printf("Error\nNo valid path from player to exit.\n");
	return (path_exists);
}
