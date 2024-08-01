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


/*La funzione aggiorna i pixel di una texture su una colonna 
dell'immagine di gioco basandosi sul risultato del raycasting.*/






//Funzione per trovare il lato del muro e calcolare la coordinata x della texture
	// Calcolare la coordinata x della texture:
	// - ray->wall_x rappresenta la posizione esatta dove il raggio colpisce la 
	//   parete (tra 0 e 1).
	// - Questa posizione viene scalata dalla dimensione della texture per 
	//   ottenere la coordinata x sulla texture.
	// - Se il raggio ha colpito da una certa direzione, viene applicato un 
	//   mirroring orizzontale per ottenere il lato corretto della texture.
static void calculate_texture_x(t_game *g)
{
    find_wall_side(g);

    g->map.text.column_x = (int)(g->ray.wall_x * TEXT_WIDTH);
    if ((g->ray.side == 0 && g->ray.dir_x < 0) || (g->ray.side == 1 && g->ray.dir_y > 0))
        g->map.text.column_x = TEXT_WIDTH - g->map.text.column_x - 1;
}

//Funzione per calcolare il passo della texture e la posizione iniziale
	// - g->map.text.vertical_step rappresenta quanto la texture deve essere scalata verticalmente 
	//           per adattarsi alla colonna dell'immagine di gioco.
	// - g->map.text.current_tex_y rappresenta la posizione corrente nella texture da cui 
	//           leggere il prossimo pixel.
	//           Viene inizializzata in base alla distanza tra la cima della 
	//           colonna da disegnare e il centro dello schermo, moltiplicata 
	//           per il passo verticale (tex->step), e viene incrementata con 
	//           ogni iterazione del ciclo while per scorrere attraverso la texture.
static void calculate_texture_step_and_initial_position(t_game *g)
{
    g->map.text.vertical_step = (double)TEXT_HEIGHT / g->ray.line_height;
    g->map.text.current_tex_y = (g->ray.draw_start - RES_Y / 2 \
        + g->ray.line_height / 2) * g->map.text.vertical_step;
}

//Funzione per aggiornare i pixel dello schermo
//La funzione update_screen_pixels aggiorna i pixel della colonna corrente 
//dell'immagine di gioco (lo schermo) basandosi sui dati delle texture e sui 
//risultati del raycasting. Qui è un'analisi dettagliata di ciò che fa la funzione:
	// - Il ciclo while scorre attraverso ogni pixel della colonna corrente dall'inizio al termine del muro.
	// - column_y calcola la coordinata y sulla texture usando g->map.text.current_tex_y 
	//   e applicando una maschera bitwise per assicurarsi che sia entro i bordi.
	//   (io la faccio con un if else)
	// - current_tex_y viene incrementato per il prossimo pixel da campionare.
	// - color estrae il valore del colore dalla texture usando le coordinate 
	//   della colonna di pixel della texture
	// - Se la texture rappresenta il lato nord o est di un muro, il colore viene 
	//   ombreggiato per dare l'effetto di illuminazione.
	// - Se il colore non è trasparente (color > 0), viene scritto nel buffer 
	//   dell'immagine di gioco alla posizione corrente.
static void update_screen_pixels(t_game *g, int x)
{
    int y = g->ray.draw_start;
    int color;

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

void draw_screen_pixels(t_game *g, int x)
{
    calculate_texture_x(g);
    calculate_texture_step_and_initial_position(g);
    update_screen_pixels(g, x);
}