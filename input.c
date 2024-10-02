/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 10:26:04 by victor            #+#    #+#             */
/*   Updated: 2024/10/03 00:14:25 by victor           ###   ########.fr       */
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
	gd->window_width = width;
	gd->window_height = height;
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
	//scl_img(&gd->player->image_p[gd->player->current_frame], &gd->player->resize_p, fmaxf(x, y), gd);
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
/*
void	ft_draw(void *param)
{
	t_gamedata	*gd;
	t_player	*pl;

	gd = (t_gamedata *)param;
	pl = gd->player;
	if (pl->resize_p != NULL)
		mlx_delete_image(gd->mlx, pl->resize_p);
	update_frame(pl);
	pl->resize_p = mlx_new_image(gd->mlx, pl->image_p[pl->current_frame]->width,
			pl->image_p[pl->current_frame]->height);
	scl_img(&pl->image_p[pl->current_frame], &pl->resize_p, pl->scale, gd);
	mlx_image_to_window(gd->mlx, pl->resize_p, pl->xy_p.x, pl->xy_p.y);
	if (gd->map->resize_m != NULL)
		mlx_image_to_window(gd->mlx, gd->map->resize_m, 0, 0);
}*/

void collect_pickup(t_gamedata *gd, int collect_index)
{
    t_collect *coin = &gd->map->collects[collect_index];

    if (!coin->pick)  // Solo si aún no ha sido recogida
    {
        coin->pick = true;
        coin->current_frame = 6;  // Iniciar animación de recogida en el frame 6
    }
}

void	update_collect_frame(t_collect *coin)
{
	float	last_frame_time = 0;
	float			current_time;
	float			delta_time;

	current_time = mlx_get_time();
	delta_time = current_time - last_frame_time;
	last_frame_time = current_time;

	coin->frame_timer += delta_time;
	if (coin->frame_timer >= coin->animation_speed)
	{
		coin->frame_timer -= coin->animation_speed;

		if (!coin->pick)
			coin->current_frame = (coin->current_frame + 1) % 8;
		else if (coin->current_frame >= 6 && coin->current_frame < 15)
			coin->current_frame++;
	}
}
/*
void	ft_draw_coll(void *param)
{
	t_gamedata	*gd;
	t_collect	*coin;
	int			idx;

	gd = (t_gamedata *)param;
	idx = 0;

	while (idx < gd->coins)
	{
		coin = &gd->map->collects[idx];

		if (!coin->pick)
		{
			//if (coin->resize_c != NULL)
				//mlx_delete_image(gd->mlx, coin->resize_c);
			update_collect_frame(coin);
			coin->resize_c = mlx_new_image(gd->mlx, coin->image_c[coin->current_frame]->width, coin->image_c[coin->current_frame]->height);
			scl_img(&coin->image_c[coin->current_frame], &coin->resize_c, coin->scale_c, gd);

			mlx_image_to_window(gd->mlx, coin->resize_c, coin->x, coin->y);
		}
		idx++;
	}
}*/
void ft_draw(void *param)
{
    t_gamedata *gd;
    t_player *pl;
    int map_x_offset;
    int map_y_offset;

    gd = (t_gamedata *)param;
    pl = gd->player;

	map_x_offset = (gd->window_width / 2) - ((pl->xy_p.x) + (pl->scale * TILE_SIZE) / 2);
    map_y_offset = (gd->window_height / 2) - ((pl->xy_p.y) + (pl->scale * TILE_SIZE) / 2);

	if (pl->resize_p != NULL)
        mlx_delete_image(gd->mlx, pl->resize_p);

    update_frame(pl);
    pl->resize_p = mlx_new_image(gd->mlx, pl->image_p[pl->current_frame]->width,
                                  pl->image_p[pl->current_frame]->height);
    scl_img(&pl->image_p[pl->current_frame], &pl->resize_p, pl->scale, gd);

    mlx_image_to_window(gd->mlx, pl->resize_p, (gd->window_width / 2) - (pl->resize_p->width / 2),
                        (gd->window_height / 2) - (pl->resize_p->height / 2));

    if (gd->map->resize_m != NULL)
        mlx_image_to_window(gd->mlx, gd->map->resize_m, map_x_offset, map_y_offset);
	//scl_img(&gd->map->full_m, &gd->map->resize_m, pl->scale, gd);


}

void ft_draw_coll(void *param)
{
    t_gamedata *gd;
    t_collect *coin;
    int idx;
    int map_x_offset;
    int map_y_offset;

    gd = (t_gamedata *)param;
    //map_x_offset = (WIDTH / 2) - (gd->player->xy_p.x * gd->player->scale);
    //map_y_offset = (HEIGHT / 2) - (gd->player->xy_p.y * gd->player->scale);
	map_x_offset = (gd->window_width / 2) - ((gd->player->xy_p.x) + (gd->player->scale * TILE_SIZE) / 2);
    map_y_offset = (gd->window_height / 2) - ((gd->player->xy_p.y) + (gd->player->scale * TILE_SIZE) / 2);
    for (idx = 0; idx < gd->coins; idx++)
    {
        coin = &gd->map->collects[idx];
        coin->scale_c = gd->player->scale;

        if (!coin->pick)
        {
            // Borra la imagen anterior de la moneda si existe
            //if (coin->resize_c != NULL)
              //  mlx_delete_image(gd->mlx, coin->resize_c);

            // Actualiza el frame de la moneda
            update_collect_frame(coin);
            coin->resize_c = mlx_new_image(gd->mlx, coin->image_c[coin->current_frame]->width, 
                                             coin->image_c[coin->current_frame]->height);
            scl_img(&coin->image_c[coin->current_frame], &coin->resize_c, coin->scale_c, gd);

            // Recuperar la posición del coleccionable desde collectible_pos
            t_coord collectible_pos = gd->map->collectible_pos[idx];

            // Calcular la posición final teniendo en cuenta el escalado
            int final_x = (collectible_pos.x * coin->scale_c) + map_x_offset;
            int final_y = (collectible_pos.y * coin->scale_c) + map_y_offset;

            // Dibuja la moneda en la ventana
            mlx_image_to_window(gd->mlx, coin->resize_c, final_x, final_y);
        }
    }
}

