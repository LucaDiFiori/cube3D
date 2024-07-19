/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaestri <cmaestri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:28:53 by cmaestri          #+#    #+#             */
/*   Updated: 2024/07/19 11:43:40 by cmaestri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static void start_raycasting(t_raycast *ray, int x)
{
    init_raycasting(ray);
    ray->camera_x = 2 * x / (double)RES_X - 1;
	ray->dir_x = ray->player.dir_vec[0] + ray->player.plane_vec[0] * ray->camera_x;
	ray->dir_y = ray->player.dir_vec[1] + ray->player.plane_vec[1] * ray->camera_x;
	ray->map_x = (int)ray->player.x;
	ray->map_y = (int)ray->player.y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
    
}

static void	init_dda(t_raycast *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->player.x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->player.y) * ray->delta_dist_y;
	}
}

static void	dda_loop(t_raycast *ray, t_map *map)
{
	bool    found_wall;

	found_wall = false;
	while (!found_wall)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_y < 0.25
			|| ray->map_x < 0.25
			|| ray->map_y > map->map_y - 0.25
			|| ray->map_x > map->map_x - 1.25)
			break ;
		else if (map->map_mat[ray->map_y][ray->map_x] > '0')
			found_wall = true;
	}
}