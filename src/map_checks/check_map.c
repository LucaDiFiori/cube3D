/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaestri <cmaestri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:59 by cmaestri          #+#    #+#             */
/*   Updated: 2024/07/15 16:09:32 by cmaestri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

/*
1) PRIMO IF:
(ho modificato i nomi delle variabili, i è x e j è y)
- se la riga che sto esaminando è al di fuori del bordo superiore della mappa (i < 0)
- o se è al di fuori del bordo inferiore della mappa (i >= rows)
- o se la colonna che sto esaminando è al di fuori del bordo sinistro della mappa (j < 0)
- o se è al di fuori del bordo destro della mappa (j >= cols)
- o se il carattere della mappa è 1 (muro) o * (già visitato)
	-> RETURNO 0 (per non continuare il flood_fill in quella direzione)

2) SECONDO IF: se il carattere della mappa è ' ' (spazio)
	-> RETURNO 1 (MALE! il carattere ' ' è raggiungibile)

3) ELSE (se il carattere della mappa e diverso da ' ' e da '1')
	-> setto il carattere della mappa a '*' (già visitato). questo impedisce alla funzione di visitare la stessa cella più di una volta.

4) TERZO IF: chiamo ricorsivamente la funzione flood_fill per le celle adiacenti a quella attuale (sopra, sotto, sinistra, destra)
	-> se una delle chiamate ricorsive returna 1 (secondo if. quindi il carattere ' ' è raggiungibile) returno 1

5) ELSE: se nessuna delle chiamate ricorsive trova uno spazio 
	-> returno 0 (BENE! il carattere ' ' non è raggiungibile)
*/

static int	flood_fill(char **map, int x, int y, int rows, int cols)
{
	if (x < 0 || x >= rows || y < 0 || y >= cols || map[x][y] == '1' || map[x][y] == '*')
		return (0);
	if (map[x][y] == ' ')
		return (1);
	map[x][y] = '*';
	if (flood_fill(map, x - 1, y, rows, cols) || flood_fill(map, x + 1, y, rows, cols) ||
		flood_fill(map, x, y - 1, rows, cols) || flood_fill(map, x, y + 1, rows, cols))
		return (1);
	return (0);
}

/*
IS_REACHABLE controlla se il carattere ' ' è raggiungibile dal personaggio (non vogliamo che lo sia).
scorre lungo la mappa e quando trova il carattere del player (N,S,E,W) chiama la funzione flood_fill che returna 1 se il carattere ' ' è raggiungibile.
*/
static int	is_reachable(char **map, int rows, int cols)
{
	int	x;
	int	y;

	x = 0;
	while (x < rows)
	{
		y = 0;
		while (y < cols)
		{
			if (map[x][y] == 'N' || map[x][y] == 'S'
				|| map[x][y] == 'E' || map[x][y] == 'W')
				return (flood_fill(map, x, y, rows, cols));
			y++;
		}
		x++;
	}
	return (0);
}


/* CONTROLLO I CARATTERI DELLA MAPPA
scorro la matrice contenente la mappa e al suo interno chiamo valid_chars(), che controlla che ci siano solo caratteri validi.
- se il carattere che sto controllando non e' tra quelli validi returno 0.
- se trovo uno dei caratteri corrispondenti al player setto le coordinate (x e y) e l'orientamento (dir) del player e returno 2 a check_characters() per segnalare la presenza di un player
- in check_characters(), se !valid_chars() returno 1 -> errore
- se valid_chars() returna un valore > 1 (2) incremento player
- se player != 1 (è stato inserito più di un player o non ci sono player) returno 1 -> errore.
- se non trovo errori returno 0.
*/

static int valid_chars(t_game *game, char c, int x, int y)
{
	if ((c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S' && c != 'E' && c != 'W' && c != 'D' && c != 'd'))
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		game->player.x = x;
		game->player.y = y;
		game->player.start_dir = c;
		return (2);
	}
	return (1);
}

static int	check_characters(t_game *game)
{
	int		x;
	int		y;
	int		player;
	char	c;
	
	y = 0;
	player = 0;
	while (game->map.map_mat[y])
	{
		x = 0;
		while (game->map.map_mat[y][x])
		{
			c = game->map.map_mat[y][x];
			if (!valid_chars(game, c, x, y))
				return (1);
			if (valid_chars(game, c, x, y) > 1)
				player++;
			x++;
		}
		y++;
	}
	if (player != 1)
		return (1);
	return (0);
}

/** QUESTA E LA MIA
 * Function: check_characters
 * ---------------------------
 * Validates the characters present in the game map to ensure they are all 
 * recognized and that there is exactly one starting position character. 
 * This function scans through the map matrix to check for valid characters 
 * and ensure that only one of the starting position characters ('N', 'S', 
 * 'E', 'W') is present.
 * 
 * Parameters:
 *  - game: A copy of the game structure containing the map data to be validated.
 *
 * Returns:
 *  - An integer indicating the result of the validation:
 *    - Returns 1 if any invalid characters are found or if more than one 
 *      starting position character is present.
 *    - Returns 0 if all characters are valid and exactly one starting position 
 *      character is found.
 *
 * Process:
 *  - Iterates over each row (`i`) and each column (`j`) of the map matrix.
 *  - Checks each character (`c`) in the map matrix:
 *    - Validates that the character is one of '0', '1', ' ', 'N', 'S', 'E', 'W'.
 *    - If any character is invalid, returns 1 to indicate an error.
 *    - Counts the occurrences of starting position characters ('N', 'S', 'E', 'W').
 *    - If more than one starting position character is found, returns 1.
 *  - If all characters are valid and only one starting position character is found, 
 *    returns 0.
 * 
 * Note: The function ensures that the map contains only valid characters and that 
 *       there is a single starting position, which is essential for correct game initialization.
 
static int	check_characters(t_game game)
{
	int		i;
	int		j;
	int		k;
	char	c;
	
	i = 0;
	k = 0;
	while (game.map.map_mat[i])
	{
		j = 0;
		while (game.map.map_mat[i][j])
		{
			c = game.map.map_mat[i][j];
			if (c != '0' && c != '1' && c != ' ' && c != 'N' 
				&& c != 'S' && c != 'E' && c != 'W')
				return (1);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				k++;
			if (k > 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}*/

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

	find_rows_and_cols(&game->map);
	if (is_closed(*game))
	{
		map_copy = duplicate_map(game->map.map_mat, game->map.map_y, game->map.map_x);
		if (check_characters(game)
			|| is_reachable(map_copy, game->map.map_y, game->map.map_x))
			{
				free_mapcopy(map_copy, game->map.map_y);
				return (0);
			}
		free_mapcopy(map_copy, game->map.map_y);
		return (1);
	}
	return (0);
}