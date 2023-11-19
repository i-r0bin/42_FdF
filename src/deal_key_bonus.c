/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:44:44 by rilliano          #+#    #+#             */
/*   Updated: 2023/11/18 11:21:26 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_key(int key)
{
	return (key == 43 || key == 45 || key == 97 || key == 100 || \
			key == 105 || key == 115 || key == 119 || key == 65361 || \
			key == 65362 || key == 65363 || key == 65364 || key == 65451 || \
			key == 65453);
}

void	key_action(int key, t_map *map)
{
	if (key == 43 || key == 65451)
		map->scale += 3;
	if (key == 45 || key == 65453)
		map->scale -= 3;
	if (key == 65362)
		map->z_scale += 1;
	if (key == 65364)
		map->z_scale -= 1;
	if (key == 119)
		map->shift_y -= 10;
	if (key == 115)
		map->shift_y += 10;
	if (key == 97)
		map->shift_x -= 10;
	if (key == 100)
		map->shift_x += 10;
	if (key == 105)
		map->is_iso = !map->is_iso;
	if (key == 65363)
		map->ng += 0.05;
	if (key == 65361)
		map->ng -= 0.05;
}

int	deal_key_bonus(int key, t_map *map)
{
	if (check_key(key))
	{
		mlx_destroy_image(map->mlx_ptr, map->img);
		key_action(key, map);
		set_image(map);
	}
	if (key == 65307)
		fdf_close(map);
	return (0);
}
