/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:27 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/16 08:41:56 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	draw_game_move(void *param)
{
	t_gdata		*game;
	static int	cycle_count = 0;

	game = (t_gdata *)param;
	if (game->is_msg)
		return ;
	cycle_count++;
	if (cycle_count >= 2)
	{
		mlx_put_string(game->mlx, "Move count:", 20, 10);
		game->cover = mlx_texture_to_image(game->mlx, game->txt_cover);
		mlx_image_to_window(game->mlx, game->cover, 150, 10);
		mlx_resize_image(game->spike.image_s, TILE_SIZE * game->map->scale,
			TILE_SIZE * game->map->scale);
		mlx_image_to_window(game->mlx, game->spike.image_s,
			game->spike.xy_s.x, game->spike.xy_s.y);
		game->spike.inst++;
		game->is_msg = true;
		cycle_count = 0;
	}
}

void	draw_game_info(void *param)
{
	static int	cycle_count = 0;
	t_gdata		*game;
	char		*move_count_str;

	game = (t_gdata *)param;
	move_count_str = ft_itoa(game->player->move_count);
	cycle_count++;
	if (cycle_count >= 2)
	{
		if (game->nbr != NULL)
			mlx_delete_image(game->mlx, game->nbr);
		game->nbr = mlx_put_string(game->mlx, move_count_str, 150, 10);
		cycle_count = 0;
	}
	free(move_count_str);
}

int	init_game(int argc, char **argv, t_gdata *gamedata, t_player *player)
{
	mlx_t	*mlx;

	if (argc != 2)
		return (ft_printf("Error\nmap_file.ber missing\n"), EXIT_FAILURE);
	gamedata->map = read_map(argv[1]);
	if (!gamedata->map)
		return (ft_printf("Invalid map\n"), EXIT_FAILURE);
	mlx_set_setting(MLX_MAXIMIZED, true);
	mlx = mlx_init(WIDTH, HEIGHT, "so_long", true);
	if (!mlx)
		return (EXIT_FAILURE);
	map_start(gamedata->map, mlx);
	player_init(player, mlx);
	gamedata->mlx = mlx;
	gamedata->player = player;
	if (!init_collectables_from_map(gamedata))
		return (EXIT_FAILURE);
	gamedata->txt_s = mlx_load_png("./textures/spike.png");
	spike_init(gamedata);
	gamedata->txt_cover = mlx_load_png("./textures/cover.png");
	if (!gamedata->txt_cover)
		return (mlx_close_window(mlx), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	game_loop(t_gdata *gamedata)
{
	mlx_key_hook(gamedata->mlx, ft_hook, gamedata);
	mlx_resize_hook(gamedata->mlx, resize_hook, gamedata);
	mlx_loop_hook(gamedata->mlx, ft_render, gamedata);
	mlx_loop_hook(gamedata->mlx, spike_collision, gamedata);
	mlx_loop_hook(gamedata->mlx, draw_game_move, gamedata);
	mlx_loop_hook(gamedata->mlx, draw_game_info, gamedata);
	mlx_loop_hook(gamedata->mlx, move_spike, gamedata);
	mlx_loop(gamedata->mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_player	player;
	t_gdata		gdata;

	if (init_game(argc, argv, &gdata, &player) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	if (game_loop(&gdata) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (free_2(&gdata), free_resources(&gdata), EXIT_SUCCESS);
}
