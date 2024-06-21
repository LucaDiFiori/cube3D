/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-21 17:35:04 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-21 17:35:04 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

/*controlla la validità degli elementi presenti nel cub file*/
static void cub_file_validator(t_game *game_struct, char **argv, int map_fd)
{


}




/*void map_validator --> controllerà la validità della mappa*/







/**************************************************************************** */
/*                         FUNZIONE PRINCIPALE                                */
/**************************************************************************** */
void	validator(t_game *game_struct, char **argv)
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
	cub_file_validator(game_struct, argv, map_fd);

	/*controllo la mappa vera e propria con map_validator*/



	/*alla fine chiudo l'fd*/
	close(map_fd);
}