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
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdarg.h>
#include <fcntl.h>
#include <limits.h>
#include "../src/gnl/get_next_line.h"
#include <stdbool.h>
#include <../mlx_linux/mlx.h>

#define RES_X 1440
#define RES_Y 960
//#define RES_X 960
//#define RES_Y 720
//#define RES_X 640
//#define RES_Y 480

/********************* */
#define MINI_RES_X (RES_X / 5)
#define MINI_RES_Y (RES_Y / 5)



/********************* */


#define EXT_ERR "Invalid file extension. '.cub' file needed\n"
#define ARG_ERR "Invalid number of arguments -> Use example: ./cub3D map.cub"
#define OPEN_ERR "opening the map file"
#define DATA_ERR "bad textures data in the file"
#define MALLOC_ERR "malloc error"
#define MAP_ERR "map error"
#define MLX_ERR "mlx initialization error"



/************************************** */


typedef struct	s_minimap 
{
	void	*img; //puntatore generico per l'immagine.
	char	*addr; //puntatore ai dati dell'immagine restituite da mlx_get_data_addr
	int		bpp; //bit per pixel.
	int		line_length; //dimensione di una linea dell'immagine in byte.
	int		endian; //ordine dei byte (endianess).
	
	
	int		minimap_width;
	int		minimap_height;

	int		view_size;
	int		cell_width;
	int		cell_height;
}				t_minimap;
/************************************** */







typedef struct s_asset
{
	float	x;
	float	y;
}	t_asset;


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
	t_rgb	c_rgb;
	t_rgb	f_rgb;
}	t_wal_text;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct	s_map
{
	char		*map_path;
	char		**map_mat;
	int			map_x;
	int			map_y;
	t_wal_text	wall_text;


}	t_map;

typedef struct s_game
{
	t_map	map;
	t_mlx	mlx;
	t_asset player;

	/********************* */
	t_minimap minimap;



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





/********************************** */
/*MINIMAP*/
/*utils*/
void my_pixel_put(t_minimap *data, int x, int y, int color);
void draw_square(t_minimap *minimap, float start_x, float start_y, float size_x,
    float size_y);
void draw_circle(t_minimap *minimap, float center_x, float center_y,
    float radius, int color);
/*ray_casting*/
void minimap_test(t_game *g_s);
/************************************** */






#endif