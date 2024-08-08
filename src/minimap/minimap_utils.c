/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 09:03:36 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-08-07 09:03:36 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"


/**
 * Function: my_pixel_put
 * ----------------------
 * Sets a pixel on the minimap image buffer to a specified color. This function ensures
 * that the pixel coordinates are within the bounds of the minimap before attempting
 * to set the pixel color.
 *
 * Parameters:
 *  - g: A pointer to the game structure containing the minimap properties and image buffer.
 *  - x: The x-coordinate of the pixel on the minimap.
 *  - y: The y-coordinate of the pixel on the minimap.
 *  - color: The color to set the pixel to (as an integer value).
 *
 * Process:
 *  - Checks if the pixel coordinates (x, y) are within the bounds of the minimap dimensions.
 *  - If the coordinates are valid, calculates the address of the pixel in the image buffer.
 *  - Sets the pixel at the calculated address to the specified color.
 */
void my_pixel_put(t_game *g, int x, int y, int color)
{
    int *dst;

    if (x >= 0 && x < g->minimap.minimap_width && y >= 0 &&
        y < g->minimap.minimap_height)
    {
        dst = g->minimap.img_bg.addr + \
            (y * (g->minimap.img_bg.line_length / sizeof(int))) + x;
        *dst = color;
    }
}

/**
 * Function: fill_background
 * -------------------------
 * Fills the background of the minimap with a specified color. This function iterates 
 * over each pixel within the given width and height dimensions and sets it to the 
 * background color using the my_pixel_put function.
 *
 * Parameters:
 *  - g: A pointer to the game structure containing the minimap properties and image buffer.
 *  - width: The width of the area to be filled.
 *  - height: The height of the area to be filled.
 *  - background_color: The color to fill the background with (as an integer value).
 *
 * Process:
 *  - Iterates over each pixel row (y-axis) up to the specified height.
 *  - For each row, iterates over each pixel column (x-axis) up to the specified width.
 *  - Calls my_pixel_put() to set the color of each pixel to the background color.
 */
void fill_background(t_game *g, int width, int height, int background_color)
{
    int y;

    y = 0;
    while (y < height)
    {
        int x = 0;
        while (x < width)
        {
            my_pixel_put(g, x, y, background_color);
            x++;
        }
        y++;
    }
}

/**
 * Function: draw_square
 * ---------------------
 * Draws a white square on the minimap at the specified starting coordinates. 
 * This function iterates over each pixel within the bounds of the square's 
 * dimensions and sets it to white using the my_pixel_put function.
 *
 * Parameters:
 *  - g: A pointer to the game structure containing the minimap properties and image buffer.
 *  - start_x: The x-coordinate where the square starts on the minimap.
 *  - start_y: The y-coordinate where the square starts on the minimap.
 *
 * Process:
 *  - Converts the starting x and y coordinates to integers.
 *  - Iterates over each pixel row (y-axis) within the square's height.
 *  - For each row, iterates over each pixel column (x-axis) within the square's width.
 *  - Calls my_pixel_put() to set the color of each pixel to white (0xFFFFFF).
 */
void draw_square(t_game *g, double start_x, double start_y) 
{
    int x;
    int y;

    x = (int)start_x;
    while (x < start_x + g->minimap.cell_width - 1) 
    {
        y = (int)start_y;
        while (y < start_y + g->minimap.cell_height - 1) 
        {
            my_pixel_put(g, x, y, 0xFFFFFF);
            y++;
        }
        x++;
    }
}

//same as draw_square but with a different color
void draw_door(t_game *g, double start_x, double start_y) 
{
    int x;
    int y;

    x = (int)start_x;
    while (x < start_x + g->minimap.cell_width - 1) 
    {
        y = (int)start_y;
        while (y < start_y + g->minimap.cell_height - 1) 
        {
            my_pixel_put(g, x, y, 0x00FFFF);
            y++;
        }
        x++;
    }
}

/**
 * Function: draw_circle
 * ---------------------
 * Draws a circle on the minimap at the specified center coordinates with a given color.
 * This function uses the midpoint circle algorithm to determine which pixels fall within
 * the circle's radius and sets them to the specified color using the my_pixel_put function.
 *
 * Parameters:
 *  - g: A pointer to the game structure containing the minimap properties and image buffer.
 *  - center_x: The x-coordinate of the circle's center on the minimap.
 *  - center_y: The y-coordinate of the circle's center on the minimap.
 *  - color: The color to set the circle's pixels to (as an integer value).
 *
 * Process:
 *  - Iterates over a square bounding box centered at (center_x, center_y) with side length 
 *    equal to the circle's diameter.
 *  - For each pixel within the bounding box, checks if it lies within the circle's radius 
 *    using the circle equation (x - center_x)^2 + (y - center_y)^2 <= radius^2.
 *  - Calls my_pixel_put() to set the color of each pixel that lies within the circle's radius.
 */
void draw_circle(t_game *g, double center_x, double center_y, int color) 
{
    double  x;
    double  y;

    x = center_x - g->minimap.player_radius;
    while (x <= center_x + g->minimap.player_radius) 
    {
        y = center_y - g->minimap.player_radius;
        while (y <= center_y + g->minimap.player_radius) 
        {
            if ((x - center_x) * (x - center_x) + (y - center_y)* (y - center_y)
                <= g->minimap.player_radius * g->minimap.player_radius) 
            {
                my_pixel_put(g, (int)x, (int)y, color);
            }
            y++;
        }
        x++;
    }
}
