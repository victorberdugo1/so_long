/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:27 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/12 19:14:13 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "so_long.h"

mlx_texture_t *cover_texture;
mlx_image_t *cover_image;

void draw_game_move(void *param)
{
    t_gdata *game = (t_gdata *)param;
	static int cycle_count = 0;

    if (game->is_msg)
		return;
    cycle_count++;
	if (cycle_count >= 2)
	{
		mlx_put_string(game->mlx, "Move count:", 20, 10);
		cover_image = mlx_texture_to_image(game->mlx, cover_texture);
		mlx_image_to_window(game->mlx, cover_image, 150, 10);
		game->is_msg = true;
		cycle_count = 0;
	}
}

void draw_game_info(void *param)
{
	static int cycle_count = 0;
	t_gdata *game = (t_gdata *)param;
	char *move_count_str;

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
	mlx = mlx_init(WIDTH, HEIGHT, "so_long", true);
	if (!mlx)
		return (EXIT_FAILURE);
	map_start(gamedata.map, mlx);
	player_init(&player, mlx);
	gamedata.mlx = mlx;
	gamedata.player = &player;
	gamedata.cover = NULL;
	if (!init_collectables_from_map(&gamedata))
		return (EXIT_FAILURE);
	mlx_key_hook(gamedata.mlx, ft_hook, &gamedata);
    cover_texture = mlx_load_png("./textures/cover.png");
    if (!cover_texture)
    {
        mlx_close_window(mlx);
        return 0; 
    }
    cover_image = mlx_texture_to_image(mlx, cover_texture);
    if (!cover_image)
    {
        mlx_delete_texture(cover_texture);
        mlx_close_window(mlx);
        return 0;
    }
	
	mlx_resize_hook(gamedata.mlx, resize_hook, &gamedata);

	mlx_loop_hook(gamedata.mlx, ft_render, &gamedata);

	mlx_loop_hook(gamedata.mlx, draw_game_move, &gamedata);
	
	mlx_loop_hook(gamedata.mlx, draw_game_info, &gamedata);
	
	mlx_loop(mlx);
	return (free_resources(&gamedata), mlx_terminate(mlx), EXIT_SUCCESS);
}
