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



int key_press(int keycode, t_game *g) {
    if (keycode < 256)
        g->player.keys[keycode] = 1;
    /*NOTA: Ho deciso io arbitrariamente che le posizioni 1 e 2 dell'arrau corrispondano alle frecce*/
    else if (keycode == 65361) // Left arrow key
        g->player.keys[1] = 1;
    else if (keycode == 65363) // Right arrow key
        g->player.keys[2] = 1;

    return (0);
}

int key_release(int keycode, t_game *g) {
    if (keycode < 256)
        g->player.keys[keycode] = 0;
    else if (keycode == 65361) // Left arrow key
        g->player.keys[1] = 0;
    else if (keycode == 65363) // Right arrow key
        g->player.keys[2] = 0;
    if (keycode == 'e')
        g->player.toggle_door_debounce = 0;
    return (0);
}


static int toggle_door(t_game *g, int x, int y)
{
    if (g->map.map_mat[y + 1][x] == 'D')
        g->map.map_mat[y + 1][x] = 'd'; //mi serve una variabile diversa dalla altre tipo "d" altrimenti modificherebbe tutte le posizioni con quella lettera
    else if (g->map.map_mat[y + 1][x] == 'd')
        g->map.map_mat[y + 1][x] = 'D';
    else if (g->map.map_mat[y - 1][x] == 'D')
        g->map.map_mat[y - 1][x] = 'd';
    else if (g->map.map_mat[y - 1][x] == 'd')
        g->map.map_mat[y - 1][x] = 'D';
    else if (g->map.map_mat[y][x + 1] == 'D')
        g->map.map_mat[y][x + 1] = 'd';
    else if (g->map.map_mat[y][x + 1] == 'd')
        g->map.map_mat[y][x + 1] = 'D';
    else if (g->map.map_mat[y][x - 1] == 'D')
        g->map.map_mat[y][x - 1] = 'd';
    else if (g->map.map_mat[y][x - 1] == 'd')
        g->map.map_mat[y][x - 1] = 'D';
    return 0;
}


void handle_input(t_game *g)
{
	mlx_hook(g->mlx.win_ptr, 17, 0, *ft_close_x, g);
	mlx_hook(g->mlx.win_ptr, 2, 1L<<0, key_press, g);
	mlx_hook(g->mlx.win_ptr, 3, 1L<<1, key_release, g);
}



int handle_movement(t_game *g) 
{
    int rotdir;


    if (g->player.keys['w'])
        move_forward(g);
    if (g->player.keys['s'])
        move_backward(g);
    if (g->player.keys['a'])
        move_left(g);
    if (g->player.keys['d'])
        move_right(g);
    if (g->player.keys[1])
    {
        rotdir = -1;
        rotate_player(g, rotdir);
    }
    if (g->player.keys[2])
    {
        rotdir = 1;
        rotate_player(g, rotdir);
    }
    /*if (g->player.keys['e'])
        toggle_door(g, (int)g->player.x, (int)g->player.y);*/
    if (g->player.keys['e'] && !g->player.toggle_door_debounce) {
        toggle_door(g, (int)g->player.x, (int)g->player.y);
        g->player.toggle_door_debounce = 1; // Imposta il debounce dopo l'azione
    }


    return 0;
}
