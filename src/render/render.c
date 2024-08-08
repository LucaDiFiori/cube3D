/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-24 08:55:27 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-07-24 08:55:27 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"
/**
 * Function: set_pixel_color
 * -------------------------
 * Sets the color of a specific pixel within the frame image's address field 
 * to the color stored in the screen_pixels matrix. This function calculates 
 * the correct index within the image's pixel array and assigns the desired color.
 * 
 * Parameters:
 *  - img: A pointer to the image structure containing the frame data.
 *  - x: The x-coordinate of the pixel to set.
 *  - y: The y-coordinate of the pixel to set.
 *  - color: The color value to assign to the specified pixel.
 *
 * Process:
 *  - Calculates the pixel index within the image's pixel array (`img->addr`) 
 *    using the formula `pixel = y * (img->line_length / 4) + x`.
 *  - `img->line_length / 4` computes the number of pixels per row, assuming 
 *    each pixel occupies 4 bytes.
 *  - Sets the value of the pixel at the calculated index to the provided color.
 */
static void set_pixel_color(t_img *img, int x, int y, int color)
{
	int	pixel;

	pixel = y * (img->line_length / 4) + x;
	img->addr[pixel] = color;
}

/**
 * Function: assign_pixel_color
 * ----------------------------
 * Determines the color of the pixel to be set based on various conditions 
 * and calls `set_pixel_color` to assign the color to the pixel on the image.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the map and screen pixel data.
 *  - img: A pointer to the image structure where the pixel color will be set.
 *  - x: The x-coordinate of the pixel to set.
 *  - y: The y-coordinate of the pixel to set.
 *
 * Process:
 *  - Checks if `g->screen_pixels[y][x]` is greater than 0, indicating a valid 
 *    color for that pixel.
 *    - If true, calls `set_pixel_color` to set the pixel color using `g->screen_pixels[y][x]`.
 *  - If the pixel is in the upper half of the screen (`y < RES_Y / 2`), sets 
 *    the pixel color to `g->map.c_color` (ceiling color).
 *  - If the pixel is in the lower half of the screen (`y < RES_Y - 1`), sets 
 *    the pixel color to `g->map.f_color` (floor color).
 */
static void assign_pixel_color(t_game *g, t_img *img, int x, int y)
{
	if (g->screen_pixels[y][x] > 0)
		set_pixel_color(img, x, y, g->screen_pixels[y][x]);
	else if (y < RES_Y / 2)
		set_pixel_color(img, x, y, g->map.c_color);
	else if (y < RES_Y - 1)
		set_pixel_color(img, x, y, g->map.f_color);
}

/**
 * Function: put_frame_on_screen
 * -----------------------------
 * Prepares and displays the frame image on the game window.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the necessary data.
 *  - img: A pointer to the image structure that holds the frame to be displayed.
 *
 * Process:
 *  - Calls `init_img_data` to initialize the image data with the specified 
 *    dimensions (RES_X and RES_Y). 
 *  - Iterates over each pixel of the image using two nested loops 
 *    (`while y < RES_Y` and `while x < RES_X`).
 *  - For each pixel, calls `assign_pixel_color` to determine and set the color 
 *    of the pixel.
 *  - After setting all the pixels, uses `mlx_put_image_to_window` to display 
 *    the image on the game window.
 *  - Finally, destroys the temporary image using `mlx_destroy_image` to free 
 *    resources (Note: This step is implied but not shown in the provided code).
 */
static void put_frame_on_screen(t_game *g, t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < RES_Y)
	{
		x = 0;
		while (x < RES_X)
		{
			assign_pixel_color(g, &(g->frame), x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(g->mlx.mlx_ptr, g->mlx.win_ptr, img->img, 0, 0);
}

/**
 * Function: render
 * ----------------
 * Renders the game frame by performing raycasting and updating the game window.
 * This function also handles the cleanup and re-initialization of necessary 
 * data structures before drawing the frame and minimap.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the necessary game data.
 *
 * Process:
 *  - Clears the pixel matrix (`screen_pixels`) by calling `clear_matrix`.
 *  - Cleans and reinitializes the raycasting structure using `init_ray` to prepare 
 *    for a new raycasting pass.
 *  - Performs raycasting to calculate the visible scene using `raycasting`.
 *  - Draws the frame on the screen by calling `put_frame_on_screen`.
 *  - Draws the minimap by calling `draw_minimap`.
 */
void render(t_game *g)
{
	clear_matrix(g->screen_pixels);
	init_ray(g);
	raycasting(g);
	put_frame_on_screen(g, &(g->frame));
	draw_minimap(g);
}