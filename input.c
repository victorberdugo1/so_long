/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:26:04 by victor            #+#    #+#             */
/*   Updated: 2024/10/01 07:50:58 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	scl_img(mlx_image_t **im, mlx_image_t **siz, float scl, t_gamedata *gd)
{
	int32_t		new_w;
	int32_t		new_h;
	int32_t		x;
	int32_t		y;
	uint32_t	src_x;
	uint32_t	src_y;
	uint32_t	pixel;

	if (!im || !*im || scl <= 0)
		return ;
	new_w = (int32_t)((*im)->width * scl);
	new_h = (int32_t)((*im)->height * scl);
	if (siz != NULL)
		mlx_delete_image(gd->mlx, *siz);
	*siz = mlx_new_image(gd->mlx, new_w, new_h);
	if (!*siz)
		return ;
	y = -1;
	while (++y < new_h)
	{
		x = -1;
		while (++x < new_w)
		{
			src_x = (x * (*im)->width) / new_w;
			src_y = (y * (*im)->height) / new_h;
			pixel = get_pixel((*im)->pixels, src_x, src_y, (*im)->width);
			pixel = convert_pixel(pixel);
			mlx_put_pixel(*siz, x, y, pixel);
		}
	}
}

void	resize_hook(int32_t width, int32_t height, void *param)
{
	t_gamedata			*gd;
	float				x;
	float				y;
	int32_t				j;
	int32_t				i;
	static mlx_image_t	*bg_image = NULL;
	uint32_t			color;

	color = ft_pixel(0, 122, 51, 255);
	gd = (t_gamedata *)param;
	if (!gd || !gd->player)
		return ;
	if (bg_image != NULL)
		mlx_delete_image(gd->mlx, bg_image);
	bg_image = mlx_new_image(gd->mlx, width, height);
	j = -1;
	while (++j < height)
	{
		i = -1;
		while (++i < width)
			mlx_put_pixel(bg_image, i, j, color);
	}
	mlx_image_to_window(gd->mlx, bg_image, 0, 0);
	x = (float)width / (float)gd->map->full_m->width;
	y = (float)height / (float)gd->map->full_m->height;
	gd->map->scale = fmaxf(x, y);
	gd->player->scale = fmaxf(x, y);
	scl_img(&gd->map->full_m, &gd->map->resize_m, fmaxf(x, y), gd);
	scl_img(&gd->player->image_p[gd->player->current_frame], &gd->player->resize_p, fmaxf(x, y), gd);
}

void	update_frame(t_player *player)
{
	static float	last_frame_time = 0;
	float			current_time;
	float			delta_time;

	current_time = mlx_get_time();
	delta_time = current_time - last_frame_time;
	last_frame_time = current_time;
	player->frame_timer += delta_time;
	if (player->frame_timer >= player->animation_speed)
	{
		player->frame_timer -= player->animation_speed;
		if (player->current_frame >= 0 && player->current_frame <= 3)
			player->current_frame = (player->current_frame + 1) % 4;
		else if (player->current_frame >= 8 && player->current_frame <= 11)
			player->current_frame = (player->current_frame + 1) % 4 + 8;
		else if (player->current_frame >= 4 && player->current_frame <= 7)
			player->current_frame = (player->current_frame + 1) % 4 + 4;
		else if (player->current_frame >= 12 && player->current_frame <= 15)
			player->current_frame = (player->current_frame + 1) % 4 + 12;
	}
}

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_gamedata	*gd;
	t_player	*player;
	float		move_speed;
	int			frame_offset;

	gd = (t_gamedata *)param;
	player = gd->player;
	move_speed = 50.0f / gd->map->scale;
	if (mlx_is_key_down(gd->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(gd->mlx);
	frame_offset = -1;
	if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
	{
		player->xy_p.y -= move_speed;
		frame_offset = 8;
	}
	else if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
	{
		player->xy_p.y += move_speed;
		frame_offset = 0;
	}
	else if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
	{
		player->xy_p.x -= move_speed;
		frame_offset = 4;
	}
	else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
	{
		player->xy_p.x += move_speed;
		frame_offset = 12;
	}
	if (frame_offset >= 0)
	{
		player->current_frame = (player->current_frame + 1) % 4 + frame_offset;
	}
}

void	ft_draw(void *param)
{
	t_gamedata	*gd;
	t_player	*player;


	gd = (t_gamedata *)param;

	player = gd->player;
	if (player->resize_p != NULL)
		mlx_delete_image(gd->mlx, player->resize_p);
	update_frame(player);
	player->resize_p = mlx_new_image(gd->mlx, player->image_p[player->current_frame]->width, player->image_p[player->current_frame]->height);
	scl_img(&player->image_p[player->current_frame], &player->resize_p, player->scale, gd);
	mlx_image_to_window(gd->mlx, player->resize_p, player->xy_p.x, player->xy_p.y);

	if (gd->map->resize_m != NULL)
		mlx_image_to_window(gd->mlx, gd->map->resize_m, 0, 0);

}

void ft_draw_coll(void *param)
{
    t_gamedata *gad;
    t_collect *collect;
    int tile_idx = 0;

    gad = (t_gamedata *)param;
    collect = &gad->map->collects[0];

    //if (collect->resize_c != NULL)
    //    mlx_delete_image(gad->mlx, collect->resize_c);  // Liberar imagen anterior

    collect->resize_c = mlx_new_image(gad->mlx, collect->image_c[tile_idx]->width, collect->image_c[tile_idx]->height);
    scl_img(&collect->image_c[tile_idx], &collect->resize_c, collect->scale_c, gad);

    if (collect->resize_c != NULL)
        mlx_image_to_window(gad->mlx, collect->resize_c, collect->x, collect->y);
}

