/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-21 11:13:25 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-21 11:13:25 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int check_extension(char *map_path, t_game *game_struct)
{
	int	len;

	len = ft_strlen(map_path);
	if (map_path[len - 1] == 'b' && map_path[len - 2] == 'u'
	&& map_path[len - 3] == 'c' && map_path[len - 4] == '.')
	{
		game_struct->map.map_path = map_path;
		return (1);
	}
	else
		return (quit_and_free(EXT_ERR, 1, game_struct));
}
