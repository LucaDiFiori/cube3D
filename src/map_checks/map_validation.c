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

char	*extract_file_data(t_game *g_s, char *info)
{
	if (line[0] == 'N' && line[0] == 'O')
		remove_space_strcpy(g_s->map.wal_text.north, (info + 2))
	else if (line[0] == 'S' && line[0] == 'O')
		remove_space_strcpy(g_s->map.wal_text.south, (info + 2))
	else if (line[0] == 'W' && line[0] == 'E')
		remove_space_strcpy(g_s->map.wal_text.west, (info + 2))
	else if (line[0] == 'E' && line[0] == 'A')
		remove_space_strcpy(g_s->map.wal_text.east, (info + 2))

	/*per i colori dovrei splittare la linea dei colori (con la virgola)
	  verificare che siano 3 e maggiori di zero e minori di 255 e poi metterli 
	  dentrio gli elementi della struct.*/
}






/*controlla la validità degli elementi presenti nel cub file

NOTA: Questa funzione, alla fine, riempirà il campo della struct game: t_wal_text
      con le info descritte nel file.
	  Alla fine di questa funzione, per controllare che ci siano tutte, dovrò verificare
	  CHE QUEI CAMPI DELLA STRUCT NON SIANO RIMASTI NULL
*/
static void cub_file_validator(t_game *g_s, char **argv, int map_fd)
{
	char	*line;
	char 	**split_line;
	int		count_info;

	count_info = 0;

	/*estraggo la prima linea*/
	line = get_next_line(map_fd);

	/*ciclo su teutte le linee*/
	while (line != NULL && count_info != 6)
	{
		/* splitto ogni riga sulla spazi creano una matrice della riga*/
		split_line = ft_split(line, ' ');

		/*controllo i primi due caratteri della prima stringa. 
		  Se sono quelli desiderati chiamo la funzione (da scrivere) che 
		  estrarrà le info (gli elementi dopo l'indentifier)*/
		if (split_line[0][0] == 'N' && split_line[0][1] == 'O'
			/*&& !(g_s->map.wal_text.north)*/)
			{
				g_s->map.wal_text.north = extract_file_data(g_s, line);
				count_info++;
				free(line);
				free(split_line);
				line = get_next_line(map_fd);
			}
		else if (split_line[0][0] == 'S' && split_line[0][1] == 'O')
			{
				g_s->map.wal_text.south = extract_file_data(g_s, line);
				count_info++;
				free(line);
				free(split_line);
				line = get_next_line(map_fd);
			}
		else if (split_line[0][0] == 'E' && split_line[0][1] == 'A')
			{
				g_s->map.wal_text.east = extract_file_data(g_s, line);
				count_info++;
				free(line);
				free(split_line);
				line = get_next_line(map_fd);
			}
		else if (split_line[0][0] == 'W' && split_line[0][1] == 'E')
			{
				g_s->map.wal_text.west = extract_file_data(g_s, line);
				count_info++;
				free(line);
				free(split_line);
				line = get_next_line(map_fd);
			}
		else if (split_line[0][0] == 'C')
			{
				g_s->map.wal_text.c_color = extract_color_data(g_s, line);
				count_info++;
				free(line);
				free(split_line);
				line = get_next_line(map_fd);
			}
		else if (split_line[0][0] == 'F')
			{
				g_s->map.wal_text.f_color = extract_color_data(g_s, line);
				count_info++;
				free(line);
				free(split_line);
				line = get_next_line(map_fd);
			}
		free(line);
		free(split_line);
		line = get_next_line(map_fd);
	}
	if (line)
		free(line);
	if (split_line)
		free(split_line);
	if (count_info != 6 )
	{
		/*Qui mi serve che quit controlli quali delgli elementi della struct texture è
		  diverso da NULL (quindi allocato e friarlo)*/
		quit_and_free(DATA_ERR, 1, g_s);
	}
	/*mettere anche un controllo sugli elementi stessi es:
	  if (g_l->)
	
	*/
}

/*NOTA: LA funzione sopra estrarrà solo le info quindi poi dovrò riaprire il file
        e andare avanti finche non trovo la mappa (se arrivo qui significa che non 
		sono uscito e quindi le info ci sono tutte).
		Per farlo posso rifare un ciclo estraendo una linea per volta di gnl
		e ogni volta fare uno STRSTR sulla linea: se trova NO, ES etc o una linea
		vuota o contenente solo un \n -> CONTINUE
		cosi si fermerà all'inizio della mappa */


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

	/*Qui potrei mettere la funzione che controlla il campo t_wall_text della game_struct
	  (controlla se tutti i campi sono stati riempiti o no)*/

	/*controllo la mappa vera e propria con map_validator*/



	/*alla fine chiudo l'fd*/
	close(map_fd);
}