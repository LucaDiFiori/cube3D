/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 09:38:12 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-08-07 09:38:12 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"


static void set_player_direction(t_game *g, int dir_x, int dir_y)
{
	g->player.dir_vec[0] = dir_x;
	g->player.dir_vec[1] = dir_y;
}

static void set_player_plane(t_game *g, double plane_x, double plane_y)
{
    g->player.plane_x = plane_x;
    g->player.plane_y = plane_y;
}
/**
 * Function: init_player_dir
 * --------------------------
 * Initializes the player's direction and view plane based on the specified
 * starting direction. This function sets up the player's movement direction
 * and the view plane to align with the initial facing direction ('N', 'E', 'S', or 'W').
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing player data and starting direction.
 *
 * Process:
 *  - Checks the `start_dir` field in the `player` structure to determine the initial
 *    facing direction.
 *  - Sets the player's direction vector and view plane accordingly
 *  - Updates the player's direction vector and view plane in the game state.
 */
void init_player_dir(t_game *g)
{
	if (g->player.start_dir == 'N')
	{
		set_player_direction(g, 0, -1);
		set_player_plane(g, FOV, 0);
	}
	else if (g->player.start_dir  == 'E')
	{
		set_player_direction(g, 1, 0);
		set_player_plane(g, 0, FOV);
	}
	else if (g->player.start_dir  == 'S')
	{
		set_player_direction(g, 0, 1);
		set_player_plane(g, -FOV, 0);
	}
	else if (g->player.start_dir  == 'W')
	{
		set_player_direction(g, -1, 0);
		set_player_plane(g, 0, -FOV);
	}
}

void init_ray(t_game *g)
{
	g->ray.camera_x = 0;
	g->ray.dir_x = 0;
	g->ray.dir_y = 0;
	g->ray.current_x = 0;
	g->ray.current_y = 0;
	g->ray.side_dist_x = 0;
	g->ray.side_dist_y = 0;
	g->ray.delta_dist_x = 0;
	g->ray.delta_dist_y = 0;
	g->ray.wall_distance = 0;
	g->ray.wall_x = 0;
	g->ray.step_x = 0;
	g->ray.step_y = 0;
	g->ray.side = 0;
	g->ray.line_height = 0;
	g->ray.draw_start = 0;
	g->ray.draw_end = 0;
	g->ray.hit_type = 0;
}

void init_player_data(t_game *g)
{
	int	i;

	i = -1;
	g->player.x = 0.0;
	g->player.y = 0.0;
	while (++i < 256)
		g->player.keys[i] = 0;
	g->player.toggle_door_debounce = 0;
	g->player.move_speed = 0;
	g->player.rot_speed = 0;
	g->player.plane_x = 0;
	g->player.plane_y = 0;
}