/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:27 by vberdugo          #+#    #+#             */
/*   Updated: 2024/09/21 17:20:09 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "so_long.h"

/*
static mlx_image_t* image;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;

	char	*relative_path = "./textures/player.png";

	mlx_texture_t *texture = mlx_load_png(relative_path);

	image = mlx_texture_to_image(param, texture);

	mlx_image_to_window(param, image, 0,0 );

	
   for (uint32_t i = 0; i < image->width; ++i)
   {
	   for (uint32_t y = 0; y < image->height; ++y)
	   {
	   	uint32_t color = ft_pixel(
	   rand() % 0xFF, // R
	   rand() % 0xFF, // G
	   rand() % 0xFF, // B
	   rand() % 0xFF  // A
	   	);
		mlx_put_pixel(image, i, y, color);
	   }
	}
	 
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}


int32_t main(void)
{
	mlx_t* mlx;

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 128, 128)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	ft_randomize(mlx);

	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);

	mlx_terminate(mlx);
	
	return (EXIT_SUCCESS);
}
*/

uint32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	pixel_texture(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	uint32_t	index;
	uint8_t		*pixel;

	index = (y * texture->width + x) * 4;
	pixel = &texture->pixels[index];
	return (ft_pixel(pixel[0], pixel[1], pixel[2], pixel[3]));
}

void	ft_resize(mlx_texture_t *original_texture, mlx_image_t **image, float scale, mlx_t *mlx)
{
	int32_t		new_width;
	int32_t		new_height;
	int32_t		x;
	int32_t		y;
	uint32_t	src_x;
	uint32_t	src_y;

	if (*image != NULL)
		mlx_delete_image(mlx, *image);
	if (original_texture)
	{
		new_width = (int32_t)(original_texture->width * scale);
		new_height = (int32_t)(original_texture->height * scale);
		*image = mlx_new_image(mlx, new_width, new_height);
		if (!*image)
		{
			mlx_close_window(mlx);
			return ;
		}
		x = 0;
		while (x < new_width)
		{
			y = 0;
			while (y < new_height)
			{
				src_x = (x * original_texture->width) / new_width;
				src_y = (y * original_texture->height) / new_height;
				mlx_put_pixel(*image, x, y, pixel_texture(original_texture, src_x, src_y));
				++y;
			}
			++x;
		}
	}
}

void	ft_hook(void *param)
{
	mlx_t					*mlx;
	static float			scale;
	static mlx_image_t		*image;
	static mlx_texture_t	*original_texture;

	mlx = param;
	scale = 1.0f;
	image = NULL;
	original_texture = NULL;
	if (!original_texture)
	{
		original_texture = mlx_load_png("./textures/player.png");
		if (!original_texture)
		{
			mlx_close_window(mlx);
			return ;
		}
		ft_resize(original_texture, &image, scale, mlx);
		mlx_image_to_window(mlx, image, 0, 0);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (image && image->instances)
	{
		if (mlx_is_key_down(mlx, MLX_KEY_UP))
			image->instances[0].y -= 5;
		if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
			image->instances[0].y += 5;
		if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
			image->instances[0].x -= 5;
		if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
			image->instances[0].x += 5;
	}
}

int	main(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		return (EXIT_FAILURE);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
