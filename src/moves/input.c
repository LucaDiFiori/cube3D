/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 10:10:53 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-08-07 10:10:53 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"
/************************PRIMO PASSAGGIO DI NORMINETTATURA******************* */

/**
 * Function: key_press
 * ---------------------
 * Handles key press events by updating the state of the keys array in the
 * game structure. This function sets the appropriate key states when specific
 * keys are pressed, including arrow keys and the ESC key.
 * 
 * Parameters:
 *  - keycode: The code of the key that was pressed.
 *  - g: A pointer to the game structure containing player data and key states.
 *
 * Process:
 *  - Checks if the `keycode` is less than 256, indicating a standard ASCII key.
 *    - Updates the `keys` array in the `player` structure to mark the key as pressed.
 *  - For non-ASCII keys:
 *    - Sets the `keys` array entry corresponding to the left arrow key (keycode 65361) to 1.
 *    - Sets the `keys` array entry corresponding to the right arrow key (keycode 65363) to 1.
 *    - Calls `ft_close_x()` to close the game if the ESC key (keycode 65307) is pressed.
 *  - Note: The assignment of array positions 1 and 2 to represent the left and right arrow keys
 *    was an arbitrary decision.
 */
int key_press(int keycode, t_game *g) 
{
    if (keycode < 256)
        g->player.keys[keycode] = 1;
    else if (keycode == 65361)
        g->player.keys[1] = 1;
    else if (keycode == 65363)
        g->player.keys[2] = 1;
	else if (keycode == 65307)
		ft_close_x(g);
    return (0);
}

/**
 * Function: key_release
 * -----------------------
 * Handles key release events by updating the state of the keys array in the
 * game structure. This function resets the appropriate key states when specific
 * keys are released, including arrow keys and the 'e' key.
 * 
 * Parameters:
 *  - keycode: The code of the key that was released.
 *  - g: A pointer to the game structure containing player data and key states.
 * 
 * Process:
 *  - Checks if the `keycode` is less than 256, indicating a standard ASCII key.
 *    - Updates the `keys` array in the `player` structure to mark the key as released.
 *  - For non-ASCII keys:
 *    - Resets the `keys` array entry corresponding to the left arrow key (keycode 65361) to 0.
 *    - Resets the `keys` array entry corresponding to the right arrow key (keycode 65363) to 0.
 *    - Resets the `toggle_door_debounce` flag in the `player` structure to 0 if the 'e' key is released.
 */
int key_release(int keycode, t_game *g) {
    if (keycode < 256)
        g->player.keys[keycode] = 0;
    else if (keycode == 65361)
        g->player.keys[1] = 0;
    else if (keycode == 65363)
        g->player.keys[2] = 0;
    if (keycode == 'e')
        g->player.toggle_door_debounce = 0;
    return (0);
}


/**
 * Function: check_mouse_pos
 * ---------------------------
 * Manages the mouse position to prevent it from getting too close to the edges 
 * of the game screen. When the mouse cursor approaches the right or left edge 
 * of the screen, it is repositioned to a specified distance from the edge to keep 
 * it within the visible area.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the MLX instance and window.
 *  - x: The current x-coordinate of the mouse cursor.
 *  - y: The current y-coordinate of the mouse cursor.
 *
 * Process:
 *  - Checks if the mouse cursor is within 20 pixels of the right edge of the screen (`RES_X`):
 *    - If so, repositions the cursor to be exactly 20 pixels from the right edge.
 *  - Checks if the mouse cursor is within 20 pixels of the left edge of the screen:
 *    - If so, repositions the cursor to be exactly 20 pixels from the left edge.
 *  - Uses `mlx_mouse_move` to move the cursor to the adjusted coordinates if necessary.
 * 
 * Note: The threshold of 20 pixels from the screen edges ensures that the cursor is kept 
 *       within the visible bounds, providing a smoother user experience and preventing 
 *       the cursor from exiting the screen area.
 */
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
/**
 * Function: mouse_input
 * -----------------------
 * Handles mouse movement input to rotate the player based on the horizontal 
 * movement of the mouse. This function adjusts the player's orientation 
 * depending on whether the mouse has moved to the left or right.
 * 
 * Parameters:
 *  - x: The current x-coordinate of the mouse cursor.
 *  - y: The current y-coordinate of the mouse cursor.
 *  - g: A pointer to the game structure containing player data and mouse state.
 *
 * Process:
 *  - Calls `check_mouse_pos()` to ensure the mouse cursor is within the visible bounds of the screen.
 *  - Compares the current x-coordinate (`x`) with the previously stored mouse position (`g->mouse_pos`):
 *    - If `x` is less than `g->mouse_pos`, it rotates the player to the left by calling `rotate_player(g, -1)`.
 *    - If `x` is greater than `g->mouse_pos`, it rotates the player to the right by calling `rotate_player(g, 1)`.
 *    - If `x` is equal to `g->mouse_pos`, no rotation is performed.
 *  - Updates `g->mouse_pos` to the current x-coordinate (`x`) for future comparisons.
 */
int	mouse_input(int x, int y, t_game *g)
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

/**
 * Function: handle_input
 * ------------------------
 * Registers event handlers for various types of input events in the game window. 
 * This function sets up callbacks for handling window close events, key presses, 
 * key releases, and mouse movements.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the MLX instance and window data.
 *
 * Process:
 *  - Registers the `ft_close_x` function to handle window close events (event type 17).
 *  - Registers the `key_press` function to handle key press events (event type 2).
 *  - Registers the `key_release` function to handle key release events (event type 3).
 *  - Registers the `mouse_input` function to handle mouse movement events (event type MotionNotify).
 * 
 * Note: The event masks and event types used are specific to the MLX library and 
 *       ensure that the appropriate functions are called in response to user input.
 */
void handle_input(t_game *g)
{
	mlx_hook(g->mlx.win_ptr, 17, 0, ft_close_x, g);
	mlx_hook(g->mlx.win_ptr, 2, 1L<<0, key_press, g);
	mlx_hook(g->mlx.win_ptr, 3, 1L<<1, key_release, g);
	mlx_hook(g->mlx.win_ptr, MotionNotify, PointerMotionMask, mouse_input, g);
}