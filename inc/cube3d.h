/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-21 11:16:22 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-21 11:16:22 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <stdarg.h>
#include "../src/gnl/get_next_line.h"

#define EXT_ERR "Invalid file extension -> Use .cub file\n"
#define ARG_ERR "Invalid number of arguments -> Use example: ./cub3D map.cub"

typedef struct	s_map
{
	char	*map_path;
}	t_map;

typedef struct s_game
{
	t_map	map;
}	t_game;



/*MINILIB*/
/*minilib*/
size_t	ft_strlen(const char *s);

/*CHECKS*/
/*check_utils*/
int check_extension(char *map_path, t_game *game_struct);

/*PRINTF*/
int	ft_printf(const char *format, ...);

/*UTILS*/
void	print_error(char *error);
int quit_and_free(char *error, int err_type, t_game *game_struct);

/*INIT*/
void	init_game_struct(t_game *game_struct);







#endif