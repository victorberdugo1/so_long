/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vberdugo <vberdugo@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:20:34 by vberdugo          #+#    #+#             */
/*   Updated: 2024/09/16 10:44:08 by vberdugo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LO_LONG_H
# define LO_LONG_H

# include <stdlib.h>
# include "libft/libft.h"

# define LONG_MAX 2147483647L
# define LONG_MIN -2147483648L
# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;

typedef struct s_map
{
	int				nbr;
	int				index;
	int				push_cost;
	t_bool			above_half;
	t_bool			cheapest;
	struct s_lst	*target_node;
	struct s_lst	*next;
	struct s_lst	*prev;
}	t_map;

#endif
