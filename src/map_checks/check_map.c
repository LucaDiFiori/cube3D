/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaestri <cmaestri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:59 by cmaestri          #+#    #+#             */
/*   Updated: 2024/07/15 16:09:32 by cmaestri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static int valid_door(t_game *g, int x, int y)
{
    if ((x > 0 && g->map.map_mat[y][x - 1] == '1')
		&& (g->map.map_mat[y][x + 1] == '1'))
		return (1);
    if ((y > 0 && g->map.map_mat[y - 1][x] == '1')
		&& (g->map.map_mat[y + 1][x] == '1'))
		return (1);
	return (0);
}

static int	valid_chars(t_game *g, char c, int x, int y)
{
	if ((c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S' && c != 'E'
		&& c != 'W' && c != 'D'))
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		g->player.x = x;
		g->player.y = y;
		g->player.start_dir = c;
		g->map.num_players++;
	}
	if (c == 'D')
	{
		if (!valid_door(g, x, y))
			return (0);
	}
	return (1);
}

static int	check_characters(t_game *g)
{
	int		x;
	int		y;
	char	c;
	
	y = 0;
	while (g->map.map_mat[y])
	{
		x = 0;
		while (g->map.map_mat[y][x])
		{
			c = g->map.map_mat[y][x];
			if (!valid_chars(g, c, x, y))
				return (1);
			x++;
		}
		y++;
	}
	if (g->map.num_players != 1)
		return (1);
	return (0);
}

int	check_map(t_game *g)
{
	char **map_copy;

	find_rows_and_cols(&g->map);
	if (is_closed(*g))
	{
		map_copy = duplicate_map(g->map.map_mat, g->map.map_y, g->map.map_x);
		if (check_characters(g)
			|| is_reachable(g, map_copy, g->map.map_y, g->map.map_x))
			{
				free_mapcopy(map_copy, g->map.map_y);
				return (0);
			}
		free_mapcopy(map_copy, g->map.map_y);
		return (1);
	}
	return (0);
}