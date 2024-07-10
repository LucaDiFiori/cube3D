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

static void	init_map_struct(t_game *game_struct)
{
	game_struct->map.map_path = NULL;
	game_struct->map.map_mat = NULL;
	game_struct->map.wall_text.north = NULL;
	game_struct->map.wall_text.south = NULL;
	game_struct->map.wall_text.east = NULL;
	game_struct->map.wall_text.west = NULL;
	game_struct->map.wall_text.c_rgb.r = -1;
	game_struct->map.wall_text.c_rgb.g = -1;
	game_struct->map.wall_text.c_rgb.b = -1;
	game_struct->map.wall_text.f_rgb.r = -1;
	game_struct->map.wall_text.f_rgb.g = -1;
	game_struct->map.wall_text.f_rgb.b = -1;
}

static void init_mlx_struct(t_game *game_struct)
{
	game_struct->mlx.mlx_ptr = NULL;
	game_struct->mlx.win_ptr = NULL;
}

void	init_game_struct(t_game *game_struct)
{
	init_map_struct(game_struct);
	init_mlx_struct(game_struct);

	/*minimappa*/
	game_struct->minimap.minimap_height = MINI_RES_Y;
	game_struct->minimap.minimap_width = MINI_RES_X;
	game_struct->minimap.view_size = 5;
	game_struct->minimap.cell_width = game_struct->minimap.minimap_width / (2.0 * game_struct->minimap.view_size + 1);
	game_struct->minimap.cell_height = game_struct->minimap.minimap_height / (2.0 * game_struct->minimap.view_size + 1);

}
