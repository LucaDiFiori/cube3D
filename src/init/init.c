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

void	init_game_struct(t_game *game_struct)
{
	game_struct->map.map_path = NULL;

	game_struct->map.t_wall_text.north = NULL;
	game_struct->map.t_wall_text.south = NULL;
	game_struct->map.t_wall_text.east = NULL;
	game_struct->map.t_wall_text.west = NULL;
	game_struct->map.t_wall_text.c_color = NULL; /*forse questa e quella sotto potrei toglielre*/
	game_struct->map.t_wall_text.f_color = NULL;
	game_struct->map.t_wall_text.c_rgb.r = 0;
	game_struct->map.t_wall_text.c_rgb.g = 0;
	game_struct->map.t_wall_text.c_rgb.b = 0;
	game_struct->map.t_wall_text.f_rgb.r = 0;
	game_struct->map.t_wall_text.f_rgb.g = 0;
	game_struct->map.t_wall_text.f_rgb.b = 0;
}