/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:31:26 by victor            #+#    #+#             */
/*   Updated: 2024/09/30 21:10:54 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	collect_color(t_collect *collect, float angle)
{
	uint32_t	i;
	uint8_t		yellow;
	uint8_t		color;
	int			tile_idx;

	tile_idx = 0;
	while (collect->image_c[tile_idx] != NULL) // Iterar sobre los tiles.
	{
		i = 0;
		while (i < collect->image_c[tile_idx]->width * collect->image_c[tile_idx]->height)
		{
			yellow = collect->image_c[tile_idx]->pixels[i * 4 + 2]; // Canal azul (B).
			if (yellow >= 16 && yellow <= 190)
			{
				color = (uint8_t)(180 + (75 * (sin(angle) + 1) / 2));
				collect->image_c[tile_idx]->pixels[i * 4] = color;       // R.
				collect->image_c[tile_idx]->pixels[i * 4 + 1] = color * 0.75; // G.
				collect->image_c[tile_idx]->pixels[i * 4 + 2] = 50;      // B.
			}
			i++;
		}
		tile_idx++;
	}
}

void	ft_randomize(void *param)
{
	t_gamedata		*gd;
	static float	angle = 0.0f;
	int				c_idx;
	t_collect		*collect;

	angle += 0.1f;
	gd = (t_gamedata *)param;
	c_idx = 0;
	while (c_idx < gd->coins)
	{
		collect = &gd->map->collects[c_idx];
		if (!collect->pick)
		{
			collect_color(collect, angle);
		}
		c_idx++;
	}
}

// Función para copiar una porción de la textura a una subimagen.
void	copy_text_c(mlx_image_t *subimage, mlx_texture_t *texture, int x_offset, int y_offset)
{
	int			x, y;
	uint32_t	pxl;
	uint32_t	src_x;
	uint32_t	src_y;

	for (y = 0; y < TILE_SIZE; y++)
	{
		for (x = 0; x < TILE_SIZE; x++)
		{
			src_x = x_offset + x; 
			src_y = y_offset + y;
			if (src_x < texture->width && src_y < texture->height)
			{
				pxl = get_pixel(texture->pixels, src_x, src_y, texture->width);
				pxl = convert_pixel(pxl);  // Si es necesario convertir el formato de píxel.
				mlx_put_pixel(subimage, x, y, pxl);
			}
		}
	}
}

void	collect_init(t_collect *coll, int x, int y, mlx_t *mlx)
{
	int tiles_x;
	int tiles_y;
	int tile_idx;
	int tx, ty;

	// Inicialización de las coordenadas.
	coll->x = x;
	coll->y = y;
	coll->scale_c = 1.0f;
	coll->pick = false;

	// Cargar la textura del colectable (moneda).
	coll->texture_c = mlx_load_png("textures/coin.png");
	if (!coll->texture_c)
	{
		mlx_close_window(mlx);  // Cerrar la ventana si no se pudo cargar la textura.
		return ;
	}

	// Calcular cuántos tiles horizontales y verticales tiene la textura.
	tiles_x = coll->texture_c->width / TILE_SIZE;
	tiles_y = coll->texture_c->height / TILE_SIZE;

	// Asignar memoria para las imágenes de los tiles, incluyendo uno adicional para NULL al final.
	coll->image_c = malloc(sizeof(mlx_image_t *) * (tiles_x * tiles_y + 1));
	if (!coll->image_c)
	{
		mlx_delete_texture(coll->texture_c);  // Liberar la textura si falla la asignación de memoria.
		mlx_close_window(mlx);
		return ;
	}

	// Inicializar todas las sub-imágenes a NULL antes de procesarlas.
	for (int i = 0; i < tiles_x * tiles_y; i++)
		coll->image_c[i] = NULL;

	// Iterar sobre los tiles de la textura para dividirla en sub-imágenes.
	tile_idx = 0;
	for (ty = 0; ty < tiles_y; ty++)  // Iterar filas.
	{
		for (tx = 0; tx < tiles_x; tx++)  // Iterar columnas.
		{
			// Crear una nueva sub-imagen de tamaño TILE_SIZE x TILE_SIZE.
			coll->image_c[tile_idx] = mlx_new_image(mlx, TILE_SIZE, TILE_SIZE);
			if (!coll->image_c[tile_idx])
			{
				// Liberar recursos si falla la creación de una imagen.
				for (int i = 0; i < tile_idx; i++)
					mlx_delete_image(mlx, coll->image_c[i]);
				free(coll->image_c);
				mlx_delete_texture(coll->texture_c);
				mlx_close_window(mlx);
				return ;
			}

			// Copiar el contenido de la textura en la sub-imagen correspondiente (tile).
			copy_text_c(coll->image_c[tile_idx], coll->texture_c, tx * TILE_SIZE, ty * TILE_SIZE);

			tile_idx++;  // Incrementar el índice de tile.
		}
	}

	// Asegurarse de que el último elemento del array sea NULL para marcar el fin.
	coll->image_c[tile_idx] = NULL;

	// Mostrar el primer tile (como prueba) en la ventana en las coordenadas iniciales.
	//mlx_image_to_window(mlx, coll->image_c[0], coll->x, coll->y);
}

/*
void	collect_color(t_collect *collect, float angle)
{
	uint32_t	i;
	uint8_t		yellow;
	uint8_t		color;

	i = 0;
	while (i < collect->image_c->width * collect->image_c->height)
	{
		yellow = collect->image_c->pixels[i * 4 + 2];
		if (yellow >= 17 && yellow <= 190)
		{
			color = (uint8_t)(180 + (75 * (sin(angle) + 1) / 2));
			collect->image_c->pixels[i * 4] = color;
			collect->image_c->pixels[i * 4 + 1] = color * 0.75;
			collect->image_c->pixels[i * 4 + 2] = 50;
		}
		i++;
	}
}

void	ft_randomize(void *param)
{
	t_gamedata		*gd;
	static float	angle = 0.0f;
	int				c_idx;
	t_collect		*collect;

	angle += 0.1f;
	gd = (t_gamedata *)param;
	c_idx = 0;
	while (c_idx < gd->coins)
	{
		collect = &gd->map->collects[c_idx];
		if (!collect->pick)
		{
			collect_color(collect, angle);
		}
		c_idx++;
	}
}

void	collect_init(t_collect *coll, int x, int y, mlx_t *mlx)
{
	coll->x = x;
	coll->y = y;
	coll->scale = 1.0f;
	coll->pick = false;
	coll->texture_c = mlx_load_png("textures/coin.png");
	if (!coll->texture_c)
	{
		mlx_close_window(mlx);
		return ;
	}
	//prptxt(&coll->image_c, coll->scale, mlx);
	if (!coll->image_c)
	{
		mlx_delete_texture(coll->texture_c);
		mlx_close_window(mlx);
		return ;
	}
	mlx_image_to_window(mlx, coll->image_c, coll->x, coll->y);
}*/
