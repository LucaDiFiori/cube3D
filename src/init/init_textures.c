/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-25 14:10:36 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-07-25 14:10:36 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"


/**
 * Function: extract_pixels_from_xpm
 * ---------------------------------
 * Extracts integer pixel values from a texture image file (XPM format) and stores
 * them in a dynamically allocated buffer. This function initializes the texture 
 * image, copies its pixel data to a buffer, and then destroys the temporary image.
 *
 * Parameters:
 *  - g: A pointer to the game structure containing the MLX instance and other game data.
 *  - text_path: The file path to the XPM texture image to be loaded.
 *
 * Returns:
 *  - A pointer to the dynamically allocated buffer containing the pixel values.
 *    The caller is responsible for freeing this buffer.
 *
 * Process:
 *  - Initializes the texture image using init_texture().
 *  - Allocates a buffer to hold the pixel data.
 *  - Copies the pixel data from the texture image to the buffer using ft_memcpy().
 *  - Destroys the temporary texture image using mlx_destroy_image().
 *  - Returns the pointer to the buffer containing the pixel data.
 */
static int *extract_pixels_from_xpm(t_game *g, char *text_path)
{
    t_img   tmp;
    int     *pixels;

    init_texture(g, &tmp, text_path);
    pixels = ft_calloc(1, sizeof(int) * (TEXT_WIDTH * TEXT_HEIGHT));
    if (!pixels)
        quit_and_free(MALLOC_ERR, 2, g);
    if (!ft_memcpy(pixels, tmp.addr, sizeof(int) * (TEXT_WIDTH * TEXT_HEIGHT)))
        quit_and_free(MEMCPY_ERR, 2, g);
    mlx_destroy_image(g->mlx.mlx_ptr, tmp.img);
    return (pixels);
}

/**
 * Function: init_textures_mat
 * ---------------------------
 * Fills the wall_pixels array with integer arrays returned by extract_pixels_from_xpm.
 * Purpose: Load and initialize textures from XPM files at the start of the game.
 *
 * Parameters:
 *  - g: A pointer to the game structure containing the map and texture data.
 *
 * Process:
 *  - Calls extract_pixels_from_xpm() for each texture path (north, south, east, west, 
 *    door, and door open) and assigns the returned pixel arrays to the corresponding
 *    elements of the wall_pixels array.
 *  - Sets the last element of the wall_pixels array to NULL.
 */
void    init_textures_mat(t_game *g)
{
	g->map.text.wall_pixels[0] = extract_pixels_from_xpm(g, g->map.text.north);
	g->map.text.wall_pixels[1] = extract_pixels_from_xpm(g, g->map.text.south);
	g->map.text.wall_pixels[2] = extract_pixels_from_xpm(g, g->map.text.east);
	g->map.text.wall_pixels[3] = extract_pixels_from_xpm(g, g->map.text.west);
    g->map.text.wall_pixels[4] = extract_pixels_from_xpm(g, DOOR_PATH);
	g->map.text.wall_pixels[5] = extract_pixels_from_xpm(g, DOOR_OPEN_PATH);
    g->map.text.wall_pixels[6] = NULL;
}