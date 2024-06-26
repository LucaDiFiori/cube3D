/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:11:16 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/06/24 11:15:59 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	print_error(char *error)
{
	ft_printf("Error: %s\n", error);
}

int free_matrix(char **ptr_matric)
{
    int i;

    if (ptr_matric == NULL) // Aggiunta del controllo per ptr_matric NULL
        return (0);

    i = 0;
    while (ptr_matric[i] != NULL)
    {
        free(ptr_matric[i]);
        i++;
    }
    free(ptr_matric);
    return (0);
}


//void ft_destroy(t_game *game_struct)

static void destroy_struct(t_game *game_struct)
{		
	if (game_struct->map.wall_text.north)
		free(game_struct->map.wall_text.north);
	if (game_struct->map.wall_text.south)
		free(game_struct->map.wall_text.south);
	if (game_struct->map.wall_text.east)
		free(game_struct->map.wall_text.east);
	if (game_struct->map.wall_text.west)
		free(game_struct->map.wall_text.west);
	if (game_struct->map.map_mat != NULL)
		free_matrix(game_struct->map.map_mat);
}

int quit_and_free(char *error, int err_type, t_game *game_struct)
{
	if (err_type == 1)
		print_error(error);
	if (err_type == 2)
	{
		print_error(error);
		destroy_struct(game_struct);
	}
	
	exit (0);
}