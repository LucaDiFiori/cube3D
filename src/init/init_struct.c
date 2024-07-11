/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-21 14:17:34 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-21 14:17:34 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static void	init_map_struct(t_game *g)
{
	g->map.map_path = NULL;
	g->map.map_mat = NULL;
	g->map.wall_text.north = NULL;
	g->map.wall_text.south = NULL;
	g->map.wall_text.east = NULL;
	g->map.wall_text.west = NULL;
	g->map.wall_text.c_rgb.r = -1;
	g->map.wall_text.c_rgb.g = -1;
	g->map.wall_text.c_rgb.b = -1;
	g->map.wall_text.f_rgb.r = -1;
	g->map.wall_text.f_rgb.g = -1;
	g->map.wall_text.f_rgb.b = -1;
}

static void init_minimap(t_game *g)
{
	g->minimap.minimap_height = MINI_RES_Y;
	g->minimap.minimap_width = MINI_RES_X;
	g->minimap.view_size = 5;
	g->minimap.cell_width = g->minimap.minimap_width / (2.0 * g->minimap.view_size + 1);
	g->minimap.cell_height = g->minimap.cell_width;
	//g->minimap.offset_x = g->minimap.cell_width / 2;
	//g->minimap.offset_y = g->minimap.cell_height / 2;
}

static void init_mlx_struct(t_game *g)
{
	g->mlx.mlx_ptr = NULL;
	g->mlx.win_ptr = NULL;
}

static void init_key (t_game *g)
{
	/*g->key.w = 0;
	g->key.a = 0;
	g->key.s = 0;
	g->key.d = 0;*/
	g->player.movement = 0;
}


void init_asset(t_game *g)
{
	g->player.speed = MOVESPEED;
	if (g->player.dir == 'N')
	{
		g->player.rad_x = 0;
		g->player.rad_y = -1.0;
	}
	else if (g->player.dir  == 'E')
	{
		g->player.rad_x = 1;
		g->player.rad_y = 0;
	}
	else if (g->player.dir  == 'S')
	{
		g->player.rad_x = 0;
		g->player.rad_y = 1;
	}
	else if (g->player.dir  == 'W')
	{
		g->player.rad_x = -1;
		g->player.rad_y = 0;
	}
}

void init_game_struct(t_game *g)
{
	init_map_struct(g);
	init_mlx_struct(g);
	init_minimap(g);
	init_key(g);

	/*minimappa*/

}
