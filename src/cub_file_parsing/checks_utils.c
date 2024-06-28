/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:13:25 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/06/24 12:52:20 by ldi-fior         ###   ########.fr       */
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


int is_map_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i] == ' ' || line[i] == '\t')
		;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

char *remove_space_strcpy(char *to_copy) 
{
    int		len;
    char	*copy; 
	char	*start;

    // Skip leading spaces
    while (*to_copy && (*to_copy == ' ' || *to_copy == '\t'))
        to_copy++;
    if (*to_copy == '\0' || !ft_isprint(*to_copy))
        return NULL; // Return NULL if the string is empty or contains only spaces

    len = ft_strlen(to_copy) + 1;
    copy = (char *)malloc(sizeof(char) * len);
    if (!copy) // Check if malloc failed
        return NULL;

    start = copy; // Save the start of the copy to return it later
    while (*to_copy) 
	{
        if (*to_copy != ' ' && ft_isprint(*to_copy)) 
		{
            *copy = *to_copy;
            copy++;
        }
        to_copy++;
    }
    *copy = '\0'; // Correctly terminate the string
    return (start); // Return the start of the allocated memory
}
