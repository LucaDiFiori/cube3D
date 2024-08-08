/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-01 10:24:33 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-08-01 10:24:33 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"


/**
 * Function: update_player_direction
 * ------------------------------------
 * Updates the player's direction vector based on the rotation angle. This function
 * applies 2D rotation formulas to the player's direction vector to account for
 * changes in orientation.
 * 
 * Parameters:
 *  - p: A pointer to the player asset containing the direction vector to be updated.
 *  - cos_rot: The cosine of the rotation angle.
 *  - sin_rot: The sine of the rotation angle.
 *
 * Process:
 *  - Applies the 2D rotation formulas:
 *    - New x-coordinate: `new_x = x * cos(alpha) - y * sin(alpha)`
 *    - New y-coordinate: `new_y = x * sin(alpha) + y * cos(alpha)`
 *  - Updates the direction vector with the new coordinates.
 */
static void update_player_direction(t_asset *p, double cos_rot, double sin_rot) 
{
	double  tmp_x;

    tmp_x = p->dir_vec[0];
	p->dir_vec[0] = p->dir_vec[0] * cos_rot - p->dir_vec[1] * sin_rot;
	p->dir_vec[1] = tmp_x * sin_rot + p->dir_vec[1] * cos_rot;
}

/**
 * Function: update_player_plane
 * -------------------------------
 * Updates the player's view plane based on the rotation angle. This function applies
 * 2D rotation formulas to the player's view plane to reflect changes in orientation.
 * 
 * Parameters:
 *  - p: A pointer to the player asset containing the view plane to be updated.
 *  - cos_rot: The cosine of the rotation angle.
 *  - sin_rot: The sine of the rotation angle.
 *
 * Process:
 *  - Applies the 2D rotation formulas:
 *    - New x-coordinate: `new_x = x * cos(alpha) - y * sin(alpha)`
 *    - New y-coordinate: `new_y = x * sin(alpha) + y * cos(alpha)`
 *  - Updates the view plane with the new coordinates.
 */
static void update_player_plane(t_asset *p, double cos_rot, double sin_rot) 
{
	double  tmp_x;

    tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos_rot - p->plane_y * sin_rot;
	p->plane_y = tmp_x * sin_rot + p->plane_y * cos_rot;
}

/**
 * Function: rotate
 * -------------------
 * Rotates the player by applying a given rotation angle to both the direction vector
 * and the view plane. This function calculates the cosine and sine of the rotation
 * angle and updates the player’s direction and view plane accordingly.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing player data.
 *  - rotspeed: The rotation speed (angle) to be applied.
 *
 * Process:
 *  - Calculates the cosine (`cos_rot`) and sine (`sin_rot`) of the rotation speed (`rotspeed`).
 *  - Calls `update_player_direction()` to update the player's direction vector.
 *  - Calls `update_player_plane()` to update the player's view plane.
 */
static int rotate(t_game *g, double rotspeed) 
{
	double  cos_rot;
	double  sin_rot;

    cos_rot = cos(rotspeed);
    sin_rot = sin(rotspeed);
	update_player_direction(&g->player, cos_rot, sin_rot);
	update_player_plane(&g->player, cos_rot, sin_rot);
	return (1);
}

/**
 * Function: rotate_player
 * -------------------------
 * Rotates the player based on the input direction and rotation speed. This function
 * determines the rotation angle for the current frame and applies it to the player’s
 * direction and view plane.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing player data and rotation speed.
 *  - rotdir: The rotation direction (1 for right, -1 for left).
 *
 * Process:
 *  - Calculates the rotation speed (`rotspeed`) as the product of the player's rotation
 *    speed (`g->player.rot_speed`) and the rotation direction (`rotdir`).
 *  - Calls `rotate()` to apply the rotation to the player’s direction vector and view plane.
 * 
 * Note: 
 *  - `ROTSPEED` is a predefined value representing how quickly the player can rotate. 
 *    It indicates the amount of angle the player rotates per input (e.g., pressing arrow keys).
 *  - `ROTDIR` indicates the direction of rotation. It multiplies `rotspeed` by -1 for left
 *    rotation or by 1 for right rotation.
 *  - The product of `rotspeed` and `rotdir` gives the actual rotation angle for the current frame or input.
 *  - Example: If `rotspeed` is 0.05 and `rotdir` is 1 (right), `rotspeed` will be 0.05 radians for that frame.
 */
int rotate_player(t_game *g, double rotdir) 
{
    double  rotspeed;

    rotspeed = g->player.rot_speed * rotdir;
    rotate(g, rotspeed);
    return (0);
}