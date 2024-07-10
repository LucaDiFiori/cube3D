/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-03 12:51:03 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-07-03 12:51:03 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/cube3d.h"

/* CONTROLLO I CARATTERI DELLA MAPPA
scorro la matrice contenente la mappa e controllo che ci siano solo caratteri validi.
-se trovo un carattere non valido returno 1.
-incremento k se trovo un carattere corrispondente al player (N,S,E,W) e se k > 1 (è stato inserito più di un player) returno 1.
-se non trovo errori returno 0.
*/
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
	// !!!!!!!!! poi possiamo settare la posizione del player a c direttamente qui se ci va !!!!!!!!!
}


/* CONTROLLO LE RIGHE
- il primo loop controlla la prima riga
- il secondo cerca l'ultima riga (k)
- il terzo controlla l'ultima riga
- se il carattere non è 1 o spazio returno 0 (errore), altrimenti returno 1 (success).
*/
static int	check_rows(t_game game)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (game.map.map_mat[0][i])
	{
		if (game.map.map_mat[0][i] != '1' && game.map.map_mat[0][i] != ' ')
			return (0);
		i++;
	}
	i = 0;
	while (game.map.map_mat[i])
		i++;
	k = i - 1;
	while (game.map.map_mat[k][j])
	{
		if (game.map.map_mat[k][j] != '1' && game.map.map_mat[k][j] != ' ')
			return (0);
		j++;
	}
	return (1);
}

/* CONTROLLO LE COLONNE
- il primo while nestato controlla il primo carattere non spazio di ogni riga (se è uno spazio lo skippo)
- il secondo idem per l'ultimo carattere non spazio della riga
- se il carattere non è 1 returno 0 (errore), altrimenti returno 1 (success).
*/
static int	check_columns(t_game game)
{
	int	i;
	int	j;
	
	i = 0;
	while (game.map.map_mat[i])
	{
		j = 0;
		while (game.map.map_mat[i][j] == ' ')
			j++;
		if (game.map.map_mat[i][j] != '1')
			return 0;
		j = 0;
		while (game.map.map_mat[i][j])
			j++;
		j--;
		while (j >= 0 && game.map.map_mat[i][j] == ' ')
			j--;
		if (game.map.map_mat[i][j] != '1')
			return (0);
		i++;
	}
	return (1);
}
// se il controllo delle righe e delle colonne è andato a buon fine la mappa è chiusa e returno 1, altrimenti returno 0.
static int	is_closed(t_game game)
{
	if (!check_rows(game) || !check_columns(game))
		return (0);
	else
		return (1);
}

int	check_map(t_game game)
{
	if (check_characters(game) || !is_closed(game))
		return (1);
	return (0);
}
