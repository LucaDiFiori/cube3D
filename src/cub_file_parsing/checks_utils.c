/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:13:25 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/06/23 16:13:21 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void check_extension(char *map_path, t_game *game_struct)
{
	int	len;

	len = ft_strlen(map_path);
	if (map_path[len - 1] == 'b' && map_path[len - 2] == 'u'
	&& map_path[len - 3] == 'c' && map_path[len - 4] == '.')
	{
		game_struct->map.map_path = map_path;
		return ;
	}
	else
		quit_and_free(EXT_ERR, 1, game_struct);
}

int check_missing_info(t_game *g_s)
{
	if (!g_s->map.wall_text.north || !g_s->map.wall_text.south
		|| !g_s->map.wall_text.east || !g_s->map.wall_text.west
		|| !g_s->map.wall_text.c_rgb.r || !g_s->map.wall_text.c_rgb.g 
		|| !g_s->map.wall_text.c_rgb.b || !g_s->map.wall_text.f_rgb.r 
		|| !g_s->map.wall_text.f_rgb.g || !g_s->map.wall_text.f_rgb.b)
		return (1);
	return (0);
}
