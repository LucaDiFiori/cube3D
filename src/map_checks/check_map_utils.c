/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaestri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:59 by cmaestri          #+#    #+#             */
/*   Updated: 2024/07/07 09:02:48 by cmaestri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

/* si occupa di copiare riga per riga la mappa in map_copy, aggiungendo spazi (' ') per arrivare alla lunghezza della riga più lunga ed avere così una mappa quadrata.
*/
char	*duplicate_row(char *row, int current_cols, int cols)
{
	char *row_copy;
	int j;
	
	row_copy = (char *)malloc((cols + 1) * sizeof(char));
	if (!row_copy)
		return (NULL);
	j = 0;
	while (j < cols)
	{
		if (j < current_cols)
			row_copy[j] = row[j];
		else
			row_copy[j] = ' ';
		j++;
	}
	row_copy[cols] = '\0';
	return (row_copy);
}

/* creo una copia della mappa da passare al flood_fill, su ogni riga della copia viene chiamata duplicate_row() */
char	**duplicate_map(char **map, int rows, int cols)
{
	char	**map_copy;
	int		i;
	int		current_cols;

	map_copy = (char **)malloc(rows * sizeof(char *));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		current_cols = 0;
		while (map[i][current_cols])
			current_cols++;
		map_copy[i] = duplicate_row(map[i], current_cols, cols);
		if (!map_copy[i])
			return (NULL);
		i++;
	}
	return (map_copy);
}

void	free_mapcopy(char **map, int rows)
{
	int	i;
	int j;
	
	if (!map)
		return ;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (map[i][j])
			j++;
		free(map[i]);
		i++;
	}
	free(map);
}

/*
void	print_map_copy(char **map_copy, int rows)
{
    int i = 0;
    int j;

    printf("\nMAP COPY\n");
    while (i < rows) {
        j = 0;
        while (map_copy[i][j]) {
            printf("%c", map_copy[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
}
*/
