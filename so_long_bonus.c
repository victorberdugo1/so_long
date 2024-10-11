/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:27 by vberdugo          #+#    #+#             */
/*   Updated: 2024/10/11 15:10:41 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "so_long.h"

/*
void	put_text_move(t_map *map)
{
	char	*move;

	move = ft_itoa(map->move);
	if (map->image.text_move == NULL)
	{
		map->image.text_title = mlx_put_string(map->mlx, "Steps:", 32, 32);
		map->image.text_move = mlx_put_string(map->mlx, move, 96, 32);
		free(move);
		return ;
	}
	if (map->image.text_info != NULL && map->p_state == 1)
	{
		mlx_delete_image(map->mlx, map->image.text_info);
		map->info = NULL;
	}
	mlx_delete_image(map->mlx, map->image.text_move);
	map->image.text_move = mlx_put_string(map->mlx, move, 96, 32);
	free(move);
}
*/

void borrar(void *param)
{
 t_gdata *game = (t_gdata *)param;

//mlx_delete_image(game->mlx, game->cover);
	int32_t width = 50;
    int32_t height = 20;
    uint32_t color = ft_pixel(0, 122, 51, 255);

	if (game->cover != NULL)
	{
		//mlx_delete_image(game->mlx, game->cover);
	}
	game->cover = mlx_new_image(game->mlx, width, height);

    for (int32_t j = 0; j < height; j++)
    {
        for (int32_t i = 0; i < width; i++)
        {
            mlx_put_pixel(game->cover, i, j, color);
        }
    }
    //mlx_image_to_window(game->mlx, game->cover, 150, 10);

}
void draw_game_info(void *param)
{
    t_gdata *game = (t_gdata *)param;
    char *move_count_str;
   	move_count_str = ft_itoa(game->player->move_count);

 	//mlx_put_string(game->mlx, "Move count:", 2, 10);
	//game->msg = mlx_put_string(game->mlx, "Move count:", 2, 10);
	mlx_image_to_window(game->mlx, game->msg , 2, 10);
	
	game->nbr =  mlx_put_string(game->mlx, move_count_str,150, 10);
	mlx_image_to_window(game->mlx, game->nbr , 150, 10);

	free(move_count_str);
}

void move(void *param)
{
	t_gdata *game = (t_gdata *)param;

	ft_move(game->player, game);
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
	gamedata.msg = mlx_put_string(mlx, "Move count:", 2, 10);
	//mlx_image_to_window(mlx, gamedata.msg , 2, 10);

	if (!init_collectables_from_map(&gamedata))
		return (EXIT_FAILURE);
	mlx_resize_hook(gamedata.mlx, resize_hook, &gamedata);
	mlx_key_hook(gamedata.mlx, ft_hook, &gamedata);

	//mlx_loop_hook(gamedata.mlx, borrar, &gamedata);

	//mlx_loop_hook(gamedata.mlx, ft_render, &gamedata);
	//ft_move(&player, &gamedata);a


	mlx_loop_hook(gamedata.mlx, move, &gamedata);


	mlx_loop_hook(gamedata.mlx, ft_draw, &gamedata);


	
	mlx_loop_hook(gamedata.mlx, ft_draw_collectable, &gamedata);
	mlx_loop_hook(gamedata.mlx, ft_draw_map, &gamedata);

	mlx_loop_hook(gamedata.mlx, borrar, &gamedata);
	mlx_loop_hook(gamedata.mlx, draw_game_info, &gamedata);


	mlx_loop(mlx);
	return (free_resources(&gamedata), mlx_terminate(mlx), EXIT_SUCCESS);
}
