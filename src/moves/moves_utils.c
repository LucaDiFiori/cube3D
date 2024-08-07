/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-10 14:05:05 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-07-10 14:05:05 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"
/************************PRIMO PASSAGGIO DI NORMINETTATURA******************* */

/**
 * Function: is_walkable
 * ----------------------
 * Checks if a specific map location is walkable based on the game map's 
 * layout. This function determines whether the given coordinates correspond
 * to a valid, non-obstructed location within the map boundaries.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the map data.
 *  - x: The x-coordinate to check.
 *  - y: The y-coordinate to check.
 *
 * Returns:
 *  - An integer indicating whether the location is walkable:
 *    - Returns 1 (true) if the location is within map bounds and not obstructed.
 *    - Returns 0 (false) otherwise.
 *
 * Process:
 *  - Converts the floating-point coordinates `x` and `y` to integer map coordinates
 *    using `floor()`.
 *  - Checks if the resulting coordinates are within the map's boundaries.
 *  - Verifies that the map cell at the calculated coordinates is not blocked:
 *    - A cell with '1' or 'D' is considered obstructed (non-walkable).
 *  - Returns 1 if the cell is valid and walkable, otherwise returns 0.
 */
static int is_walkable(t_game *g, double x, double y) 
{
    int map_x;
    int map_y;

	map_x = (int)floor(x);
	map_y = (int)floor(y);
    return (map_x >= 0 && map_x < g->map.map_x && map_y >= 0 
        && map_y < g->map.map_y && g->map.map_mat[map_y][map_x] != '1'
        && g->map.map_mat[map_y][map_x] != 'D');
}

/**
 * Function: move_forward
 * -----------------------
 * Moves the player forward in the direction they are currently facing. 
 * This function updates the player's position based on their direction vector
 * and move speed, provided the new position is walkable and within map boundaries.
 * 
 * Process:
 *  - Calculates the new potential position (`new_x` and `new_y`) by adding the
 *    direction vector multiplied by the move speed to the current player position.
 *  - Checks if the new position is walkable using the `is_walkable` function.
 *  - If the new position is valid and walkable, updates the player's position to
 *    the new coordinates.
 *  - Returns 0 to indicate successful execution of the move operation.
 */
int move_forward(t_game *g) 
{
    double  new_x;
    double  new_y;

    new_x = g->player.x + g->player.dir_vec[0] * g->player.move_speed;
    new_y = g->player.y + g->player.dir_vec[1] * g->player.move_speed;
    if (is_walkable(g, new_x, new_y)) 
    {
        g->player.x = new_x;
        g->player.y = new_y;
    }
    return (0);
}

int move_backward(t_game *g) 
{
    double  new_x ;
    double  new_y;

    new_x = g->player.x - g->player.dir_vec[0] * g->player.move_speed;
    new_y = g->player.y - g->player.dir_vec[1] * g->player.move_speed;
    if (is_walkable(g, new_x, new_y)) 
    {
        g->player.x = new_x;
        g->player.y = new_y;
    }
    return (0);
}

int move_left(t_game *g) 
{
    double  new_x;
    double  new_y;

    new_x = g->player.x + g->player.dir_vec[1] * g->player.move_speed;
    new_y = g->player.y - g->player.dir_vec[0] * g->player.move_speed;
    if (is_walkable(g, new_x, new_y)) 
    {
        g->player.x = new_x;
        g->player.y = new_y;
    }
    return (0);
}

int move_right(t_game *g) 
{
    double  new_x;
    double  new_y;

    new_x = g->player.x - g->player.dir_vec[1] * g->player.move_speed;
    new_y = g->player.y + g->player.dir_vec[0] * g->player.move_speed;
    if (is_walkable(g, new_x, new_y)) 
    {
        g->player.x = new_x;
        g->player.y = new_y;
    }
    return (0);
}

