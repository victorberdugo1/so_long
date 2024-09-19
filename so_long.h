/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:34 by vberdugo          #+#    #+#             */
/*   Updated: 2024/09/19 12:50:56 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# define LONG_MAX 2147483647L
# define LONG_MIN -2147483648L
# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_map
{
	int				nbr;
	int				index;
	int				push_cost;
	bool			above_half;
	bool			cheapest;
	struct s_lst	*target_node;
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_map;

#endif
