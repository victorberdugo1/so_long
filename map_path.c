/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:30:41 by victor            #+#    #+#             */
/*   Updated: 2024/10/17 14:36:46 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/* ************************************************************************** */
/* Checks if there is a valid path from the player's position to the exit     */
/* using depth-first search (DFS). Returns true if a path exists, false       */
/* otherwise, printing an error message if no valid path is found.            */
/* ************************************************************************** */
bool	path_valid(t_map *map)
{
	char	**visited;
	bool	path_exists;
	int		i;

	visited = create_visited_array(map->hgt, map->wdt);
	if (!visited)
		return (false);
	path_exists = dfs(map, map->player_pos.x, map->player_pos.y, visited);
	i = -1;
	while (++i < map->hgt)
		free(visited[i]);
	free(visited);
	if (!path_exists)
		ft_printf("Error\nNo valid path from player to exit.\n");
	return (path_exists);
}

/* ************************************************************************** */
/* Allocates and initializes a 2D array to track visited positions during     */
/* pathfinding. Each cell is initialized to 0, and the array dimensions are   */
/* determined by the specified height and width. Returns a pointer to the     */
/* allocated array or NULL if memory allocation fails, freeing previously     */
/* allocated rows in case of failure.                                         */
/* ************************************************************************** */
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

/* ************************************************************************** */
/* Performs a depth-first search (DFS) to find a path from the player's       */
/* position to the exit. Marks the current position as visited, checks for    */
/* valid moves in all four directions (up, down, left, right) and recursively */
/* explores those moves. Returns true if a path to the exit is found, or      */
/* false if no valid path exists.                                             */
/* ************************************************************************** */
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

/* ************************************************************************** */
/* Checks if a move to the specified coordinates (x, y) is valid. A move is   */
/* considered valid if it is within the map boundaries lands on an empty tile */
/* an exit or a collectible, and has not been visited before. Returns true    */
/* if the move is valid, or false otherwise.                                  */
/* ************************************************************************** */
bool	is_valid_move(t_map *map, int x, int y, char **visited)
{
	return (x >= 0 && x < map->wdt && y >= 0 && y < map->hgt
		&& (map->grid[y][x] == '0' || map->grid[y][x] == 'E'
		|| map->grid[y][x] == 'C')
		&& !visited[y][x]);
}
