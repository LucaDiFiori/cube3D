/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:51:18 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/07/07 14:43:50 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cube3d.h"

/*da cancellare*/
static void stampamappa(t_game *g)
{
	printf("map_path = %s\n", g->map.map_path);
	printf("north = %s\n", g->map.wall_text.north);
	printf("south = %s\n", g->map.wall_text.south);
	printf("east = %s\n", g->map.wall_text.east);
	printf("west = %s\n", g->map.wall_text.west);
	printf("c_rgb.r = %d\n", g->map.wall_text.c_rgb.r);
	printf("c_rgb.g = %d\n", g->map.wall_text.c_rgb.g);
	printf("c_rgb.b = %d\n", g->map.wall_text.c_rgb.b);
	printf("f_rgb.r = %d\n", g->map.wall_text.f_rgb.r);
	printf("f_rgb.g = %d\n", g->map.wall_text.f_rgb.g);
	printf("f_rgb.b = %d\n", g->map.wall_text.f_rgb.b);
	int i = 0;
	while (g->map.map_mat[i])
	{
		printf("%s\n", g->map.map_mat[i]);
		i++;
	}

}

/**************************************************************************** */
/*                      FUNZIONE PRINCIPALE VALIDAZIONE                       */
/**************************************************************************** */
static void	validator(t_game *game_struct, char **argv)
{
	int	map_fd;

	//controllo .cub. Se va male la funzione fa exit
	check_extension(argv[1], game_struct);

	//se l'estensione va bene apro la mappa
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
	{
		close(map_fd);
		quit_and_free(OPEN_ERR, 1, game_struct);
	}




	//passo l'fd della mappa alla funzione econtrollo gli elementi del file .cub
	if (!extract_info(game_struct, map_fd))
		quit_and_free(DATA_ERR, 2, game_struct); // Fallimento nella validazione dei dati capire cosa fare


	if (!extract_map(game_struct, map_fd))
		quit_and_free(MAP_ERR, 2, game_struct); // Fallimento nella validazione dei dati capire cosa fare

	


	//dopo questa riga ho allocato anche la matrice
	
	if (!check_map(game_struct))
	{
		quit_and_free(MAP_ERR, 2, game_struct); // Fallimento nella validazione dei dati capire cosa fare
	}


	//qui devo chiamare la funzione che valida la mappa

	//alla fine chiudo l'fd
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

	// funzione che valida (map_validator) la mappa: 1) controlla il ".ber"
	validator(&game_struct, argv);

	/*devo inizializzarla qui perche leggo N,W,S,E solo qui*/
	init_asset(&game_struct);

	
	// ******************DACANCELLARE*********************************
	stampamappa(&game_struct);
	// ***********************************************



	//inizializazione del motore grafico e lancio della finestra
	if (!init_engine(&game_struct))
		quit_and_free(MLX_ERR, 2, &game_struct);





	// *******************PROVA RAY CASTING*********************************
	/*minimap_test(&game_struct);

	//gestione chiusura con il tasto x
	mlx_hook(game_struct.mlx.win_ptr, 17, 0, *ft_close_x, &game_struct);

	//hook per i pulsanti  --> devo fare la funzione INPUTS
	mlx_key_hook(game_struct.mlx.win_ptr, *inputs, &game_struct);
    
	//loop della finestra 
	mlx_loop(game_struct.mlx.mlx_ptr);*/


	
	//disegno la minimappa
	minimap_test(&game_struct);

	//gestisco la chiusura con il tasto x
	mlx_hook(game_struct.mlx.win_ptr, 17, 0, *ft_close_x, &game_struct);

	// Imposta gli hook per la pressione e il rilascio dei tasti
    mlx_hook(game_struct.mlx.win_ptr, 2, 1L<<0, key_press, &game_struct);
    mlx_hook(game_struct.mlx.win_ptr, 3, 1L<<1, key_release, &game_struct);

    // Imposta l'hook per il loop principale
	/*La funzionehandle_movement nel tuo codice (handle_movement nel tuo caso) 
	viene chiamata ripetutamente dal loop principale di MinilibX ogni volta che 
	la finestra è in attesa di input o di rendering. All'interno di loop_hook, 
	puoi includere la logica per controllare lo stato dei tasti (W, A, S, D) e 
	gestire il movimento del personaggio, aggiornare la minimappa, e eseguire 
	altre operazioni necessarie per il funzionamento del tuo gioco.*/
    mlx_loop_hook(game_struct.mlx.mlx_ptr, handle_movement, &game_struct);

    // Avvia il loop della finestra
    mlx_loop(game_struct.mlx.mlx_ptr);



	

	quit_and_free("fine", 2, &game_struct);


}