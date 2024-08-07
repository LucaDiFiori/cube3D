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

/**
 * Function: check_rows
 * ----------------------
 * Validates the boundary rows of the game map to ensure they contain only
 * '1' or ' ' characters. This function checks the first and last rows of the 
 * map matrix to confirm that they consist solely of wall ('1') or space (' ') 
 * characters, as required by the game's map rules.
 * 
 * Parameters:
 *  - game: A copy of the game structure containing the map data to be validated.
 *
 * Returns:
 *  - An integer indicating the result of the validation:
 *    - Returns 0 if any character in the first or last row is not '1' or ' ' (error).
 *    - Returns 1 if all characters in the first and last rows are valid (success).
 *
 * Process:
 *  - Checks the first row of the map:
 *    - Iterates through each character in the first row.
 *    - Returns 0 if any character is not '1' or ' '.
 *  - Finds the index of the last row (`k`):
 *    - Iterates to count the total number of rows and sets `k` to the index of the last row.
 *  - Checks the last row of the map:
 *    - Iterates through each character in the last row.
 *    - Returns 0 if any character is not '1' or ' '.
 *  - Returns 1 if both boundary rows are valid.
 */
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

/**
 * Function: check_columns
 * -------------------------
 * Validates the boundary columns of the game map to ensure they contain only
 * '1' characters. This function checks the first and last non-space characters 
 * in each row of the map matrix to confirm that they are all '1', which is required 
 * for enclosing the map properly.
 * 
 * Parameters:
 *  - game: A copy of the game structure containing the map data to be validated.
 *
 * Returns:
 *  - An integer indicating the result of the validation:
 *    - Returns 0 if any boundary column character is not '1' (error).
 *    - Returns 1 if all boundary column characters are valid (success).
 *
 * Process:
 *  - Iterates through each row of the map:
 *    - Finds the first non-space character in the row (`j`).
 *    - Returns 0 if the first non-space character is not '1'.
 *    - Finds the last non-space character in the row (`j`).
 *    - Returns 0 if the last non-space character is not '1'.
 *  - Returns 1 if all boundary columns are valid.
 */
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