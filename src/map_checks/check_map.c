/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaestri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:24:59 by cmaestri          #+#    #+#             */
/*   Updated: 2024/07/06 01:59:20 by cmaestri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

/*

1) PRIMO IF:
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

static int	flood_fill(char **map, int i, int j, int rows, int cols)
{
	if (i < 0 || i >= rows || j < 0 || j >= cols || map[i][j] == '1' || map[i][j] == '*')
		return (0);
	if (map[i][j] == ' ')
		return (1);
	map[i][j] = '*';
	if (flood_fill(map, i - 1, j, rows, cols) || flood_fill(map, i + 1, j, rows, cols) ||
		flood_fill(map, i, j - 1, rows, cols) || flood_fill(map, i, j + 1, rows, cols))
		return (1);
	return (0);
}

/*
IS_REACHABLE controlla se il carattere ' ' è raggiungibile dal personaggio (non vogliamo che lo sia).
scorre lungo la mappa e quando trova il carattere del player (N,S,E,W) chiama la funzione flood_fill che returna 1 se il carattere ' ' è raggiungibile.
*/
static int	is_reachable(char **map, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
				return (flood_fill(map, i, j, rows, cols));
			j++;
		}
		i++;
	}
	return (0);
}


/* CONTROLLO I CARATTERI DELLA MAPPA
scorro la matrice contenente la mappa e controllo che ci siano solo caratteri validi.
-se trovo un carattere non valido returno 1.
-incremento k se trovo un carattere corrispondente al player 
 (N,S,E,W) e se k > 1 (è stato inserito più di un player) returno 1.
-se non trovo errori returno 0.
*/
static int	check_characters(t_game *game)
{
	int		y;
	int		x;
	int		k;
	char	c;
	
	y = 0;
	k = 0;
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
				k++;
				game->player.y = y;
				game->player.x = x;
			}
			if (k > 1)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
/*
la funzione CHECK MAP
- conta per prima cosa le righe e le colonne della mappa (così da poterle passare alla funzione is_reachable).
- dopodiché:
	- se la funzione check_characters ritorna 1 (errore) 
	- o is closed returna 0 (!is_closed = non è chiusa eheheh)
	- o la funzione is_reachable returna 1 (quindi il carattere ' ' è raggiungibile dal personaggio, il che non va bene) 
	-> returno 0 (errore)
- altrimenti returno 1 (success).
*/
int	check_map(t_game *game)
{
	int rows; 
	int cols;

	rows = 0;
	while (game->map.map_mat[rows])
		rows++;
	cols = 0;
	while (game->map.map_mat[0][cols])
		cols++;
	if (check_characters(game) || !is_closed(*game)
		|| is_reachable(game->map.map_mat, rows, cols))
		return (0);
	return (1);
}
