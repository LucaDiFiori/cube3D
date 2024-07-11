/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaestri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:59 by cmaestri          #+#    #+#             */
/*   Updated: 2024/07/07 09:30:51 by cmaestri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

/*
funzione per determinare il numero di righe e colonne della mappa. se trovo una riga con un numero maggiore di colonne rispetto alla precedente, aggiorno il numero di map_cols.
*/
void	find_rows_and_cols(t_map *map)
{
	int	x;
	
	if (!map->map_mat)
		return ;
	map->map_y = 0;
	map->map_x = 0;
	while (map->map_mat[map->map_y])
	{
		x = 0;
		while (map->map_mat[map->map_y][x])
			x++;
		if (x > map->map_y)
			map->map_x = x;
		map->map_y++;
	}
}

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
scorro la matrice contenente la mappa e controllo che ci siano solo caratteri validi.
-se trovo un carattere non valido returno 1.
-incremento num_player se trovo un carattere corrispondente al player 
 (N,S,E,W) e se num_player > 1 (è stato inserito più di un player) returno 1.
-se non trovo errori returno 0.
*/
static int	check_characters(t_game *game)
{
	int		x;
	int		y;
	int		num_players;
	char	c;
	
	y = 0;
	num_players = 0;
	while (game->map.map_mat[y])
	{
		x = 0;
		while (game->map.map_mat[y][x])
		{
			c = game->map.map_mat[y][x];
			if ((c != '0' && c != '1' && c != ' ' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W'))
				return (1);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player.x = x;
				game->player.y = y;
				game->player.dir = c;
				num_players++;
			}
			if (num_players > 1)
				return (1);
			x++;
		}
		y++;
	}
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
