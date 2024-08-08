/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 09:15:48 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-08-07 09:15:48 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"
/************************PRIMO PASSAGGIO DI NORMINETTATURA******************* */

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
	g->map.text.wall_pixels = ft_calloc(7, sizeof(int *));
	if (!g->map.text.wall_pixels)
		quit_and_free(MALLOC_ERR, 2, g);
	g->map.text.column_x = 0;
	g->map.text.column_y = 0;
	g->map.text.vertical_step = 0;
	g->map.text.current_tex_y = 0;
}

static void	init_map_struct(t_game *g)
{
	init_text(g);
	g->frame.img = NULL;
	g->fps.img = NULL;
	g->map.map_path = NULL;
	g->map.map_mat = NULL;
	g->map.map_x = 0;
	g->map.map_y = 0;
	g->map.c_color = 0;
	g->map.f_color = 0;
	g->map.num_players = 0;
}

/**
 * Function: init_screen_pixels
 * -----------------------------
 * Allocates a matrix representing the individual pixels of the game screen. This function 
 * creates a 2D array where each element corresponds to a pixel's color value. The matrix 
 * is sized according to the screen resolution defined by RES_X and RES_Y.
 */
static void init_screen_pixels(t_game *g)
{
	int	i;
	
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

static void set_minimap(t_game *g)
{
	g->minimap.img_bg.img = NULL;
	g->minimap.cell_width = 0;
	g->minimap.cell_height = 0;
	g->minimap.player_radius = 0;
	g->minimap.minimap_height = MINI_RES_Y;
	g->minimap.minimap_width = MINI_RES_X;
}

void init_game_struct(t_game *g)
{
	init_map_struct(g);
	set_minimap(g);
	g->screen_pixels = NULL;
	init_screen_pixels(g);
	g->mlx.mlx_ptr = NULL;
	g->mlx.win_ptr = NULL;
	init_player_data(g);
	g->frametime_sec = 0;
	g->mouse_pos = RES_X/2;
	g->frame_time_init_flag = 0;
	g->current_time = 0;
	g->frame_time = 0;
}
