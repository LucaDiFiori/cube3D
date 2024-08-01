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
/*Questa funzione imposta il colore di un pixel specifico all'interno del campo
  addr dell'immagine del frame impostandolo al colore salvato nella matrice screen_pixels
- Calcola l'indice del pixel all'interno dell'array di pixel dell'immagine (img->addr) 
  utilizzando la formula pixel = y * (img->line_length / 4) + x.
- img->line_length / 4 calcola il numero di pixel per riga (presumendo che ogni pixel occupi 4 byte).
- Imposta il valore del pixel all'indice calcolato con il colore fornito.*/
static void set_pixel_color(t_img *img, int x, int y, int color)
{
	int pixel;

	pixel = y * (img->line_length / 4) + x;
	img->addr[pixel] = color;
}

/*Questa funzione decide il colore del pixel da assegnare in base a diverse condizioni 
  e chiama set_pixel_color per impostare il colore del pixel sull'immagine.
  - Controlla se g->screen_pixels[y][x] è maggiore di 0, il che indica che c'è 
    un colore valido per quel pixel.
    -Se sì, chiama set_pixel_color per impostare il colore del pixel 
	 usando g->screen_pixels[y][x].
  - Se il pixel si trova nella metà superiore dello schermo (y < RES_Y / 2), 
    imposta il colore del pixel a g->map.c_color (che rappresenta il colore 
	del soffitto).
  - Se il pixel si trova nella metà inferiore dello schermo (y < RES_Y - 1), 
    imposta il colore del pixel a g->map.f_color (che rappresenta il colore 
	del pavimento).*/
static void assign_pixel_color(t_game *g, t_img *img, int x, int y)
{
	if (g->screen_pixels[y][x] > 0)
		set_pixel_color(img, x, y, g->screen_pixels[y][x]);
	else if (y < RES_Y / 2)
		set_pixel_color(img, x, y, g->map.c_color);
	else if (y < RES_Y - 1)
		set_pixel_color(img, x, y, g->map.f_color);
}

/*Questa funzione prepara e visualizza l'immagine del frame sulla finestra del gioco.
  - Chiama init_img_data per inizializzare i dati dell'immagine con le dimensioni 
    specificate (RES_X e RES_Y).
  - Scorre ogni pixel dell'immagine usando due cicli annidati 
    (while y < RES_Y e while x < RES_X).
  - Per ogni pixel, chiama assign_pixel_color per determinare e impostare il 
    colore del pixel.
  - Dopo aver impostato tutti i pixel, usa mlx_put_image_to_window per visualizzare 
    l'immagine sulla finestra del gioco.
  - Infine, distrugge l'immagine temporanea utilizzando mlx_destroy_image per 
    liberare risorse.*/
static void put_frame_on_screen(t_game *g, t_img *img)
{
	int x;
	int y;

	//init_img_data(g, img, RES_X, RES_Y); //-> questa non la posso chiamare qui in un
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
	//mlx_destroy_image(g->mlx.mlx_ptr, img->img);
}


//ricordarsi di deallocare screen_pixels 
void render(t_game *g)
{
	//pulisco la matrice dei pixels
	clear_matrix(g->screen_pixels);


	//pulisco la struct del raycasting (per riaggiornarla)
	init_ray(g);
	//raycasting
	raycasting(g);
	

	//disegno la mappa
	put_frame_on_screen(g, &(g->frame));
	
	
	draw_minimap(g);

}