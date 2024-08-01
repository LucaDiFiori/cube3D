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


//initialize the ray info
static void init_info(t_game *g, int x)
{
	g->ray.camera_x = 2 * x / (double)RES_X - 1;
	g->ray.dir_x = g->player.dir_vec[0] + g->player.plane_x * g->ray.camera_x;
	g->ray.dir_y = g->player.dir_vec[1] + g->player.plane_y * g->ray.camera_x;
	g->ray.current_x = (int)g->player.x;
	g->ray.current_y = (int)g->player.y;
    if (fabs(g->ray.dir_x) < DBL_EPSILON) 
	{
        // Gestisci il caso in cui dir_x è vicino a zero
		g->ray.delta_dist_x = DBL_MAX; // O un valore molto grande
    } 
	else 
	{
        g->ray.delta_dist_x = fabs(1 / g->ray.dir_x);
    }
    if (fabs(g->ray.dir_y) < DBL_EPSILON) 
	{
        // Gestisci il caso in cui dir_y è vicino a zero
        g->ray.delta_dist_y = DBL_MAX; // O un valore molto grande
    } 
	else 
	{
        g->ray.delta_dist_y = fabs(1 / g->ray.dir_y);
    }
}


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

static void dda(t_game *g)
{
	int	hit;

	hit = 0;
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
		//if (g->ray.current_y < 0.25 || g->ray.current_y > g->map.map_y - 0.25 || g->ray.current_x > g->map.map_x -1.25)
		//	break;
		/*else*/if (g->map.map_mat[g->ray.current_y][g->ray.current_x] == '1')  // QUESTA LINEA DECIDE COSA è SOLITO E QUINDI COSA VIENE DISEGNATO A SCHERMO COME MURO
			hit = 1;
	}
}

/*vedere se dividerla in 3 funzioni*/
static void find_column_height(t_game *g)
{
	/*Questa parte del codice determina la distanza dal giocatore al muro che il 
	  raggio ha colpito (wall_distance). Se g->ray.side è 0, significa che il 
	  raggio ha colpito una parete verticale; se è 1, ha colpito una parete orizzontale.*/
	if (g->ray.side == 0)
		g->ray.wall_distance = (g->ray.side_dist_x - g->ray.delta_dist_x);
	else
		g->ray.wall_distance = (g->ray.side_dist_y - g->ray.delta_dist_y);

	/*calcolo dell'altezza della linea*/
	g->ray.line_height = (int)(RES_Y / g->ray.wall_distance);

	/*calcolo del punto di inizio e fine della linea da disegnare*/
	g->ray.draw_start = -(g->ray.line_height) / 2 + RES_Y / 2;
	if (g->ray.draw_start < 0)
		g->ray.draw_start = 0;
	g->ray.draw_end = g->ray.line_height / 2 + RES_Y / 2;
	if (g->ray.draw_end >= RES_Y)
		g->ray.draw_end = RES_Y - 1;

	/*Questa parte calcola la posizione precisa del punto di impatto del raggio 
	  sul muro, memorizzandola in wall_x.*/
	if (g->ray.side == 0)
		g->ray.wall_x = g->player.y + g->ray.wall_distance * g->ray.dir_y;
	else
		g->ray.wall_x = g->player.x + g->ray.wall_distance * g->ray.dir_x;
	g->ray.wall_x -= floor(g->ray.wall_x);
}


void raycasting(t_game *g)
{
	int x;

	x = 0;
	//in un ciclo che itera per ogni colonna di pixel dello schermo 
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