/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:51:18 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/06/23 16:09:38 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cube3d.h"

/**************************************************************************** */
/*                      FUNZIONE PRINCIPALE VALIDAZIONE                       */
/**************************************************************************** */
static void	validator(t_game *game_struct, char **argv)
{
	int	map_fd;

	/*controllo .cub*/
	check_extension(argv[1], game_struct);

	/*se l'estensione va bene apro la mappa*/
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
	{
		close(map_fd);
		quit_and_free(OPEN_ERR, 1, game_struct);
	}




	/*passo l'fd della mappa alla funzione econtrollo gli elementi del file .cub*/
	cub_file_validator(game_struct, map_fd);

	/*Qui potrei mettere la funzione che controlla il campo t_walll_text della game_struct
	  (controlla se tutti i campi sono stati riempiti o no)*/

	/*controllo la mappa vera e propria con map_validator*/



	/*alla fine chiudo l'fd*/
	close(map_fd);
}

int	main(int argc, char **argv)
{
	t_game	game_struct;

	if (argc != 2)
		quit_and_free(ARG_ERR,1, &game_struct);

	// funzione che inizializza la struct del gioco 
	init_game_struct(&game_struct);

	/* funzione che valida (map_validator) la mappa:
	   1) controlla il ".ber" */
	validator(&game_struct, argv); 

	/*funzione che fa il parsing e crea la matrice*/
	
	
	// funzione che crea la matrice della mappa 

}