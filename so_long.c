/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:27 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/02 22:40:04 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "so_long.h"

int	count_collectables(t_map *map)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < map->hgt)
	{
		x = 0;
		while (x < map->wdt)
		{
			if (map->grid[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

void	init_collectables(t_gamedata *gd)
{
	int	x;
	int	y;
	int	idx;

	idx = 0;
	y = 0;
	gd->map->collectible_pos = malloc(gd->coins  * sizeof(t_coord));
    if (!gd->map->collectible_pos)
    {
       exit(EXIT_FAILURE);// Error en la asignación de memoria
    }

	while (y < gd->map->hgt)
	{
		x = 0;
		while (x < gd->map->wdt)
		{
			if (gd->map->grid[y][x] == 'C')
			{
				collect_init(&gd->map->collects[idx], x, y, gd->mlx);
				gd->map->collectible_pos[idx].x = x;
				gd->map->collectible_pos[idx].y = y;
				idx++;
			}
			x++;
		}
		y++;
	}
}

int	init_collectables_from_map(t_gamedata *gamedata)
{
gamedata->player->xy_p.x = gamedata->map->player_pos.x;
gamedata->player->xy_p.y = gamedata->map->player_pos.y;
	gamedata->coins = count_collectables(gamedata->map);
	gamedata->map->collects = malloc(sizeof(t_collect) * gamedata->coins);
	if (!gamedata->map->collects)
	{
		ft_printf("Error\nFailed to allocate memory for collectables\n");
		return (0);
	}
	init_collectables(gamedata);
	return (1);
}

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_player	player;
	t_gamedata	gamedata;

	if (argc != 2)
		return (ft_printf("Error\nmap_file.ber missing\n"), EXIT_FAILURE);
	gamedata.map = read_map(argv[1]);
	if (!gamedata.map)
		return (ft_printf("Error\nInvalid map\n"), EXIT_FAILURE);
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		return (EXIT_FAILURE);
	draw_map(gamedata.map, mlx);
	player_init(&player, mlx);
	gamedata.mlx = mlx;
	gamedata.player = &player;
	if (!init_collectables_from_map(&gamedata))
		return (EXIT_FAILURE);
	mlx_resize_hook(gamedata.mlx, resize_hook, &gamedata);
	mlx_key_hook(gamedata.mlx, ft_hook, &gamedata);
	mlx_loop_hook(gamedata.mlx, ft_randomize, &gamedata);
	mlx_loop_hook(gamedata.mlx, ft_draw, &gamedata);
	mlx_loop_hook(gamedata.mlx, ft_draw_coll, &gamedata);
	mlx_loop(mlx);
	return (free_resources(&gamedata), mlx_terminate(mlx), EXIT_SUCCESS);
}
