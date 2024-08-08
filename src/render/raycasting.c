/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-24 09:50:33 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-07-24 09:50:33 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"
/**
 * Function: init_info
 * -------------------
 * Initializes the raycasting information for the current frame. This function 
 * sets up the ray direction and distance parameters based on the player's position 
 * and view direction.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the necessary game data.
 *  - x: The x-coordinate of the current ray in the screen.
 *
 * Process:
 *  - Calculates the camera x-coordinate relative to the screen width.
 *  - Sets the ray direction (`dir_x` and `dir_y`) based on the player's direction 
 *    vector and camera plane.
 *  - Initializes the current position of the ray (`current_x` and `current_y`) 
 *    to the player's current position.
 *  - Calculates the distance to the next x-side and y-side based on the ray direction.
 *  - If the ray direction (`dir_x` or `dir_y`) is close to zero, sets the corresponding 
 *    delta distance to a very large value (`DBL_MAX`) to avoid division by zero errors.
 */
static void init_info(t_game *g, int x)
{
	g->ray.camera_x = 2 * x / (double)RES_X - 1;
	g->ray.dir_x = g->player.dir_vec[0] + g->player.plane_x * g->ray.camera_x;
	g->ray.dir_y = g->player.dir_vec[1] + g->player.plane_y * g->ray.camera_x;
	g->ray.current_x = (int)g->player.x;
	g->ray.current_y = (int)g->player.y;
    if (fabs(g->ray.dir_x) < DBL_EPSILON) 
	{
		g->ray.delta_dist_x = DBL_MAX;
    } 
	else 
	{
        g->ray.delta_dist_x = fabs(1 / g->ray.dir_x);
    }
    if (fabs(g->ray.dir_y) < DBL_EPSILON) 
	{
        g->ray.delta_dist_y = DBL_MAX;
    } 
	else 
	{
        g->ray.delta_dist_y = fabs(1 / g->ray.dir_y);
    }
}
/**
 * Function: init_step_and_distance
 * --------------------------------
 * Initializes the step direction and initial side distances for the DDA (Digital 
 * Differential Analysis) algorithm used in raycasting. This function sets up the 
 * initial values needed to traverse the map grid.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the necessary game data.
 *
 * Process:
 *  - Determines the step direction (`step_x` and `step_y`) based on the ray direction 
 *    (`dir_x` and `dir_y`).
 *    - If `dir_x` is negative, sets `step_x` to -1 and calculates the initial 
 *      `side_dist_x` based on the player's position relative to the current grid cell.
 *    - If `dir_x` is positive or zero, sets `step_x` to 1 and calculates the initial 
 *      `side_dist_x` based on the player's position relative to the next grid cell.
 *    - If `dir_y` is negative, sets `step_y` to -1 and calculates the initial 
 *      `side_dist_y` based on the player's position relative to the current grid cell.
 *    - If `dir_y` is positive or zero, sets `step_y` to 1 and calculates the initial 
 *      `side_dist_y` based on the player's position relative to the next grid cell.
 */
static void init_step_and_distance(t_game *g)
{
	if (g->ray.dir_x < 0)
	{
		g->ray.step_x = -1;
		g->ray.side_dist_x =
			(g->player.x - g->ray.current_x) * g->ray.delta_dist_x;
	}
	else
	{
		g->ray.step_x = 1;
		g->ray.side_dist_x =
			(g->ray.current_x + 1.0 - g->player.x) * g->ray.delta_dist_x;
	}
	if (g->ray.dir_y < 0)
	{
		g->ray.step_y = -1;
		g->ray.side_dist_y =
			(g->player.y - g->ray.current_y) * g->ray.delta_dist_y;
	}
	else
	{
		g->ray.step_y = 1;
		g->ray.side_dist_y =
			(g->ray.current_y + 1.0 - g->player.y) * g->ray.delta_dist_y;
	}
}

/**
 * Function: dda
 * -------------
 * Performs the Digital Differential Analyzer (DDA) algorithm to determine 
 * the point of intersection between the ray and a wall or door in the game map.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the necessary game data.
 *
 * Process:
 *  - Initializes `hit` to 0 to start the loop.
 *  - Iterates until a wall, door, or open door is hit (`hit` is set to 1, 2, or 3 respectively).
 *  - Compares `side_dist_x` and `side_dist_y` to determine the next step:
 *    - If `side_dist_x` is smaller, increments `side_dist_x` by `delta_dist_x` 
 *      and updates the ray's current x-coordinate by `step_x`. Sets `side` to 0.
 *    - Otherwise, increments `side_dist_y` by `delta_dist_y` and updates the 
 *      ray's current y-coordinate by `step_y`. Sets `side` to 1.
 *  - Checks the value at the current map coordinates (`map_mat`):
 *    - If it's '1', sets `hit` to 1 (wall).
 *    - If it's 'D', sets `hit` to 2 (door).
 *    - If it's 'd', sets `hit` to 3 (open door).
 *  - Saves the type of object hit (`hit_type`) in the ray structure.
 */
