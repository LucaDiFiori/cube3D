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

void init_img_data(t_game *g, t_img *img, int width, int height)
{
	init_img(img);
	img->img = mlx_new_image(g->mlx.mlx_ptr, width, height);
	if (!img->img)
		quit_and_free(INIT_IMG_ERR, 2, g);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp,
		&img->line_length, &img->endian);
}


/*NOTA: La funzione mlx_get_data_addr è una funzione della libreria MiniLibX 
        che viene utilizzata per ottenere informazioni sull'immagine creata 
		in memoria. Essa restituisce un puntatore all'array di dati 
		dell'immagine che rappresenta i pixel. Questo permette 
		di accedere e manipolare direttamente i pixel dell'immagine.*/

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