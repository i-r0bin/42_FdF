/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:51:13 by rilliano          #+#    #+#             */
/*   Updated: 2023/11/10 22:12:55 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_default(t_map *map)
{
	map->scale = 20;
	map->z_scale = 1;
	map->is_iso = 1;
	map->ng = 0.523599;
	map->win_x = 1980;
	map->win_y = 1000;
	map->shift_x = map->win_x / 3;
	map->shift_y = map->win_y / 3;
	map->mlx_ptr = mlx_init();
	if (!map->mlx_ptr)
		handle_error("malloc() failed to allocate memory", map);
	map->win_ptr = mlx_new_window(map->mlx_ptr, map->win_x, map->win_y, "FDF");
	if (!map->win_ptr)
		handle_error("malloc() failed to allocate memory", map);
}

void	map_init(t_map *map)
{
	map->matrix = NULL;
	map->img = NULL;
	map->mlx_ptr = NULL;
	map->win_ptr = NULL;
}

int	main(int argc, char **argv)
{
	t_map	*map;

	if (argc != 2)
		handle_error("Error!\nTry:\t./fdf filepathname.fdf", NULL);
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		handle_error("malloc() failed to allocate memory", map);
	load_map(argv[1], map);
	set_default(map);
	mlx_key_hook(map->win_ptr, deal_key, map);
	mlx_hook(map->win_ptr, DestroyNotify, ButtonPressMask, fdf_close, map);
	set_image(map);
	mlx_loop(map->mlx_ptr);
	return (0);
}
