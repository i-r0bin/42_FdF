/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rilliano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:51:53 by rilliano          #+#    #+#             */
/*   Updated: 2023/11/11 12:47:24 by rilliano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(char *path, t_map *map)
{
	int		height;
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		handle_error("an error occurred while opening file", map);
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		height++;
	}
	close(fd);
	return (height);
}

void	row_alloc(t_map *map, int n_row, char *line, int fd)
{
	map->matrix[n_row] = (t_point *)malloc((n_words(line, \
		' ') + 1) * sizeof(t_point));
	if (!map->matrix[n_row])
	{
		free(line);
		n_row++;
		while (n_row++ < map->rows)
		{
			line = get_next_line(fd);
			free(line);
		}
		close(fd);
		handle_error("malloc() failed to allocate memory", map);
	}
}

void	fill_row(t_map *map, int n_row, char *line)
{
	char	**splitted;
	int		j;

	splitted = ft_split(line, ' ');
	j = 0;
	while (splitted[j])
	{
		map->matrix[n_row][j].y = (float)n_row;
		map->matrix[n_row][j].x = (float)j;
		map->matrix[n_row][j].z = (float)ft_atoi(splitted[j]);
		map->matrix[n_row][j].is_last = 0;
		free(splitted[j]);
		j++;
	}
	map->matrix[n_row][--j].is_last = 1;
	free(splitted);
}

void	load_map(char *path, t_map *map)
{
	char	*line;
	int		fd;
	int		i;

	map->rows = get_height(path, map);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		handle_error("an error occurred while opening file", map);
	map->matrix = (t_point **)malloc((map->rows + 1) * sizeof(t_point *));
	if (!map->matrix)
	{
		close(fd);
		handle_error("malloc() failed to allocate memory", map);
	}
	i = 0;
	while (i < map->rows)
	{
		line = get_next_line(fd);
		row_alloc(map, i, line, fd);
		fill_row(map, i, line);
		free(line);
		i++;
	}
	map->matrix[i] = NULL;
	close(fd);
}
