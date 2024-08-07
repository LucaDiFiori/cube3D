/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubemacro.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-07-14 06:10:23 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-07-14 06:10:23 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBEMACRO_H
# define CUBEMACRO_H

#define RES_X 1440
#define RES_Y 960
#define MINI_RES_X (RES_X / 5)
#define MINI_RES_Y (RES_Y / 5)

#define TEXT_WIDTH 64
#define TEXT_HEIGHT 64

#define FOV 0.66
#define FPS_LIMIT 16.6
#define MOVESPEED 3.0
#define ROTSPEED 1.5

#define EXT_ERR "Invalid file extension. '.cub' file needed\n"
#define ARG_ERR "Invalid number of arguments -> Use example: ./cub3D map.cub"
#define OPEN_ERR "opening the map file"
#define DATA_ERR "bad textures data in the file"
#define MALLOC_ERR "malloc error"
#define MAP_ERR "map error"
#define MLX_ERR "mlx initialization error"
#define INIT_IMG_ERR "mlx_xpm_file_to_image error"
#define MEMCPY_ERR "memcpy error"

#define DOOR_PATH "textures/wolfenstein/door.xpm"
#define DOOR_OPEN_PATH "textures/wolfenstein/dooropen.xpm"

#endif