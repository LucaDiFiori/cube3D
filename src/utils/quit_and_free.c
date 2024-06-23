/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-21 13:11:16 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-21 13:11:16 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	print_error(char *error)
{
	ft_printf("Error: %s\n", error);
}

int	free_matrix(char **ptr_matric)
{
	int i;

	i = 0;
	while (ptr_matric[i] != NULL)
	{
		free(ptr_matric[i]);
		i++;
	}
	free(ptr_matric);
	return (0);
}

//void free_map_matric(char **ptr_map, t_game *game_struct)

//void ft_destroy(t_game *game_struct)

int quit_and_free(char *error, int err_type, t_game *game_struct)
{
	(void)game_struct; //togliere questa linea/
	if (err_type == 1)
		print_error(error);
	
	exit (0);
}