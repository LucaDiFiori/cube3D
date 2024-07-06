/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:51:18 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/06/24 11:39:05 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cube3d.h"

/**************************************************************************** */
/*                      FUNZIONE PRINCIPALE VALIDAZIONE                       */
/**************************************************************************** */
static void	validator(t_game *game_struct, char **argv)
{
	int	map_fd;

	/*controllo .cub. Se va male la funzione fa exit*/
	check_extension(argv[1], game_struct);

	/*se l'estensione va bene apro la mappa*/
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
	{
		close(map_fd);
		quit_and_free(OPEN_ERR, 1, game_struct);
	}




	/*passo l'fd della mappa alla funzione econtrollo gli elementi del file .cub*/
	if (!extract_info(game_struct, map_fd))
		quit_and_free(DATA_ERR, 2, game_struct); // Fallimento nella validazione dei dati capire cosa fare


	if (!extract_map(game_struct, map_fd))
		quit_and_free(MAP_ERR, 2, game_struct); // Fallimento nella validazione dei dati capire cosa fare

	


	/*dopo questa riga ho allocato anche la matrice*/
	
	if (!check_map(game_struct))
	{
		quit_and_free(MAP_ERR, 2, game_struct); // Fallimento nella validazione dei dati capire cosa fare
	}


	/* qui devo chiamare la funzione che valida la mappa*/

	/*alla fine chiudo l'fd*/
	close(map_fd);
}





/**************************************************************************** */
/*                      	   		MAIN	  		                          */
/**************************************************************************** */
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

	
	/*************************************************** */
	printf("map_path = %s\n", game_struct.map.map_path);
	printf("north = %s\n", game_struct.map.wall_text.north);
	printf("south = %s\n", game_struct.map.wall_text.south);
	printf("east = %s\n", game_struct.map.wall_text.east);
	printf("west = %s\n", game_struct.map.wall_text.west);
	printf("c_rgb.r = %d\n", game_struct.map.wall_text.c_rgb.r);
	printf("c_rgb.g = %d\n", game_struct.map.wall_text.c_rgb.g);
	printf("c_rgb.b = %d\n", game_struct.map.wall_text.c_rgb.b);
	printf("f_rgb.r = %d\n", game_struct.map.wall_text.f_rgb.r);
	printf("f_rgb.g = %d\n", game_struct.map.wall_text.f_rgb.g);
	printf("f_rgb.b = %d\n", game_struct.map.wall_text.f_rgb.b);
	int i = 0;
	while (game_struct.map.map_mat[i])
	{
		printf("linea = %s\n", game_struct.map.map_mat[i]);
		i++;
	}
	/*********************************************** */



	/*inizializazione del motore grafico e lancio della finestra */
	if (!init_engine(&game_struct))
		quit_and_free(MLX_ERR, 2, &game_struct);









	/*******************PROVA RAY CASTING********************************* */
	minimap_test(&game_struct);
	 // Mette il programma in attesa degli eventi (necessario per mantenere aperta la finestra)
    mlx_loop(game_struct.mlx.mlx_ptr);
	/**************************************************** */
	






	quit_and_free("fine", 2, &game_struct);


}