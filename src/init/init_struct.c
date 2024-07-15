/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaestri <cmaestri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 14:17:34 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/07/15 16:17:40 by cmaestri         ###   ########.fr       */
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
	g->map.map_x = 0;
	g->map.door_x = -1;
	g->map.door_y = -1;
	g->map.exit_x = -1;
	g->map.exit_y = -1;
}

static void init_minimap_struct(t_game *g)
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

static void init_keys (t_game *g)
{

	//g->player.moved = 0;
	for (int i = 0; i < 256; i++)
		g->player.keys[i] = 0;
}


void init_asset(t_game *g)
{
	if (g->player.dir == 'N')
	{
		g->player.dir_vec[0] = 0;
		g->player.dir_vec[1] = -1;
	}
	else if (g->player.dir  == 'E')
	{
		g->player.dir_vec[0] = 1;
		g->player.dir_vec[1] = 0;
	}
	else if (g->player.dir  == 'S')
	{
		g->player.dir_vec[0] = 0;
		g->player.dir_vec[1] = 1;
	}
	else if (g->player.dir  == 'W')
	{
		g->player.dir_vec[0] = -1;
		g->player.dir_vec[1] = 0;
	}
}

void init_game_struct(t_game *g)
{
	init_map_struct(g);
	init_mlx_struct(g);
	init_minimap_struct(g);
	init_keys(g);

	/*minimappa*/

}
