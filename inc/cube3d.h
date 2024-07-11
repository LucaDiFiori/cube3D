/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:16:22 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/06/24 12:52:58 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdarg.h>
#include <fcntl.h>
#include <limits.h>
#include "../src/gnl/get_next_line.h"
#include <stdbool.h>
#include <../mlx_linux/mlx.h>
#include <X11/Xlib.h>
#include "cubestruct.h"

#define RES_X 1440
#define RES_Y 960
//#define RES_X 960
//#define RES_Y 720
//#define RES_X 640
//#define RES_Y 480

/********************* */
#define MINI_RES_X (RES_X / 5)
#define MINI_RES_Y (RES_Y / 5)

#define PI 3.1415927

//0.0125
#define MOVESPEED 0.0050



/********************* */


#define EXT_ERR "Invalid file extension. '.cub' file needed\n"
#define ARG_ERR "Invalid number of arguments -> Use example: ./cub3D map.cub"
#define OPEN_ERR "opening the map file"
#define DATA_ERR "bad textures data in the file"
#define MALLOC_ERR "malloc error"
#define MAP_ERR "map error"
#define MLX_ERR "mlx initialization error"




/*MINILIB*/
/*minilib*/
int		ft_strlen(const char *s);
char	**ft_split(char *str, char c);
char	*ft_substr(char *s, int start, int len);
char	*ft_strdup(char *src);
/*minilib_2*/
void	*ft_memcpy(void *dest, void *src, int n);
char	*ft_strstr(const char *source, const char *to_find);
int		ft_isprint(int c);
int		ft_isdigit(int c);
char	*ft_strcpy(char *to_copy);
/*minilib_3*/
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
int		max(int a, int b);
int		min(int a, int b);

/*ft_atoi*/
int		ft_atoi(const char *nptr);


/*CUBE_FILE_PARSING*/
/*extract_rgb*/
int		extract_rgb(t_rgb *color, char *line);
/*extract_info_utils*/
void	check_extension(char *map_path, t_game *game_struct);
int		is_map_line(char *line);
char	*remove_space_strcpy(char *to_copy);
void	cleanup(char **line, char ***split_line, int flag);
/*extract_info*/
int		extract_info(t_game *g_s, int map_fd);
/*extract_map*/
int		extract_map(t_game *g_s, int map_fd);

/*MAP_CHECKS*/
int		check_map(t_game *game);
int		is_closed(t_game game);
/*utils*/
char	*duplicate_row(char *row, int current_cols, int cols);
char	**duplicate_map(char **map, int rows, int cols);
void	free_mapcopy(char **map, int rows);


/*PRINTF*/
int		ft_printf(const char *format, ...);


/*UTILS*/
void	print_error(char *error);
int		free_matrix(char **ptr_matric);
int		quit_and_free(char *error, int err_type, t_game *game_struct);
int		ft_close_x(t_game *ptr_game);


/*INIT*/
/*init_struct.c*/
void	init_game_struct(t_game *game_struct);
/*init_engine.c*/
int		init_engine(t_game *g_s);
void    init_asset(t_game *g);


/*MOVES*/
/*moves_utils*/
float degrees_to_radiant(float degrees);

/*moves*/
int     inputs(int key, t_game *g);
int key_press(int key, t_game *g);
int key_release(int key, t_game *g);
int handle_movement(t_game *g);




/********************************** */
/*MINIMAP*/
/*utils*/
void my_pixel_put(t_game *g, t_img_data *data, int x, int y, int color);
void draw_square(t_game *g, t_img_data *minimap, float start_x, float start_y, float size_x,
    float size_y);
void draw_circle(t_game *g, t_img_data *data, float center_x, float center_y,
    float radius, int color);
/*ray_casting*/
void draw_map(t_game *g_s);
void minimap_test(t_game *g_s);
void draw_player(t_game *g_s, float x, float y);
/************************************** */






#endif