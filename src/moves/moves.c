/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-10 13:53:50 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-07-10 13:53:50 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"


/*static void	move_forward(t_game *g_s, t_asset *asset)
{
	float new_x = asset->x + asset->rad_x * asset->speed;
	float new_y = asset->y + asset->rad_y * asset->speed;




	if (g_s->map.map_mat[(int)new_y][(int)new_x] != '1')
	{
		asset->x = new_x;
		asset->y = new_y;
		printf("new_x = %f\n", new_x);
	    printf("new_y = %f\n", new_y);
	}
}


int inputs(int key, t_game *g)
{
	//printf("Player coordinates: x = %f, y = %f\n", g->player.x, g->player.y);
	//if (key == 27)
	//	ft_close_x(g);
	if (key == 'w')
	{
		//mlx_clear_window(g->mlx.mlx_ptr, g->mlx.win_ptr);
		move_forward(g, &g->player);
		minimap_test(g);
	}
	return (0);
}*/

/*int inputs(int key, t_game *g)
{
    if (key == 'w')
        g->key.w = 1; // Tasto w premuto
    else if (key == 0) // Simbolo per KeyRelease
        g->key.w = 0; // Tasto w rilasciato
    return (0);
}

void handle_movement(t_game *g)
{
	if (g->key.w)
	{
		move_forward(g, &g->player);
        minimap_test(g);
	}
}*/


static void	move_forward(t_game *g_s, t_asset *asset)
{





	if (g_s->map.map_mat[(int)asset->y][(int)asset->x] != '1')
	{
		float new_x = asset->x + asset->rad_x * asset->speed;
		float new_y = asset->y + asset->rad_y * asset->speed;
		asset->x = new_x;
		asset->y = new_y;
		printf("new_x = %f\n", new_x);
	    printf("new_y = %f\n", new_y);
	}
}



int key_press(int key, t_game *g)
{
    if (key == 'w')
        g->player.movement = 1;
    return (0);
}

int key_release(int key, t_game *g)
{
    if (key == 'w')
        g->player.movement = 0;
    return (0);
}

int handle_movement(t_game *g)
{
	if (g->player.movement)
	{
		move_forward(g, &g->player);
        minimap_test(g);
	}
	return (0);
}