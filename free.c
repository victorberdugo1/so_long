/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 07:50:05 by victor            #+#    #+#             */
/*   Updated: 2024/10/03 20:18:38 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void free_player(t_player *player, t_gamedata *gd)
{
    int i;

    if (player->image_p)
    {
        i = 0;
        while (i < player->total_frames)
        {
            if (player->image_p[i])
                mlx_delete_image(gd->mlx, player->image_p[i]);
            i++;
        }
        free(player->image_p);
        player->image_p = NULL;
    }

    if (player->resize_p)
    {
        mlx_delete_image(gd->mlx, player->resize_p);
        player->resize_p = NULL;
    }

    if (player->texture_p)
    {
        mlx_delete_texture(player->texture_p);
        player->texture_p = NULL;
    }
}

void free_collects(t_collect *collects, int coin_count, t_gamedata *gd)
{
    int i;

    i = 0;
    while (i < coin_count)
    {
        if (collects[i].image_c != NULL)
        {
            mlx_delete_image(gd->mlx, collects[i].image_c);
            collects[i].image_c = NULL;
        }
        if (collects[i].resize_c != NULL)
        {
            mlx_delete_image(gd->mlx, collects[i].resize_c);
            collects[i].resize_c = NULL;
        }
        if (collects[i].texture_c != NULL)
        {
            mlx_delete_texture(collects[i].texture_c);
            collects[i].texture_c = NULL;
        }
        i++;
    }
    free(collects);
    collects = NULL;
}

void free_map(t_map *map, t_gamedata *gd)
{
    int i;

    if (map->full_m)
    {
        mlx_delete_image(gd->mlx, map->full_m);
        map->full_m = NULL;
    }

    if (map->resize_m)
    {
        mlx_delete_image(gd->mlx, map->resize_m);
        map->resize_m = NULL;
    }

    if (map->tiles)
    {
        i = 0;
        while (i < map->wdt * map->hgt)
        {
            if (map->tiles[i])
                mlx_delete_image(gd->mlx, map->tiles[i]);
            i++;
        }
        free(map->tiles);
        map->tiles = NULL;
    }

    if (map->texture_m)
    {
        mlx_delete_texture(map->texture_m);
        map->texture_m = NULL;
    }

    i = 0;
    while (i < map->hgt)
    {
        free(map->grid[i]);
        map->grid[i] = NULL;
        i++;
    }
    free(map->grid);
    map->grid = NULL;

    if (map->collectible_pos)
    {
        free(map->collectible_pos);
        map->collectible_pos = NULL;
    }

    if (map->collects)
        free_collects(map->collects, gd->coins, gd);
}

void free_resources(t_gamedata *gamedata)
{
    if (gamedata->player)
    {
        free_player(gamedata->player, gamedata);
        gamedata->player = NULL;
    }
    if (gamedata->map)
    {
        free_map(gamedata->map, gamedata);
        free(gamedata->map);
        gamedata->map = NULL;
    }
}
