/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaestri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 01:08:41 by cmaestri          #+#    #+#             */
/*   Updated: 2024/07/07 02:29:50 by cmaestri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static int	check_rows(t_game game)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (game.map.map_mat[0][i])
	{
		if (game.map.map_mat[0][i] != '1' && game.map.map_mat[0][i] != ' ')
			return (0);
		i++;
	}
	i = 0;
	while (game.map.map_mat[i])
		i++;
	k = i - 1;
	while (game.map.map_mat[k][j])
	{
		if (game.map.map_mat[k][j] != '1' && game.map.map_mat[k][j] != ' ')
			return (0);
		j++;
	}
	return (1);
}

static int	check_columns(t_game game)
{
	int	i;
	int	j;
	
	i = 0;
	while (game.map.map_mat[i])
	{
		j = 0;
		while (game.map.map_mat[i][j] == ' ')
			j++;
		if (game.map.map_mat[i][j] != '1')
			return (0);
		j = 0;
		while (game.map.map_mat[i][j])
			j++;
		j--;
		while (j >= 0 && game.map.map_mat[i][j] == ' ')
			j--;
		if (game.map.map_mat[i][j] != '1')
			return (0);
		i++;
	}
	return (1);
}
int	is_closed(t_game game)
{
	if (!check_rows(game) || !check_columns(game))
		return (0);
	else
		return (1);
}