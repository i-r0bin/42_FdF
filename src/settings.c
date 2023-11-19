/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:52:46 by rilliano          #+#    #+#             */
/*   Updated: 2023/11/10 22:19:25 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_close(t_map *map)
{
	fdf_free(map);
	exit(0);
}

void	set_zoom(t_point *a, t_point *b, t_map *map)
{
	a->x *= map->scale;
	a->y *= map->scale;
	a->z *= map->z_scale;
	b->x *= map->scale;
	b->y *= map->scale;
	b->z *= map->z_scale;
}

void	set_param(t_point *a, t_point *b, t_map *map)
{
	set_zoom(a, b, map);
	if (map->is_iso)
	{
		ft_isometric(a, map->ng);
		ft_isometric(b, map->ng);
	}
	a->x += map->shift_x;
	a->y += map->shift_y;
	b->x += map->shift_x;
	b->y += map->shift_y;
}

int	set_line_color(float a_z, float b_z)
{
	if (a_z == 0 && b_z == 0)
		return (0xBBFAFF);
	if (a_z != b_z)
		return (0xfc031c);
	return (0xfc0345);
}

int	set_image(t_map *map)
{
	map->img = mlx_new_image(map->mlx_ptr, map->win_x, map->win_y);
	if (map->img == NULL)
		fdf_close(map);
	map->img_addr = mlx_get_data_addr(map->img, &(map->pixel_bits), \
			&(map->line_bytes), &(map->endian));
	if (map->img_addr == NULL)
		fdf_close(map);
	draw_map(map);
	mlx_put_image_to_window(map->mlx_ptr, map->win_ptr, map->img, 0, 0);
	return (0);
}
