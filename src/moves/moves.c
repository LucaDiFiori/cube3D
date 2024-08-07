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
/************************PRIMO PASSAGGIO DI NORMINETTATURA******************* */

/**
 * Function: toggle_door
 * -----------------------
 * Toggles the state of a door in the game map. This function changes the 
 * door's state between open ('d') and closed ('D') based on its current 
 * state and its neighboring cells. The function checks the cells adjacent 
 * to the given coordinates to determine and update the door's state.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the map data.
 *  - x: The x-coordinate of the current position.
 *  - y: The y-coordinate of the current position.
 */
static int toggle_door(t_game *g, int x, int y)
{
    if (g->map.map_mat[y + 1][x] == 'D')
        g->map.map_mat[y + 1][x] = 'd';
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
    return (0);
}

/**
 * Function: movements
 * ---------------------
 * Processes player movement based on the current key states. This function
 * checks which movement keys are pressed and calls the appropriate functions 
 * to move the player forward, backward, left, or right.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing player data and key states.
 *
 * Process:
 *  - Checks if the 'w' key is pressed and calls `move_forward()` if true.
 *  - Checks if the 's' key is pressed and calls `move_backward()` if true.
 *  - Checks if the 'a' key is pressed and calls `move_left()` if true.
 *  - Checks if the 'd' key is pressed and calls `move_right()` if true.
 */
static void movements(t_game *g)
{
    if (g->player.keys['w'])
        move_forward(g);
    if (g->player.keys['s'])
        move_backward(g);
    if (g->player.keys['a'])
        move_left(g);
    if (g->player.keys['d'])
        move_right(g);
}
/**
 * Function: rotations
 * ----------------------
 * Processes player rotation based on the current key states for rotating the player.
 * This function updates the rotation direction and calls `rotate_player()` to
 * rotate the player left or right based on the keys pressed.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing player data and key states.
 *  - rotdir: A pointer to an integer that is updated with the rotation direction.
 *
 * Process:
 *  - Checks if the key mapped to the left arrow (position 1) is pressed:
 *    - Sets `*rotdir` to -1 (left rotation) and calls `rotate_player()` with this direction.
 *  - Checks if the key mapped to the right arrow (position 2) is pressed:
 *    - Sets `*rotdir` to 1 (right rotation) and calls `rotate_player()` with this direction.
 */
static void rotations(t_game *g, int *rotdir)
{
    if (g->player.keys[1])
    {
        *rotdir = -1;
        rotate_player(g, *rotdir);
    }
    if (g->player.keys[2])
    {
        *rotdir = 1;
        rotate_player(g, *rotdir);
    }
}

/**
 * Function: handle_movement
 * ---------------------------
 * Manages player movement and interactions based on the current input states.
 * This function handles player movement, rotation, and door toggling.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing player data, key states, and other game data.
 *
 * Process:
 *  - Calls `movements()` to handle player movement based on the key states.
 *  - Calls `rotations()` to handle player rotation and update the rotation direction.
 *  - Checks if the 'e' key is pressed and if the `toggle_door_debounce` flag is not set:
 *    - If true, toggles the door state at the player's current position using `toggle_door()`.
 *    - Sets the `toggle_door_debounce` flag to prevent repeated toggling.
 */
int handle_movement(t_game *g) 
{
    int rotdir;

    movements(g);
    rotations(g, &rotdir);
    if (g->player.keys['e'] && !g->player.toggle_door_debounce) 
    {
        toggle_door(g, (int)g->player.x, (int)g->player.y);
        g->player.toggle_door_debounce = 1;
    }
    return (0);
}
