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

/*questa funzione estrae i valori interi (pixell) dall'immagine della texture */
/*questa funzione estrae i valori interi (pixell) dall'immagine della texture */
static int *extract_pixels_from_xpm(t_game *g, char *text_path)
{
    t_img tmp;
    int *pixels;


    // Inizializzazione dell'immagine della texture
    init_texture(g, &tmp, text_path);

    // Allocazione del buffer
    pixels = ft_calloc(1, sizeof(int) * (TEXT_WIDTH * TEXT_HEIGHT));
    if (!pixels)
        quit_and_free(MALLOC_ERR, 2, g);

    // Copia dei dati dell'immagine nel buffer
    if (!ft_memcpy(pixels, tmp.addr, sizeof(int) * (TEXT_WIDTH * TEXT_HEIGHT)))
        quit_and_free(MEMCPY_ERR, 2, g);

    // Distruzione dell'immagine temporanea
    mlx_destroy_image(g->mlx.mlx_ptr, tmp.img);

    return pixels;
}



/*questa funzione riempie l'array wall pixels con l'array di interi restituito da extract_pixels_from_xpm
  Scopo: Caricare e inizializzare le texture dai file XPM all'inizio del gioco.*/
void    init_textures_mat(t_game *g)
{
	g->map.text.wall_pixels[0] = extract_pixels_from_xpm(g, g->map.text.north);
	g->map.text.wall_pixels[1] = extract_pixels_from_xpm(g, g->map.text.south);
	g->map.text.wall_pixels[2] = extract_pixels_from_xpm(g, g->map.text.east);
	g->map.text.wall_pixels[3] = extract_pixels_from_xpm(g, g->map.text.west);
	g->map.text.wall_pixels[4] = NULL;
}