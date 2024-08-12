/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaestri <cmaestri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:16:22 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/07/15 15:06:21 by cmaestri         ###   ########.fr       */
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
#include <sys/time.h>
#include <fcntl.h>
#include <limits.h>
#include <float.h>
#include "../src/gnl/get_next_line.h"
#include <stdbool.h>
#include <../mlx/mlx.h>
#include <X11/Xlib.h> 
#include "cubestruct.h"


int				ft_strlen(const char *s);
char			**ft_split(char *str, char c);
char			*ft_substr(char *s, int start, int len);
char			*ft_strdup(char *src);
void			*ft_memcpy(void *dest, void *src, int n);
char			*ft_strstr(const char *source, const char *to_find);
int				ft_isprint(int c);
int				ft_isdigit(int c);
int	    		ft_isalpha(int c);
char			*ft_strcpy(char *to_copy);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strchr(const char *s, int c);
void			*ft_calloc(int count, int size);
int				ft_atoi(const char *nptr);
int				extract_rgb(t_rgb *color, char *line);
int				parse_rgb_value(char *temp_ptr, int *value);
int				process_single_rgb_value(char *temp_ptr, int index, t_rgb *color);
int				check_missing_info(t_game *g_s);
void			check_extension(char *map_path, t_game *game_struct);
int				is_map_line(char *line);
char			*remove_space_strcpy(char *to_copy);
void			cleanup(char **line, char ***split_line, int flag);
int				extract_info(t_game *g_s, int map_fd);
int				extract_map(t_game *g_s, int map_fd);
char			*join_lines(int map_fd, char *first_line);
char			*find_map( int map_fd);
int				check_map(t_game *game);
int				is_closed(t_game game);
void			find_rows_and_cols(t_map *map);
char			*duplicate_row(char *row, int current_cols, int cols);
char			**duplicate_map(char **map, int rows, int cols);
void			free_mapcopy(char **map, int rows);
void    		clear_matrix(int **matrix);
int				ft_printf(const char *format, ...);
void			print_error(char *error);
int				free_matrix(void **ptr_matric);
int				quit_and_free(char *error, int err_type, t_game *game_struct);
int				ft_close_x(t_game *ptr_game);
unsigned long	get_time_in_milliseconds();
void			draw_fps_counter(t_game *g);
void			init_game_struct(t_game *game_struct);
void			init_player_dir(t_game *g);
void			init_ray(t_game *g);
void			init_player_data(t_game *g);
int				init_engine(t_game *g_s);
void			init_img(t_img *img);
void			init_texture(t_game *g, t_img *img, char *path);
void			init_img_data(t_game *g, t_img *img, int width, int height);
void			init_fps_counter(t_game *g);
void			init_textures_mat(t_game *g);
int				move_forward(t_game *g);
int				move_backward(t_game *g);
int				move_left(t_game *g);
int				move_right(t_game *g);
int				rotate_player(t_game *g, double rotdir); 
int				handle_movement(t_game *g);
void			handle_input(t_game *g);
int				key_press(int keycode, t_game *g);
int				key_release(int keycode, t_game *g);
int				mouse_input(int x, int y, t_game *g);
void			my_pixel_put(t_game *g, int x, int y, int color);
void			fill_background(t_game *g, int width, int height, int bg_color);
void			draw_square(t_game *g, double start_x, double start_y);
void			draw_door(t_game *g, double start_x, double start_y);
void			draw_circle(t_game *g, double c_x, double c_y, int color);
void			init_minimap(t_game *g);
void			draw_map(t_game *g_s);
void			draw_minimap(t_game *g_s);
void			draw_player(t_game *g_s, double x, double y);
void			render(t_game *g);
void			raycasting(t_game *g);
void			find_wall_side(t_game *g);
void			draw_screen_pixels(t_game *g, int x);
int				is_reachable(t_game *game, char **map, int x, int y);

#endif