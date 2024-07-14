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
//#define RES_X 960
//#define RES_Y 720
//#define RES_X 640
//#define RES_Y 480

/********************* */
#define MINI_RES_X (RES_X / 5)
#define MINI_RES_Y (RES_Y / 5)

#define PI 3.1415927

//0.0125
#define MOVESPEED 0.0005



/********************* */


#define EXT_ERR "Invalid file extension. '.cub' file needed\n"
#define ARG_ERR "Invalid number of arguments -> Use example: ./cub3D map.cub"
#define OPEN_ERR "opening the map file"
#define DATA_ERR "bad textures data in the file"
#define MALLOC_ERR "malloc error"
#define MAP_ERR "map error"
#define MLX_ERR "mlx initialization error"

#endif