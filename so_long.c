/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:27 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/16 18:29:43 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	{
//free_resources(&gamedata);
		//free(
		return (ft_printf("Invalid map\n"), EXIT_FAILURE);
	}
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx = mlx_init(WIDTH, HEIGHT, "so_long", true);
	if (!mlx)
		return (EXIT_FAILURE);
	map_start(gamedata.map, mlx);
	player_init(&player, mlx);
	gamedata.mlx = mlx;
	gamedata.player = &player;
	if (!init_collectables_from_map(&gamedata))
		return (EXIT_FAILURE);
	mlx_resize_hook(gamedata.mlx, resize_hook, &gamedata);
	mlx_key_hook(gamedata.mlx, ft_hook, &gamedata);
	mlx_loop_hook(gamedata.mlx, ft_render, &gamedata);
	mlx_loop(mlx);
	return (free_resources(&gamedata), EXIT_SUCCESS);
}
