/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:35:04 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/06/24 10:24:48 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

#include "../../inc/cube3d.h"

/*
COSA NON FUNZIONA SULLE INFO DELLA MAPPA:
- map_only.cub: Manca un controllo nel caso in cui la mappa non sia presente
*/




static int extract_rgb(t_rgb *color, char *line) 
{
    char **split_line;
		/*mi serve temp_ptr perchè altrimenti dovrei modificare il puntatore
		split_line (ad esempio facendo split_line++) e questo causa problemi 
		quando chiamo la funzione free():
		Questo perchè essendo un array di puntatori, facendo split_line++ sto 
		puntando alla stringa successiva e non piu al primo elemento. Andrei quindi 
		a passare questo elemento alla funzione free_matrix ed avrò quindi problemi*/
    char *temp_ptr;
    int i;
    
    split_line = ft_split(line, ',');
    if (!split_line)
	{
		printf("ERRORE_EXTRACT_RGB: 0\n"); //////
		return (0); // Fallimento nell'allocazione
	}

    i = 0;
    while (split_line[i] != NULL)
    {
		/*salto tutti i caratteri che non siano numeri*/
        temp_ptr = split_line[i];
        while (*temp_ptr && !ft_isdigit(*temp_ptr))
            temp_ptr++;
		/*se la stringa è finita esco */
        if (!*temp_ptr)
		{
			printf("ERRORE_EXTRACT_RGB: 1\n"); //////
			return (free_matrix(split_line)); // Pulizia e uscita per errore
		}

		printf("strlen(temp_ptr): %d\n", ft_strlen(temp_ptr)); //////
			
		/*per ogni stringa controllo che la lunghezza sia fra 0 e 3 e la converto in numero*/
		if (i == 0)
			color->r = ft_atoi(temp_ptr);
		else if (i == 1)
			color->g = ft_atoi(temp_ptr);
		else if (i == 2)
			color->b = ft_atoi(temp_ptr);
		else
		{
			printf("ERRORE_EXTRACT_RGB: 2\n"); //////
			return (free_matrix(split_line)); // Pulizia e uscita per errore
		}
        i++;
    }
    
	
	// Validazione dei valori RGB
    if (color->r < 0 || color->r > 255 || color->g < 0 || color->g > 255 
		|| color->b < 0 || color->b > 255) 
		{
			printf("ERRORE_EXTRACT_RGB: 3\n"); //////
			return (free_matrix(split_line)); // Pulizia e uscita per errore
		}

    free_matrix(split_line); // Pulizia
    return (1); // Successo
}






/*controlla la validità degli elementi presenti nel cub file

NOTA: Questa funzione, alla fine, riempirà il campo della struct game: t_wall_text
      con le info descritte nel file.
	  Alla fine di questa funzione, per controllare che ci siano tutte, dovrò verificare
	  CHE QUEI CAMPI DELLA STRUCT NON SIANO RIMASTI NULL
*/
void cub_file_validator(t_game *g_s, int map_fd)
{
	char	*line;
	char 	**split_line;
	int		count_info;

	count_info = 0;

	/*estraggo la prima linea*/
	line = get_next_line(map_fd);

	/*ciclo su teutte le linee finchè non è finito il file o finchè non ha raccolto tutte le info */
	while (line != NULL && check_missing_info(g_s))
	{
		/* splitto ogni riga sulla spazi creano una matrice della riga*/
		split_line = ft_split(line, ' ');

		/*controllo i primi due caratteri della prima stringa. 
		  Se sono quelli desiderati chiamo la funzione (da scrivere) che 
		  estrarrà le info (gli elementi dopo l'indentifier)*/
		if (split_line[0][0] == 'N' && split_line[0][1] == 'O')
		{
			g_s->map.wall_text.north = remove_space_strcpy(line + 2);
			if (!g_s->map.wall_text.north)
			{
				printf("ERRORE: 1\n"); //////
				quit_and_free(DATA_ERR, 1, g_s);////CAPIRE COSA FREARE
			}
			count_info++;
		}
		else if (split_line[0][0] == 'S' && split_line[0][1] == 'O')
		{
			g_s->map.wall_text.south = remove_space_strcpy(line + 2);
			if (!g_s->map.wall_text.south)
			{
				printf("ERRORE: 2\n"); //////
				quit_and_free(DATA_ERR, 1, g_s);////CAPIRE COSA FREARE
			}
			count_info++;
		}
		else if (split_line[0][0] == 'E' && split_line[0][1] == 'A')
		{
			g_s->map.wall_text.east = remove_space_strcpy(line + 2);
			if (!g_s->map.wall_text.east)
			{
				printf("ERRORE: 3\n"); //////
				quit_and_free(DATA_ERR, 1, g_s);////CAPIRE COSA FREARE
			}
			count_info++;
		}
		else if (split_line[0][0] == 'W' && split_line[0][1] == 'E')
		{
			g_s->map.wall_text.west = remove_space_strcpy(line + 2);
			if (!g_s->map.wall_text.west)
			{
				printf("ERRORE: 4\n"); //////
				quit_and_free(DATA_ERR, 1, g_s);////CAPIRE COSA FREARE
			}
			count_info++;
		}
		else if (split_line[0][0] == 'F')
		{
			if (!extract_rgb(&(g_s->map.wall_text.f_rgb), line))
			{
				printf("ERRORE: 5\n"); //////
				quit_and_free(DATA_ERR, 1, g_s);////CAPIRE COSA FREARE
			}
			printf("g_s->map.wall_text.f_rgb.r: %d\n", g_s->map.wall_text.f_rgb.r); //////
			count_info++;
		}
		else if (split_line[0][0] == 'C')
		{
			if (!extract_rgb(&(g_s->map.wall_text.c_rgb), line))
			{
				printf("ERRORE: 6\n"); //////
				quit_and_free(DATA_ERR, 1, g_s);////CAPIRE COSA FREARE
			}
			printf("g_s->map.wall_text.c_rgb.r: %d\n", g_s->map.wall_text.c_rgb.r); //////
			count_info++;
		}
		else if (is_map_line(line))
		{
			printf("SONO NELLA MAPPA\n"); //////
			break;
		}
		free(line);
		line = get_next_line(map_fd);
		free(split_line);
	}
	if (line)
		free(line);

	/*Qui verifico che siano state raccolte esattamente 6 informazioni e che tutti
	  i campi siano riempiti nella struct (e quindi non ho 6 informazioni uguali
	  nel file)*/
	if (count_info != 6 || check_missing_info(g_s))
	{
		/*Qui mi serve che quit controlli quali delgli elementi della struct texture è
		  diverso da NULL (quindi allocato e friarlo)*/
		printf("count_info: %d\n", count_info); //////
		printf("ERRORE: 7\n");                  //////
		quit_and_free(DATA_ERR, 1, g_s);
	}

	
}



/*NOTA: LA funzione sopra estrarrà solo le info quindi poi dovrò riaprire il file
        e andare avanti finche non trovo la mappa (se arrivo qui significa che non 
		sono uscito e quindi le info ci sono tutte).
		Per farlo posso rifare un ciclo estraendo una linea per volta di gnl
		e ogni volta fare uno STRSTR sulla linea: se trova NO, ES etc o una linea
		vuota o contenente solo un \n -> CONTINUE
		cosi si fermerà all'inizio della mappa */


/*void map_validator --> controllerà la validità della mappa*/

