/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaestri <cmaestri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:59 by cmaestri          #+#    #+#             */
/*   Updated: 2024/07/17 10:35:30 by cmaestri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

/* CONTROLLO I CARATTERI DELLA MAPPA
scorro la matrice contenente la mappa e al suo interno chiamo valid_chars(), che controlla che ci siano solo caratteri validi.
- se il carattere che sto controllando non e' tra quelli validi returno 0.
- se trovo uno dei caratteri corrispondenti al player setto le coordinate (x e y) e l'orientamento (dir) del player e returno 2 a check_characters() per segnalare la presenza di un player
- in check_characters(), se !valid_chars() returno 1 -> errore
- se valid_chars() returna un valore > 1 (2) incremento player
- se player != 1 (è stato inserito più di un player o non ci sono player) returno 1 -> errore.
- se non trovo errori returno 0.
*/

static int valid_door(t_game *game, int x, int y)
{
    if ((x > 0 && game->map.map_mat[y][x - 1] == '1') && (game->map.map_mat[y][x + 1] == '1'))
		return (1);
    if ((y > 0 && game->map.map_mat[y - 1][x] == '1') && (game->map.map_mat[y + 1][x] == '1'))
		return (1);
	return (0);
}


static int	valid_chars(t_game *game, char c, int x, int y)
{
	if ((c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != 'D' && c != 'U'))
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->player.x = x;
		game->player.y = y;
		game->player.dir = c;
		game->map.num_players++;
	}
	if (c == 'D')
	{
		if (!valid_door(game, x, y))
			return (0);
		game->map.num_doors++;
	}
	if (c == 'U')
		game->map.num_exits++;
	return (1);
}

static int	check_characters(t_game *game)
{
	int		x;
	int		y;
	char	c;
	
	y = 0;
	while (game->map.map_mat[y])
	{
		x = 0;
		while (game->map.map_mat[y][x])
		{
			c = game->map.map_mat[y][x];
			if (!valid_chars(game, c, x, y))
				return (1);
			x++;
		}
		y++;
	}
	if (game->map.num_players != 1 || game->map.num_exits > 1 || game->map.num_doors > 20)
		return (1);
	return (0);
}

/*
la funzione CHECK MAP
- chiama la funzione find_rows_and_cols per determinare il numero di righe e colonne della mappa.
- se la mappa è chiusa (is_closed) 
	-> per prima cosa crea una copia della mappa (map_copy)
	-> poi chiama la funzione check_characters per controllare che tutti i caratteri della mappa siano validi e che esista un solo player sulla mappa (N, S, W, E) 
	-> e is_reachable (flood_fill) per controllare se il carattere ' ' è raggiungibile.
		-> se queste due funzioni returnano 1 (ERRORE) libero per prima cosa la copia della mappa e poi returno 0 (ERRORE!)
	-> altriementi libero la copia della mappa e returno 1 (no problema)
- altrimenti returno 0 (ERRORE!)
*/

int	check_map(t_game *game)
{
	char **map_copy;
	char **map_copy2;

	find_rows_and_cols(&game->map);
	if (is_closed(*game))
	{
		map_copy = duplicate_map(game->map.map_mat, game->map.map_y, game->map.map_x);
		map_copy2 = duplicate_map(game->map.map_mat, game->map.map_y, game->map.map_x);
		if (check_characters(game)
			|| is_reachable(game, map_copy, map_copy2, game->map.map_y, game->map.map_x))
			{
				free_mapcopy(map_copy, game->map.map_y);
				free_mapcopy(map_copy2, game->map.map_y);
				return (0);
			}
		free_mapcopy(map_copy, game->map.map_y);
		free_mapcopy(map_copy2, game->map.map_y);
		return (1);
	}
	return (0);
}
