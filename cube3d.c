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

static void init_game(t_game *g)
{
	//inizializazione del motore grafico e lancio della finestra
	if (!init_engine(g))
		quit_and_free(MLX_ERR, 2, g);

	//inizializzo la matrice contente i pixel delle texture dei muri
	init_textures_mat(g);

	/*devo inizializzarla qui perche leggo N,W,S,E solo qui*/
	init_player_dir(g);

	// Inizializza l'immagine del contatore FPS
	init_fps_counter(g); 

	//inizializzo la minimappa
	init_minimap(g);

	
	//inizializzo il puntatore all'imagine del frame
	init_img_data(g, &g->frame, RES_X, RES_Y);


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
		quit_and_free(DATA_ERR, 2, game_struct);


	if (!extract_map(game_struct, map_fd))
		quit_and_free(MAP_ERR, 2, game_struct);

	
	if (!check_map(game_struct))
	{
		quit_and_free(MAP_ERR, 2, game_struct);
	}

	//alla fine chiudo l'fd
	close(map_fd);
}












/**************************************************************************** */
/*                      	   GAME LOOP	  		                          */
/**************************************************************************** */


static int ft_cube (t_game *g)
{
	static unsigned long last_frame_time;
	//unsigned long current_time;
	//unsigned long frame_time;

	if (g->frame_time_init_flag == 0)
	{
		last_frame_time = 0;
		g->frame_time_init_flag = 1;
	}
	
	g->current_time = get_time_in_milliseconds();
	g->frame_time = g->current_time - last_frame_time;
	
	
	// Verifica se è il momento di eseguire il rendering
	if (g->frame_time >= FPS_LIMIT)
	{
		// Aggiorna il tempo di frame
		g->frametime_sec = g->frame_time / 1000.0; // Converti millisecondi in secondi
		
		// Aggiorna la velocità in base al framerate
		g->player.move_speed = g->frametime_sec * MOVESPEED;
		g->player.rot_speed = g->frametime_sec * ROTSPEED;
		
		// Gestisci la logica di movimento
		handle_movement(g);
		
		// Esegui il rendering del frame
		render(g);
		
		// Mostra il frame rate
		//printf("fps = %d\n", (int)(1 / g->frametime_sec));
		draw_fps_counter(g);
		
		// Aggiorna il tempo dell'ultimo frame
		last_frame_time = g->current_time;
	}
return (0);
}

	



/**************************************************************************** */
/*                      	   		MAIN	  		                          */
/**************************************************************************** */
int	main(int argc, char **argv)
{
	t_game	game_struct;

	if (argc != 2)
		quit_and_free(ARG_ERR, 1, &game_struct);


	// funzione che inizializza la struct del gioco 
	init_game_struct(&game_struct);

	// funzione che valida (map_validator) la mappa: 1) controlla il ".ber"
	validator(&game_struct, argv);


	init_game(&game_struct);


	handle_input(&game_struct);


	//*****************************FUNZIONE DI GIOCO***********************************
	mlx_loop_hook(game_struct.mlx.mlx_ptr, ft_cube, &game_struct); 
	//*****************************FUNZIONE DI GIOCO***********************************


	// Avvia il loop della finestra
    mlx_loop(game_struct.mlx.mlx_ptr);


	//quit_and_free("fine", 2, &game_struct);
}