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

static int find_map( int map_fd)
{
	char	*line;

	line = get_next_line(map_fd);
	while (line && (!*line || line[0] == '\n'))
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
	free(line);
	get_next_line(-2);
	return (1);
}



/*capire cosa friare in caso di errore*/
	/*Senno faccio una funzione che:
	 * gli passo l'fd
	 * dentro dichiaro un puntatore char ( che sarà il buffer di read)
	 * leggo tot caratteri alla volta in un ciclo (finche read non restituisce 0)
	 * faccio uno stjoin con questa riga e libero il buffer
	 * una volta uscito dal ciclo avrà una lunga stringa che splietterà sul carattere '\n'
	   assegnando il risultato dello splitt alla struct
	 - libero la stringa joinata*/
int extract_map(t_game *g_s, int map_fd)
{
	char	*buffer;
	char	*join_map;
	ssize_t bytes_read;

	
	if (!find_map(map_fd))
		return (0); /*in questo caso non ho trovato la mappa*/


	/*se sono qui la mappa c'è e la prima riga è stata letta*/



	join_map = NULL;
	buffer = (char *)malloc(sizeof(char) * 21);
	if (!buffer) 
        return 0;

	bytes_read = read(map_fd, buffer, 20);
	while (bytes_read > 0)
	{
    	buffer[bytes_read] = '\0';
    	char *temp = ft_strjoin(join_map, buffer); // Concatenate
    	if (!temp) 
    	{
        	free(buffer); // Only free buffer here, join_map is already freed by ft_strjoin if it fails
        	return 0;
    	}
    	join_map = temp;
    	bytes_read = read(map_fd, buffer, 20); // Read next block
	}
	free(buffer); // Free buffer after the loop
	//buffer = NULL; // Prevent reuse

    if (bytes_read == -1) {
        // Errore di lettura dal file descriptor
        free(join_map);
		//join_map = NULL; // Prevent reuse
        return 0;
    }




	g_s->map.map_mat = ft_split(join_map, '\n');
	free(join_map);

	if (!g_s->map.map_mat)
		return (0);
	return (1);
}