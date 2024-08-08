/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-08 08:17:34 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-08-08 08:17:34 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	print_error(char *error)
{
	ft_printf("Error: %s\n", error);
}

int free_matrix(void **ptr_matric)
{
    int	i;

    i = 0;
    while (ptr_matric[i] != NULL)
    {
        free(ptr_matric[i]);
        i++;
    }
    free(ptr_matric);
    return (0);
}

int	ft_close_x(t_game *ptr_game)
{
	quit_and_free("See U <3", 0, ptr_game);
	return (0);
}