/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:46:01 by rilliano          #+#    #+#             */
/*   Updated: 2023/11/10 22:11:26 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_pixel_put(t_map *map, int x, int y, int color)
{
	char	*dst;

	if (x > map->win_x || y > map->win_y || x < 0 || y < 0)
		return ;
	dst = map->img_addr + (y * map->line_bytes + x * (map->pixel_bits / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_point a, t_point b, t_map *map)
{
	float	x_gap;
	float	y_gap;
	float	gap;
	int		color;

	set_param(&a, &b, map);
	gap = ft_max(ft_module(b.x - a.x), ft_module(b.y - a.y));
	x_gap = (b.x - a.x) / gap;
	y_gap = (b.y - a.y) / gap;
	color = set_line_color(a.z, b.z);
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		fdf_pixel_put(map, a.x, a.y, color);
		a.x += x_gap;
		a.y += y_gap;
	}
}

void	draw_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->rows)
	{
		j = 0;
		while (1)
		{
			if (map->rows > (i + 1))
				draw_line(map->matrix[i][j], map->matrix[i + 1][j], map);
			if (!map->matrix[i][j].is_last)
				draw_line(map->matrix[i][j], map->matrix[i][j + 1], map);
			if (map->matrix[i][j].is_last)
				break ;
			j++;
		}
		i++;
	}
}
