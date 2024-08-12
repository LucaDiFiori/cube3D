/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaestri <cmaestri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:59 by cmaestri          #+#    #+#             */
/*   Updated: 2024/07/15 15:05:48 by cmaestri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	find_rows_and_cols(t_map *map)
{
	int	x;
	
	if (!map->map_mat)
		return ;
	map->map_y = 0;
	map->map_x = 0;
	while (map->map_mat[map->map_y])
	{
		x = 0;
		while (map->map_mat[map->map_y][x])
			x++;
		if (x > map->map_x)
			map->map_x = x;
		map->map_y++;
	}
}

char	*duplicate_row(char *row, int current_cols, int cols)
{
	char *row_copy;
	int j;
	
	row_copy = (char *)malloc((cols + 1) * sizeof(char));
	if (!row_copy)
		return (NULL);
	j = 0;
	while (j < cols)
	{
		if (j < current_cols)
			row_copy[j] = row[j];
		else
			row_copy[j] = ' ';
		j++;
	}
	row_copy[cols] = '\0';
	return (row_copy);
}

char	**duplicate_map(char **map, int rows, int cols)
{
	char	**map_copy;
	int		i;
	int		current_cols;

	map_copy = (char **)malloc(rows * sizeof(char *));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		current_cols = 0;
		while (map[i][current_cols])
			current_cols++;
		map_copy[i] = duplicate_row(map[i], current_cols, cols);
		if (!map_copy[i])
			return (NULL);
		i++;
	}
	return (map_copy);
}

void	free_mapcopy(char **map, int rows)
{
	int	i;
	int j;
	
	if (!map)
		return ;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (map[i][j])
			j++;
		free(map[i]);
		i++;
	}
	free(map);
}
