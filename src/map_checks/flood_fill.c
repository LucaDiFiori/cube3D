/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaestri <cmaestri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:56:00 by cmaestri          #+#    #+#             */
/*   Updated: 2024/07/17 10:45:18 by cmaestri         ###   ########.fr       */
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

int	flood_fill_spaces(char **map, int x, int y, int rows, int cols)
{
	if (x < 0 || x >= rows || y < 0 || y >= cols || map[x][y] == '1' || map[x][y] == '*')
		return (0);
	if (map[x][y] == ' ')
		return (1);
	map[x][y] = '*';
	if (flood_fill_spaces(map, x - 1, y, rows, cols) || flood_fill_spaces(map, x + 1, y, rows, cols) ||
		flood_fill_spaces(map, x, y - 1, rows, cols) || flood_fill_spaces(map, x, y + 1, rows, cols))
		return (1);
	return (0);
}

/* uguale ma controlla che l'uscita sia raggiungibile */
int	flood_fill_exit(char **map, int x, int y, int rows, int cols)
{
	if (x < 0 || x >= rows || y < 0 || y >= cols || map[x][y] == '1' || map[x][y] == '*')
		return (0);
	if (map[x][y] == 'U')
		return (1);
	map[x][y] = '*';
	if (flood_fill_exit(map, x - 1, y, rows, cols) || flood_fill_exit(map, x + 1, y, rows, cols) ||
		flood_fill_exit(map, x, y - 1, rows, cols) || flood_fill_exit(map, x, y + 1, rows, cols))
		return (1);
	return (0);
}

/*
IS_REACHABLE controlla se il carattere ' ' è raggiungibile dal personaggio (non vogliamo che lo sia)
e che, nel caso in cui ci sia l'uscita, essa sia anche raggiungibile.
scorre lungo la mappa e quando trova il carattere del player (N,S,E,W) 
- returna 1 (male) se lo spazio e' raggiungibile
- returna 1 (male) se c'e' un'uscita sulla mappa (num_exits != 0) && non e' pero' raggiungibile */

int	is_reachable(t_game *game, char **map, char **map2, int rows, int cols)
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
			{
				if (flood_fill_spaces(map, x, y, rows, cols))
					return (1);
				if (game->map.num_exits && !flood_fill_exit(map2, x, y, rows, cols))
					return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}