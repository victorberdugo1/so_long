/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 07:50:05 by victor            #+#    #+#             */
/*   Updated: 2024/10/15 09:51:38 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_2(t_gdata *gamedata)
{
	if (gamedata->cover)
	{
		mlx_delete_image(gamedata->mlx, gamedata->cover);
		gamedata->cover = NULL;
	}
	if (gamedata->txt_cover)
	{
		mlx_delete_texture(gamedata->txt_cover);
		gamedata->txt_cover = NULL;
	}
	if (gamedata->nbr)
	{
		mlx_delete_image(gamedata->mlx, gamedata->nbr);
		gamedata->nbr = NULL;
	}
	if (gamedata->msg)
	{
		mlx_delete_image(gamedata->mlx, gamedata->msg);
		gamedata->msg = NULL;
	}
}
