/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:27 by vberdugo          #+#    #+#             */
/*   Updated: 2024/09/19 17:00:06 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "so_long.h"

static mlx_image_t* image;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
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
    mlx_texture_t* texture = NULL;
    mlx_image_t* img;
	char	*relative_path = "./textures/sheet.png";
	//int32_t		img_width = 576;
	//int32_t		img_height = 384;

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


// Load texture from file
    texture = mlx_load_png(relative_path); // Corrected to use one argument
    if (!texture)
    {
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return(EXIT_FAILURE);
    }

    // Convert texture to an image
    img = mlx_texture_to_image(mlx, texture);
    if (!img)
    {
        mlx_delete_texture(texture); // Clean up texture
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return(EXIT_FAILURE);
    }

    // Display the texture image
    if (mlx_image_to_window(mlx, img, 0, 0) < 0)
    {
        mlx_delete_image(mlx, img);  // Corrected to include mlx
        mlx_delete_texture(texture);
        mlx_close_window(mlx);
        puts(mlx_strerror(mlx_errno));
        return(EXIT_FAILURE);
    }


	mlx_loop_hook(mlx, ft_randomize, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);

	// Cleanup
	mlx_delete_image(mlx, img);
	mlx_delete_texture(texture);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
