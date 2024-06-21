/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-21 13:51:18 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-21 13:51:18 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cube3d.h"

int	main(int argc, char **argv)
{
	t_game	game_struct;
	(void)game_struct;///togliere/
	(void)argv;///togliere/

	if (argc != 2)
		quit_and_free(ARG_ERR,1, &game_struct);

	// funzione che inizializza la struct del gioco 
	init_game_struct(&game_struct);

	/* funzione che valida (map_validator) la mappa:
	   1) controlla il ".ber"
	*/ 

	/*funzione che fa il parsing e crea la matrice*/
	
	
	// funzione che crea la matrice della mappa 

}