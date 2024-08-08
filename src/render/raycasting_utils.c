/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-24 09:01:14 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-07-24 09:01:14 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"
/**
 * Function: find_wall_side
 * -------------------------
 * Determines which side of the wall the ray has hit and sets the corresponding 
 * texture side in the game map structure. This function helps in selecting the 
 * appropriate texture for rendering the wall segment based on the ray's direction.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the necessary game data.
 *
 * Process:
 *  - Checks the value of `g->ray.side` to determine if the ray hit a vertical or 
 *    horizontal wall.
 *    - If `g->ray.side` is 0 (vertical wall):
 *      - If `g->ray.dir_x` is less than 0, the ray hit the west side of the wall.
 *      - Otherwise, the ray hit the east side of the wall.
 *    - If `g->ray.side` is 1 (horizontal wall):
 *      - If `g->ray.dir_y` is greater than 0, the ray hit the south side of the wall.
 *      - Otherwise, the ray hit the north side of the wall.
 *  - Sets the appropriate wall side texture in `g->map.text.wall_side` based on 
 *    the direction of the ray and the side of the wall hit.
 */
void find_wall_side(t_game *g)
{
	if (g->ray.side == 0)
	{
		if (g->ray.dir_x < 0)
			g->map.text.wall_side = WEST;
		else
			g->map.text.wall_side = EAST;
	}
	else
	{
		if (g->ray.dir_y > 0)
			g->map.text.wall_side = SOUTH;
		else
			g->map.text.wall_side = NORTH;
	}
}

/**
 * Function: calculate_texture_x
 * ------------------------------
 * Calculates the x-coordinate of the texture column to be sampled based on the 
 * impact point of the ray on the wall. This function also handles special cases 
 * where the ray hits a door or an open door.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the necessary game data.
 *
 * Process:
 *  - Checks the type of object hit by the ray (`hit_type`):
 *    - If the ray hit a door (`hit_type` is 2), sets the texture side to `DOOR`.
 *    - If the ray hit an open door (`hit_type` is 3), sets the texture side to `DOOROPEN`.
 *    - Otherwise, calls `find_wall_side` to determine the normal wall side for texture mapping.
 *  - Calculates the x-coordinate of the texture column (`column_x`) based on the 
 *    fractional part of the wall impact position (`wall_x`):
 *    - Multiplies `wall_x` by the texture width (`TEXT_WIDTH`) to get the column index.
 *    - Adjusts `column_x` if the ray hit a wall on the west side or south side:
 *      - For vertical walls hit from the left, or horizontal walls hit from below, 
 *        the column index is adjusted to sample the opposite side of the texture.
 */
static void calculate_texture_x(t_game *g)
{
	if (g->ray.hit_type == 2)
        g->map.text.wall_side = DOOR;
	else if (g->ray.hit_type == 3)
		g->map.text.wall_side = DOOROPEN;
    else
        find_wall_side(g);
    g->map.text.column_x = (int)(g->ray.wall_x * TEXT_WIDTH);
    if ((g->ray.side == 0 && g->ray.dir_x < 0)
		|| (g->ray.side == 1 && g->ray.dir_y > 0))
        g->map.text.column_x = TEXT_WIDTH - g->map.text.column_x - 1;
}

/**
 * Function: calculate_texture_step_and_initial_position
 * -------------------------------------------------------
 * Computes the vertical step size for texture mapping and the initial texture 
 * position for rendering a wall column. This function helps in correctly scaling 
 * and positioning the texture on the wall slice based on its height and the 
 * drawing area on the screen.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the necessary game data.
 *
 * Process:
 *  - Calculates the vertical step size for texture mapping (`vertical_step`):
 *    - This represents how much to move vertically through the texture for each 
 *      pixel of the wall column, based on the height of the column to be drawn 
 *      (`line_height`) and the height of the texture (`TEXT_HEIGHT`).
 *  - Computes the initial position in the texture (`current_tex_y`):
 *    - This position is determined by the vertical offset from the center of the 
 *      screen to the top of the wall column, scaled by `vertical_step`.
 *    - The formula used is based on the difference between the start of the drawing 
 *      area (`draw_start`) and the screen center, adjusted for the height of the 
 *      wall column and multiplied by `vertical_step`.
 */
static void calculate_texture_step_and_initial_position(t_game *g)
{
    g->map.text.vertical_step = (double)TEXT_HEIGHT / g->ray.line_height;
    g->map.text.current_tex_y = (g->ray.draw_start - RES_Y / 2 \
        + g->ray.line_height / 2) * g->map.text.vertical_step;
}

/**
 * Function: update_screen_pixels
 * -------------------------------
 * Updates the pixels of the current column on the screen based on texture data 
 * and raycasting results. This function applies texture mapping to render the wall 
 * segment accurately, including shading effects for different wall sides.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the necessary game data.
 *  - x: The x-coordinate of the column on the screen to update.
 *
 * Process:
 *  - Iterates over each pixel in the column from the start to the end of the wall slice:
 *    - Uses `g->ray.draw_start` and `g->ray.draw_end` to define the vertical range of the wall column.
 *    - Calculates the y-coordinate on the texture (`column_y`) based on the current texture position (`current_tex_y`):
 *      - Ensures `column_y` is within the texture bounds, clamping it if necessary.
 *    - Increments `current_tex_y` by `vertical_step` to move to the next texture row for the next pixel.
 *    - Extracts the color from the texture using the calculated `column_y` and the x-coordinate (`column_x`):
 *      - If the wall side is north or east, applies shading to the color to simulate lighting effects.
 *    - If the color is not transparent (`color > 0`), updates the corresponding pixel in `g->screen_pixels`.
 *  - Continues until all pixels in the wall column are processed.
 */
static void update_screen_pixels(t_game *g, int x)
{
    int	y;
    int	color;

	y = g->ray.draw_start;
    while (y < g->ray.draw_end)
    {
        g->map.text.column_y = (int)g->map.text.current_tex_y;
        if (g->map.text.column_y >= TEXT_HEIGHT)
            g->map.text.column_y = TEXT_HEIGHT - 1;
        else if(g->map.text.column_y < 0)
            g->map.text.column_y = 0;
        g->map.text.current_tex_y += g->map.text.vertical_step;
        color = g->map.text.wall_pixels[g->map.text.wall_side] \
            [TEXT_HEIGHT * g->map.text.column_y \
            + g->map.text.column_x];
        if (g->map.text.wall_side == NORTH || g->map.text.wall_side == EAST)
            color = (color >> 1) & 8355711;
        if (color > 0)
            g->screen_pixels[y][x] = color;
        y++;
    }
}

/**
 * Function: draw_screen_pixels
 * -----------------------------
 * Draws the pixels for the current column on the screen by applying texture 
 * mapping based on the raycasting results. This function coordinates the 
 * calculation of texture position and step size, and updates the screen pixels 
 * accordingly.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the necessary game data.
 *  - x: The x-coordinate of the column on the screen to be drawn.
 *
 * Process:
 *  - Calls `calculate_texture_x` to determine the correct texture column to sample 
 *    and handle special cases such as doors or open doors.
 *  - Calls `calculate_texture_step_and_initial_position` to compute the vertical 
 *    step size for texture mapping and the initial texture position for the column.
 *  - Calls `update_screen_pixels` to update the pixel data of the specified column 
 *    on the screen based on the texture mapping calculations and shading effects.
 */
void draw_screen_pixels(t_game *g, int x)
{
    calculate_texture_x(g);
    calculate_texture_step_and_initial_position(g);
    update_screen_pixels(g, x);
}