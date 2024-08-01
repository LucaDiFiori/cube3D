/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-01 10:24:33 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-08-01 10:24:33 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/cube3d.h"

/*NOTA. Per ruatare stiamo applicando le formule di rotazione per un vettore 2d:
            nuovox =  x * cos(alpha) - y * sin(alpha)
            nuovoy =  x * sin(alpha) + y * cos(alpha)*/

// Aggiorna la direzione del giocatore
static void update_player_direction(t_asset *p, double cos_rot, double sin_rot) 
{
	double tmp_x = p->dir_vec[0];
	p->dir_vec[0] = p->dir_vec[0] * cos_rot - p->dir_vec[1] * sin_rot;
	p->dir_vec[1] = tmp_x * sin_rot + p->dir_vec[1] * cos_rot;
}

// Aggiorna il piano del giocatore
static void update_player_plane(t_asset *p, double cos_rot, double sin_rot) 
{
	double tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos_rot - p->plane_y * sin_rot;
	p->plane_y = tmp_x * sin_rot + p->plane_y * cos_rot;
}

static int rotate(t_game *g, double rotspeed) 
{
	double cos_rot = cos(rotspeed);
	double sin_rot = sin(rotspeed);

	update_player_direction(&g->player, cos_rot, sin_rot);
	update_player_plane(&g->player, cos_rot, sin_rot);

	return 1;
}

int rotate_player(t_game *g, double rotdir) 
{
    double rotspeed;

    /*NOTA: Collegamento fra rotspeed e l'angolo di rotazione:
            ROTSPEED = Questo valore rappresenta quanto velocemente il giocatore può ruotare.
                       è un valore predefinito che indica la quantità di angolo 
                       che il giocatore ruota per input di rotazione (pressione frecce).
                       
            ROTDIR = questo valore indica solo la direzione. Moltiplica rotspeed per -1
                     muoversi a sinistra o per 1 per muoversi a destra
                     
            Quando vuoi ruotare il giocatore, moltiplichi la velocità di rotazione 
            (rotspeed) per la direzione (rotdir). 
            Questo prodotto (rotspeed * rotdir) ti dà l'angolo di rotazione 
            effettivo per quel frame o input.
            
            es: Se rot_speed è 0.05 e rotdir è 1 (destra), rotspeed sarà 0.05 radianti per quel frame*/
    rotspeed = g->player.rot_speed * rotdir;
    rotate(g, rotspeed);
    return (0);
}