/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-30 15:01:13 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-30 15:01:13 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int init_engine(t_game *g_s)
{
	g_s->mlx.mlx_ptr = mlx_init();
	if (!g_s->mlx.mlx_ptr)
		return (0);
	g_s->mlx.win_ptr = mlx_new_window(g_s->mlx.mlx_ptr, RES_X, RES_Y, "cub3D");
	if (!g_s->mlx.win_ptr)
		return (0);
	return (1);
}