static void dda(t_game *g)
{
    int	hit = 0;
    while (hit == 0)
    {
        if (g->ray.side_dist_x < g->ray.side_dist_y)
        {
            g->ray.side_dist_x += g->ray.delta_dist_x;
            g->ray.current_x += g->ray.step_x;
            g->ray.side = 0;
        }
        else
        {
            g->ray.side_dist_y += g->ray.delta_dist_y;
            g->ray.current_y += g->ray.step_y;
            g->ray.side = 1;
        }
        if (g->map.map_mat[g->ray.current_y][g->ray.current_x] == '1')
            hit = 1;
        else if (g->map.map_mat[g->ray.current_y][g->ray.current_x] == 'D')
            hit = 2;
		else if (g->map.map_mat[g->ray.current_y][g->ray.current_x] == 'd')
			hit = 3;
    }
    g->ray.hit_type = hit;
}


/**
 * Function: find_column_height
 * ----------------------------
 * Determines the height and drawing boundaries of the vertical line representing 
 * the wall slice on the screen, as well as the precise impact point of the ray 
 * on the wall.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the necessary game data.
 *
 * Process:
 *  - Calculates the distance from the player to the wall (`wall_distance`):
 *    - If `g->ray.side` is 0, the ray hit a vertical wall, so `wall_distance` 
 *      is computed using `side_dist_x` and `delta_dist_x`.
 *    - If `g->ray.side` is 1, the ray hit a horizontal wall, so `wall_distance` 
 *      is computed using `side_dist_y` and `delta_dist_y`.
 *  - Computes the height of the wall slice (`line_height`) to be drawn on the screen:
 *    - `line_height` is calculated as the inverse of `wall_distance` scaled to the screen height.
 *  - Determines the start and end points of the vertical line to be drawn:
 *    - `draw_start` is computed to center the line on the screen, adjusted to ensure it is within bounds.
 *    - `draw_end` is computed to ensure it does not exceed the screen height.
 *  - Calculates the precise point of impact of the ray on the wall (`wall_x`):
 *    - If `g->ray.side` is 0, calculates `wall_x` using the player's y-coordinate and the ray's y-direction.
 *    - If `g->ray.side` is 1, calculates `wall_x` using the player's x-coordinate and the ray's x-direction.
 *    - Adjusts `wall_x` to be in the range [0, 1) by subtracting the floor of `wall_x`.
 */
static void find_column_height(t_game *g)
{
    // Calculate the distance to the wall
    if (g->ray.side == 0)
        g->ray.wall_distance = (g->ray.side_dist_x - g->ray.delta_dist_x);
    else
        g->ray.wall_distance = (g->ray.side_dist_y - g->ray.delta_dist_y);

    // Calculate the height of the wall slice
    g->ray.line_height = (int)(RES_Y / g->ray.wall_distance);

    // Calculate the start and end points for drawing the line
    g->ray.draw_start = -(g->ray.line_height) / 2 + RES_Y / 2;
    if (g->ray.draw_start < 0)
        g->ray.draw_start = 0;
    g->ray.draw_end = g->ray.line_height / 2 + RES_Y / 2;
    if (g->ray.draw_end >= RES_Y)
        g->ray.draw_end = RES_Y - 1;

    // Calculate the precise impact point on the wall
    if (g->ray.side == 0)
        g->ray.wall_x = g->player.y + g->ray.wall_distance * g->ray.dir_y;
    else
        g->ray.wall_x = g->player.x + g->ray.wall_distance * g->ray.dir_x;
    g->ray.wall_x -= floor(g->ray.wall_x);
}

/**
 * Function: raycasting
 * --------------------
 * Performs the raycasting algorithm for each vertical column of pixels on the screen.
 * This function calculates the intersection of rays with the game map and determines 
 * how each column of pixels should be drawn based on the ray's interaction with walls.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the necessary game data.
 *
 * Process:
 *  - Iterates over each column of pixels on the screen (`x` from 0 to `RES_X`).
 *  - For each column:
 *    - Calls `init_info` to initialize the ray parameters based on the column index `x`.
 *    - Calls `init_step_and_distance` to set up the step directions and distance to the next wall.
 *    - Calls `dda` to perform the Digital Differential Analyzer algorithm and determine 
 *      the intersection point with the wall.
 *    - Calls `find_column_height` to compute the height of the wall slice and its drawing boundaries.
 *    - Calls `draw_screen_pixels` to update the pixel data for the current column.
 *  - Increments the column index `x` to process the next column.
 */
void raycasting(t_game *g)
{
	int	x;

	x = 0; 
	while (x < RES_X)
	{
		init_info(g, x);
		init_step_and_distance(g);
		dda(g);
		find_column_height(g);
		draw_screen_pixels(g, x);
		x++;
	}
}