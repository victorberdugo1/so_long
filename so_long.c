/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:27 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/09 17:06:40 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "so_long.h"

int	main(int argc, char **argv)
{
	mlx_t		*mlx;
	t_player	player;
	t_gdata		gamedata;

	if (argc != 2)
		return (ft_printf("Error\nmap_file.ber missing\n"), EXIT_FAILURE);
	gamedata.map = read_map(argv[1]);
	if (!gamedata.map)
		return (ft_printf("Invalid map\n"), EXIT_FAILURE);
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
	mlx_loop_hook(gamedata.mlx, ft_render, &gamedata);
	mlx_loop(mlx);
	return (free_resources(&gamedata), mlx_terminate(mlx), EXIT_SUCCESS);
}
