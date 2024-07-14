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



/*static void	move_forward(t_game *g, t_asset *asset)
{
		asset->x = asset->x + asset->dir_vec[0] * MOVESPEED;
		asset->y = asset->y + asset->dir_vec[1] * MOVESPEED;
		if (g->map.map_mat[(int)floor(g->player.y)][(int)floor(g->player.x)] != '1')
			return ;

		// **********************************
		printf("new_x = %f\n", asset->x);
	    printf("new_y = %f\n", asset->y);
		// **********************************
}



int key_press(int key, t_game *g)
{
    if (key == 'w')
        g->player.mov = 1;
    return (0);
}

int key_release(int key, t_game *g)
{
    if (key == 'w')
         g->player.mov = 0;
    return (0);
}

int handle_movement(t_game *g)
{
	if (g->player.mov && (g->map.map_mat[(int)floor(g->player.y)][(int)floor(g->player.x)] != '1'))
	{
		move_forward(g, &g->player);
        minimap_test(g);
	}
	return (0);
}*/







/*static void move_up_down(t_game *g, float x_dir, float y_dir)
{
    float new_x;
    float new_y;

	new_x = g->player.x + x_dir * MOVESPEED;
	new_y = g->player.y + y_dir * MOVESPEED;


    if (g->map.map_mat[(int)floor(new_y)][(int)floor(new_x)] != '1')
    {
        g->player.x = new_x;
        g->player.y = new_y;
		g->player.dir_vec[0] = x_dir;
		g->player.dir_vec[1] = y_dir;

        // Stampa la nuova posizione
        printf("new_x = %f\n", g->player.x);
        printf("new_y = %f\n", g->player.y);
    }
}

// Funzione per gestire il movimento
int handle_movement(int keycode, t_game *g)
{


    if (keycode == 'w') // 'w'
       move_up_down(g, 0.0, -1.0);
    else if (keycode == 's') // 's'
		move_up_down(g, 0.0, 1.0);

	//destra sinistra vanno modificati
    else if (keycode == 97) // 'a'
        move_up_down(g, -1.0, 0.0);
    else if (keycode == 100) // 'd'
        move_up_down(g, 1.0, 0.0);


    minimap_test(g);

    return (0);
}*/








/*int is_walkable(t_game *g, float x, float y)
{
    // Controlla la direzione del movimento in base ai tasti premuti
    if (g->player.keys['w']) {
        float next_y = y - 0.2;
        if (next_y < 0 || g->map.map_mat[(int)floor(next_y)][(int)floor(x)] == '1')
            return 0;
    } else if (g->player.keys['s']) {
        float next_y = y + 0.2;
        if (next_y >= g->map.map_y || g->map.map_mat[(int)floor(next_y)][(int)floor(x)] == '1')
            return 0;
    } else if (g->player.keys['d']) {
        float next_x = x + 0.2;
        if (next_x >= ft_strlen(g->map.map_mat[(int)floor(y)]) || g->map.map_mat[(int)floor(y)][(int)floor(next_x)] == '1')
            return 0;
    } else if (g->player.keys['a']) {
        float next_x = x - 0.2;
        if (next_x < 0 || g->map.map_mat[(int)floor(y)][(int)floor(next_x)] == '1')
            return 0;
    }

    return 1; // La casella è calpestabile
}*/


























int is_walkable(t_game *g, float x, float y) {
    int map_x = (int)floor(x);
    int map_y = (int)floor(y);
    return (map_x >= 0 && map_x < g->map.map_x && map_y >= 0 
        && map_y < g->map.map_y && g->map.map_mat[map_y][map_x] != '1');
}



/*static void move_up_down(t_game *g, float x_dir, float y_dir)
{
    float new_x;
    float new_y;

	new_x = g->player.x + x_dir * MOVESPEED;
	new_y = g->player.y + y_dir * MOVESPEED;


    if (is_walkable(g, new_x, new_y))
    {
        
		g->player.x = new_x;
        g->player.y = new_y;
		g->player.dir_vec[0] = x_dir;
		g->player.dir_vec[1] = y_dir;

        // Stampa la nuova posizione
        printf("new_x = %f\n", g->player.x);
        printf("new_y = %f\n", g->player.y);

    }
}*/



int key_press(int keycode, t_game *g) {
    if (keycode < 256)
        g->player.keys[keycode] = 1;
    return (0);
}

int key_release(int keycode, t_game *g) {
    if (keycode < 256)
        g->player.keys[keycode] = 0;
    return (0);
}
/*int handle_movement(t_game *g) {


    if (g->player.keys['w'] && is_walkable(g, g->player.x, g->player.y)) 
	{
        move_up_down(g, 0.0, -1.0);
		//minimap_test(g);
    }
    if (g->player.keys['s'] && is_walkable(g, g->player.x, g->player.y)) {
        move_up_down(g, 0.0, 1.0);
		//minimap_test(g);
    }
    if (g->player.keys['a'] && is_walkable(g, g->player.x, g->player.y)) {
        move_up_down(g, -1.0, 0.0);
		//minimap_test(g);
    }
    if (g->player.keys['d'] && is_walkable(g, g->player.x, g->player.y)) {
        move_up_down(g, 1.0, 0.0);
		//minimap_test(g);
    }
	minimap_test(g);

	return (0);
}*/

static int move_forward(t_game *g) {
    float new_x = g->player.x;
    float new_y = g->player.y - MOVESPEED;
    if (is_walkable(g, new_x, new_y)) {
        g->player.x = new_x;
        g->player.y = new_y;
        g->player.dir_vec[0] = 0;
        g->player.dir_vec[1] = -1;
    }
    return 0;
}

static int move_backward(t_game *g) {
    float new_x = g->player.x;
    float new_y = g->player.y + MOVESPEED;
    if (is_walkable(g, new_x, new_y)) {
        g->player.x = new_x;
        g->player.y = new_y;
        g->player.dir_vec[0] = 0;
        g->player.dir_vec[1] = 1;
    }
    return 0;
}

static int move_left(t_game *g) {
    float new_x = g->player.x - MOVESPEED;
    float new_y = g->player.y;
    if (is_walkable(g, new_x, new_y)) {
        g->player.x = new_x;
        g->player.y = new_y;
        g->player.dir_vec[0] = -1;
        g->player.dir_vec[1] = 0;
    }
    return 0;
}

static int move_right(t_game *g) {
    float new_x = g->player.x + MOVESPEED;
    float new_y = g->player.y;
    if (is_walkable(g, new_x, new_y)) {
        g->player.x = new_x;
        g->player.y = new_y;
        g->player.dir_vec[0] = 1;
        g->player.dir_vec[1] = 0;
    }
    return 0;
}

int handle_movement(t_game *g) {
    if (g->player.keys['w']) {
        move_forward(g);
    }
    if (g->player.keys['s']) {
        move_backward(g);
    }
    if (g->player.keys['a']) {
        move_left(g);
    }
    if (g->player.keys['d']) {
        move_right(g);
    }

    minimap_test(g);

    return 0;
}