/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_engine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-24 09:04:55 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-07-24 09:04:55 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"
/************************PRIMO PASSAGGIO DI NORMINETTATURA******************* */

int init_engine(t_game *g_s)
{
	g_s->mlx.mlx_ptr = mlx_init();
	if (!g_s->mlx.mlx_ptr)
		return (0);
	g_s->mlx.win_ptr = mlx_new_window(g_s->mlx.mlx_ptr, RES_X, RES_Y, "cub3D");
	if (!g_s->mlx.win_ptr)
		return (0);
	return (1);
}

void init_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_length = 0;
	img->endian = 0;
	img->width = TEXT_WIDTH;
	img->height = TEXT_HEIGHT;
}

/**
 * Function: init_img_data
 * -----------------------
 * Initializes an image structure for use in the game, setting up the image
 * buffer and its associated properties. This function creates a new image
 * using the MLX library, retrieves its data address, and stores it in the 
 * image structure.
 *
 * Parameters:
 *  - g: A pointer to the game structure containing the MLX instance and other game data.
 *  - img: A pointer to the image structure to be initialized.
 *  - width: The width of the image to be created.
 *  - height: The height of the image to be created.
 *
 * Process:
 *  - Calls init_img() to initialize the image structure.
 *  - Creates a new image using mlx_new_image() with the specified width and height.
 *  - Checks if the image creation was successful; if not, calls quit_and_free() to handle the error.
 *  - Retrieves the data address of the image using mlx_get_data_addr() and stores it in the image structure.
 */
void init_img_data(t_game *g, t_img *img, int width, int height)
{
	init_img(img);
	img->img = mlx_new_image(g->mlx.mlx_ptr, width, height);
	if (!img->img)
		quit_and_free(INIT_IMG_ERR, 2, g);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp,
		&img->line_length, &img->endian);
}


/* 
 * NOTE: The function mlx_get_data_addr is a function from the MiniLibX library
 *       that is used to obtain information about the image created in memory. 
 *       It returns a pointer to the image data array that represents the pixels. 
 *       This allows direct access and manipulation of the image's pixels.
 */

/**
 * Function: init_texture
 * ----------------------
 * Initializes a texture image from a file for use in the game, setting up the 
 * image buffer and its associated properties. This function loads an XPM image
 * file using the MLX library, retrieves its data address, and stores it in the 
 * image structure.
 *
 * Parameters:
 *  - g: A pointer to the game structure containing the MLX instance and other game data.
 *  - img: A pointer to the image structure to be initialized.
 *  - path: The file path to the XPM image file to be loaded.
 *
 * Process:
 *  - Calls init_img() to initialize the image structure.
 *  - Loads the XPM image file using mlx_xpm_file_to_image() with the specified path.
 *  - Checks if the image loading was successful; if not, calls quit_and_free() to handle the error.
 *  - Retrieves the data address of the image using mlx_get_data_addr() and stores it in the image structure.
 */
void init_texture(t_game *g, t_img *img, char *path)
{
	init_img(img);
	img->img = mlx_xpm_file_to_image(g->mlx.mlx_ptr, path,
		&img->width, &img->height);
	if (!img->img)
		quit_and_free(INIT_IMG_ERR, 2, g);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp,
		&img->line_length, &img->endian);
}

void init_fps_counter(t_game *g)
{
	init_img_data(g, &g->fps, 100, 100);
}