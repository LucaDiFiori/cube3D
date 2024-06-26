/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-26 09:31:22 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-26 09:31:22 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"
static int missing_map(char *line)
{
	if (!*line || line[0] == '\n') 
		return (1);
	return (0);
}

static int find_map(char *line, int map_fd)
{
	while (line && missing_map(line))
	{
		free(line);
		line = get_next_line(map_fd);
	}
	/*Se sono uscito dal ciclo ed il file è terminato (!line) significa che la
	  mappa manca*/
	if (!line)
	{
		free(line);
		get_next_line(-2);
		return (0); //in questo casa manca la mappa 
	}
	return (1);
}

int extract_map(t_game *g_s, int map_fd)
{
	char	*line;

	line = get_next_line(map_fd);
	if (!find_map(line, map_fd))
		return (0);
	/*se sono qui la mappa c'è e la prima riga è stata letta*/


	/*Senno faccio una funzione che:
	 - gli passo l'fd
	 - dentro dichiaro un puntatore char ( che sarà il buffer di read)
	 - leggo tot caratteri alla volta in un ciclo (finche read non restituisce 0)
	 - faccio uno stjoin con questa riga e libero il buffer
	 - una volta uscito dal ciclo avrà una lunga stringa che splietterà sul carattere '\n'
	   assegnando il risultato dello splitt alla struct
	
	*/





	return (1);
}