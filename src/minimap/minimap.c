/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 09:03:48 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-08-07 09:03:48 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"
/**
 * Function: draw_map
 * ------------------
 * Renders the map on the screen by iterating through the map matrix and drawing
 * each cell based on its type. The map is represented by a 2D array where each cell
 * contains a character indicating its type (e.g., door, wall, etc.). This function
 * calculates the position and size of each cell to be drawn on the minimap, and 
 * calls the appropriate drawing function to render it with a grid effect.
 *
 * Parameters:
 *  - g: A pointer to the game structure containing the map data and minimap properties.
 *
 * Process:
 *  - Iterates through each row and column of the map matrix.
 *  - For each cell, calculates its position on the minimap using the cell width and height.
 *  - Checks the cell type:
 *    - If the cell contains 'D' or 'd', it calls draw_door() to render a door.
 *    - If the cell contains '1', it calls draw_square() to render a wall.
 *  - The cell width and height are decremented by 1 to create a grid effect on the minimap.
 */
void draw_map(t_game *g) 
{
    int y;
    int x;
    double  map_x;
    double  map_y;

    y = 0;
    while (y < g->map.map_y) 
    {
        int row_length = ft_strlen(g->map.map_mat[y]);
        x = 0;
        while (x < row_length) 
        {
            map_x = x * g->minimap.cell_width;
            map_y = y * g->minimap.cell_height;
            if (g->map.map_mat[y][x] == 'D' || g->map.map_mat[y][x] == 'd') // door
                draw_door(g, map_x, map_y); // -1 for grid effect on the minimap
            else if (g->map.map_mat[y][x] == '1') // wall
                draw_square(g, map_x, map_y); // -1 for grid effect on the minimap
            x++;
        }
        y++;
    }
}

//initialize the minimap img
void init_minimap(t_game *g)
{
    init_img_data(g, &g->minimap.img_bg, g->minimap.minimap_width, g->minimap.minimap_height);
    g->minimap.cell_height = (double) g->minimap.minimap_height / g->map.map_y;
    g->minimap.cell_width = (double) g->minimap.minimap_width / g->map.map_x;
    g->minimap.player_radius = g->minimap.cell_width / 3;
}

/**
 * Function: draw_player
 * ---------------------
 * Draws a green circle on the minimap to represent the player's position.
 * 
 * Parameters:
 *  - g: A pointer to the game structure containing the minimap properties and image buffer.
 *  - x: The player's x-coordinate on the map (relative to the map matrix).
 *  - y: The player's y-coordinate on the map (relative to the map matrix).
 *
 * Process:
 *  - Calculates the player's position on the minimap by scaling the map coordinates
 *    according to the minimap cell dimensions.
 *  - Determines the radius of the circle representing the player, which is set to 
 *    one-third of the minimap cell width.
 *  - Calls draw_circle() to render the circle on the minimap image buffer with a green color.
 */
void draw_player(t_game *g, double x, double y) 
{
    // Calculate the player's position on the minimap
    double player_x;
    double player_y;

    player_x = x * g->minimap.cell_width;
    player_y = y * g->minimap.cell_height;
    draw_circle(g, player_x, player_y, 0x00FF00); // Green color
}


// Draw the minimap on the screen
void draw_minimap(t_game *g) {
    fill_background(g, g->minimap.minimap_width, g->minimap.minimap_height, 0x404040);    
    draw_map(g);
    draw_player(g, g->player.x, g->player.y);
    mlx_put_image_to_window(g->mlx.mlx_ptr, g->mlx.win_ptr, g->minimap.img_bg.img, RES_X - g->minimap.minimap_width, 0);
}
