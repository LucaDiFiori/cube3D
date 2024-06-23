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

#define EXT_ERR "Invalid file extension. '.cub' file needed\n"
#define ARG_ERR "Invalid number of arguments -> Use example: ./cub3D map.cub"
#define OPEN_ERR "opening the map file"
#define DATA_ERR "bad textures data in the file"

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct	s_wal_text
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*c_color;
	char 	*f_color;
	t_rgb	c_rgb;
	t_rgb	f_rgb;
}	t_wal_text;

typedef struct	s_map
{
	char		*map_path;
	t_wal_text	wal_text;
}	t_map;

typedef struct s_game
{
	t_map	map;
}	t_game;



/*MINILIB*/
/*minilib*/
int		ft_strlen(const char *s);
char	**ft_split(char *str, char c);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *src);
/*minilib_2*/
void	*ft_memcpy(void *dest, void *src, int n);
char	*ft_strstr(const char *source, const char *to_find);
void	remove_space_strcpy(char *copy, char *to_copy);


/*CHECKS*/
/*check_utils*/
void	check_extension(char *map_path, t_game *game_struct);
/*map_validation*/
void	validator(t_game *game_struct, char **argv);

/*PRINTF*/
int		ft_printf(const char *format, ...);

/*UTILS*/
void	print_error(char *error);
int		quit_and_free(char *error, int err_type, t_game *game_struct);

/*INIT*/
void	init_game_struct(t_game *game_struct);







#endif