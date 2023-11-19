/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:43:05 by rilliano          #+#    #+#             */
/*   Updated: 2023/11/10 22:05:10 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include <math.h>
# include <errno.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		is_last;
}	t_point;

typedef struct s_map
{
	int		rows;
	t_point	**matrix;
	int		scale;
	int		z_scale;
	int		shift_x;
	int		shift_y;
	int		is_iso;
	double	ng;
	int		win_x;
	int		win_y;
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	void	*img;
	void	*mlx_ptr;
	void	*win_ptr;
	char	*img_addr;
}	t_map;

void	load_map(char *path, t_map *map);
void	fdf_pixel_put(t_map *map, int x, int y, int color);
void	draw_line(t_point a, t_point b, t_map *map);
void	draw_map(t_map *map);
int		deal_key(int key, t_map *map);
int		deal_key_bonus(int key, t_map *map);
void	handle_error(char *s, t_map *map);
float	ft_module(float n);
float	ft_max(float a, float b);
void	ft_isometric(t_point *dot, double ng);
void	free_matrix(t_point **matrix);
int		fdf_close(t_map *map);
void	fdf_free(t_map *map);
int		set_line_color(float a_z, float b_z);
void	set_zoom(t_point *a, t_point *b, t_map *map);
void	set_param(t_point *a, t_point *b, t_map *map);
int		set_image(t_map *map);

#endif
