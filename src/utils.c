/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:54:35 by rilliano          #+#    #+#             */
/*   Updated: 2023/11/18 16:26:23 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	ft_module(float n)
{
	if (n < 0)
		return (n * -1);
	return (n);
}

float	ft_max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

void	ft_isometric(t_point *dot, double ng)
{
	dot->x = (dot->x - dot->y) * cos(ng);
	dot->y = (dot->x + dot->y) * sin(ng) - dot->z;
}

void	free_matrix(t_point **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void	fdf_free(t_map *map)
{
	if (map->matrix != NULL)
		free_matrix(map->matrix);
	if (map->img != NULL)
		mlx_destroy_image(map->mlx_ptr, map->img);
	if (map->win_ptr != NULL)
		mlx_destroy_window(map->mlx_ptr, map->win_ptr);
	if (map->mlx_ptr != NULL)
	{
		mlx_destroy_display(map->mlx_ptr);
		free(map->mlx_ptr);
	}
	free(map);
}
