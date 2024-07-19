/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaestri <cmaestri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:34:19 by cmaestri          #+#    #+#             */
/*   Updated: 2024/07/19 10:40:30 by cmaestri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static void init_raycasting(t_raycast *ray)
{
	ray->plane_x = 0;
	ray->dir_x = 0;
	ray->dir_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
    ray->wall_distance = 0;
	ray->wall_x = 0;
    ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->side_dist_x = 0;
	ray->side_dist_y = 0;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}