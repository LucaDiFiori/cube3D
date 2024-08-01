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

static void init_text(t_game *g)
{
	g->map.text.north = NULL;
	g->map.text.south = NULL;
	g->map.text.east = NULL;
	g->map.text.west = NULL;
	g->map.text.c_rgb.r = -1;
	g->map.text.c_rgb.g = -1;
	g->map.text.c_rgb.b = -1;
	g->map.text.f_rgb.r = -1;
	g->map.text.f_rgb.g = -1;
	g->map.text.f_rgb.b = -1;
	g->map.text.wall_side = 0;
	g->map.text.wall_pixels = NULL;
	g->map.text.wall_pixels = ft_calloc(5, sizeof(int *));
	if (!g->map.text.wall_pixels)
		quit_and_free(MALLOC_ERR, 2, g);
	g->map.text.column_x = 0;
	g->map.text.column_y = 0;
	g->map.text.vertical_step = 0;
	g->map.text.current_tex_y = 0;
}
static void	init_map_struct(t_game *g)
{
	g->map.map_path = NULL;
	g->map.map_mat = NULL;
	init_text(g);
	g->map.map_x = 0;
	g->map.door_x = -1;
	g->map.door_y = -1;
	g->map.exit_x = -1;
	g->map.exit_y = -1;
	g->map.c_color = 0;
	g->map.f_color = 0;
}



void init_player_dir(t_game *g)
{
	if (g->player.start_dir == 'N')
	{
		g->player.dir_vec[0] = 0;
		g->player.dir_vec[1] = -1;
		g->player.plane_x = FOV;
		g->player.plane_y = 0;
	}
	else if (g->player.start_dir  == 'E')
	{
		g->player.dir_vec[0] = 1;
		g->player.dir_vec[1] = 0;
		g->player.plane_x = 0;
		g->player.plane_y = FOV;
	}
	else if (g->player.start_dir  == 'S')
	{
		g->player.dir_vec[0] = 0;
		g->player.dir_vec[1] = 1;
		g->player.plane_x = -(FOV);
		g->player.plane_y = 0;
	}
	else if (g->player.start_dir  == 'W')
	{
		g->player.dir_vec[0] = -1;
		g->player.dir_vec[1] = 0;
		g->player.plane_x = 0;
		g->player.plane_y = -(FOV);
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
}

/*Alloca la matrice che rappresenta i singoli pixel della schermata di gioco*/
static void init_screen_pixels(t_game *g)
{
	int i;
	
	i = 0;
	g->screen_pixels = ft_calloc(RES_Y + 1, sizeof(int *));
    if (!g->screen_pixels)
	{
        quit_and_free(MALLOC_ERR, 2, g);
	}
	while (i < RES_Y)
	{
		g->screen_pixels[i] = ft_calloc(RES_X + 1, sizeof(int));
		if (!g->screen_pixels[i])
        quit_and_free(MALLOC_ERR, 2, g);
		i++;
	}
}

void init_game_struct(t_game *g)
{
	init_map_struct(g);
	g->screen_pixels = NULL;
	init_screen_pixels(g);
	g->mlx.mlx_ptr = NULL;
	g->mlx.win_ptr = NULL;

	/*minimap*/
	g->minimap.minimap_height = MINI_RES_Y;
	g->minimap.minimap_width = MINI_RES_X;
	//g->minimap.view_size = 5;

	/*player array*/
	for (int i = 0; i < 256; i++)
		g->player.keys[i] = 0;
	
	/*frame*/
	g->time = 0;
	g->old_time = 0;
	g->frametime_sec = 0;


	//init_ray(g); tanto la chiamo in render

}
