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


static int is_walkable(t_game *g, double x, double y) 
{
    int map_x;
    int map_y;

	map_x = (int)floor(x);
	map_y = (int)floor(y);
    return (map_x >= 0 && map_x < g->map.map_x && map_y >= 0 
        && map_y < g->map.map_y && g->map.map_mat[map_y][map_x] != '1');
}

int move_forward(t_game *g) 
{
    double new_x;
    double new_y;

    new_x = g->player.x + g->player.dir_vec[0] * g->player.move_speed;
    new_y = g->player.y + g->player.dir_vec[1] * g->player.move_speed;
    if (is_walkable(g, new_x, new_y)) 
    {
        g->player.x = new_x;
        g->player.y = new_y;
    }
    return 0;
}

int move_backward(t_game *g) 
{
    double new_x = g->player.x - g->player.dir_vec[0] * g->player.move_speed;
    double new_y = g->player.y - g->player.dir_vec[1] * g->player.move_speed;
    if (is_walkable(g, new_x, new_y)) 
    {
        g->player.x = new_x;
        g->player.y = new_y;
    }
    return 0;
}

int move_left(t_game *g) 
{
    double new_x = g->player.x + g->player.dir_vec[1] * g->player.move_speed;
    double new_y = g->player.y - g->player.dir_vec[0] * g->player.move_speed;
    if (is_walkable(g, new_x, new_y)) 
    {
        g->player.x = new_x;
        g->player.y = new_y;
    }
    return 0;
}

int move_right(t_game *g) 
{
    double new_x = g->player.x - g->player.dir_vec[1] * g->player.move_speed;
    double new_y = g->player.y + g->player.dir_vec[0] * g->player.move_speed;
    if (is_walkable(g, new_x, new_y)) 
    {
        g->player.x = new_x;
        g->player.y = new_y;
    }
    return 0;
}

