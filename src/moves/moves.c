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




// Questa funzione serve a gestire la posizione del mouse per evitare che esca 
// fuori dallo schermo del gioco. Quando il mouse si avvicina troppo al bordo destro 
// o sinistro dello schermo, la posizione del mouse viene "avvolta" (wrapped) all'altro lato.
//
// - Controllo del bordo destro: Se il cursore del mouse supera RES_X - 20, 
//                               viene riportato a RES_X - 20 pixel dal bordo.
// - Controllo del bordo sinistro: Se il cursore del mouse è meno di 20 pixel dal 
//                                bordo sinistro, viene riportato a 20 
//                                pixel dal bordo .
// - mlx_mouse_move: Questa funzione della libreria MLX sposta il cursore 
//                   del mouse alla posizione specificata.

static void	check_mouse_pos(t_game *g, int x, int y)
{
	if (x > RES_X - 20)
	{
		x = RES_X - 20;
		mlx_mouse_move(g->mlx.mlx_ptr, g->mlx.win_ptr, x, y);
	}
	if (x < 20)
	{
		x = 20;
		mlx_mouse_move(g->mlx.mlx_ptr, g->mlx.win_ptr, x, y);
	}
}

static int	mouse(int x, int y, t_game *g)
{
	check_mouse_pos(g, x, y);
	if (x == g->mouse_pos)
		return (0);
	else if (x < g->mouse_pos)
		rotate_player(g, -1);
	else if (x > g->mouse_pos)
		rotate_player(g, 1);
	g->mouse_pos = x;
	return (0);
}





void handle_input(t_game *g)
{
	mlx_hook(g->mlx.win_ptr, 17, 0, *ft_close_x, g);
	mlx_hook(g->mlx.win_ptr, 2, 1L<<0, key_press, g);
	mlx_hook(g->mlx.win_ptr, 3, 1L<<1, key_release, g);
    mlx_hook(g->mlx.win_ptr, MotionNotify, PointerMotionMask,
			mouse, g);
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
