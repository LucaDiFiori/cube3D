/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-12 13:47:17 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-08-12 13:47:17 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static int	flood_fill_spaces(t_game *g, char **map, int x, int y)
{
	if (x < 0 || x >= g->map.map_y || y < 0 || y >= g->map.map_x
		|| map[x][y] == '1' || map[x][y] == '*')
		return (0);
	if (map[x][y] == ' ')
		return (1);
	map[x][y] = '*';
	if (flood_fill_spaces(g, map, x - 1, y)
		|| flood_fill_spaces(g, map, x + 1, y)
		|| flood_fill_spaces(g, map, x, y - 1)
		|| flood_fill_spaces(g, map, x, y + 1))
		return (1);
	return (0);
}

int	is_reachable(t_game *game, char **map, int rows, int cols)
{
	int	x;
	int	y;

	x = 0;
	while (x < rows)
	{
		y = 0;
		while (y < cols)
		{
			if (map[x][y] == 'N' || map[x][y] == 'S'
				|| map[x][y] == 'E' || map[x][y] == 'W')
				return (flood_fill_spaces(game, map, x, y));
			y++;
		}
		x++;
	}
	return (0);
}