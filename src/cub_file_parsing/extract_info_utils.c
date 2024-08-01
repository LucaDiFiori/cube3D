/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_validation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:51:49 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/06/24 12:51:49 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

/*
  Function use in "extract_info" to free the memory allocated in each 
  iteration by the get_next_line function and the split function 
  
  NOTE: get_next_line(-2) is used to free the static variable in get_next_line*/
void cleanup(char **line, char ***split_line, int flag)
{
	if (flag == 1)
	{
		free(*line);
		free_matrix((void **)*split_line);
		*split_line = NULL;
	}
	else if (flag == 2)
	{
		if (*line)
			free(*line);
		if (*split_line)
			free_matrix((void **)*split_line);
		get_next_line(-2);
	}
}

/*
	Function to check the file extension.
	If the extension is correct, the path is saved in the game_struct
	Otherwise the program quits with an error message */
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

/*
	function use in extract_info to check if the line extracted from the
	file is a map line or not */
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

/*
	Function to remove spaces from a string and copy it into a new allocated memory
	Returns NULL if the string is empty or contains only spaces

	89-91: Skip leading spaces, tabs and capital letters
	92-93: Check if the string is empty or contains only spaces, if so return NULL
	93-96: Allocate memory for the new string
	98: Save the start of the copy to return it later
	99-108: Copy the string into the new allocated memory, 
	        skipping spaces and non-printable characters
*/
char *remove_space_strcpy(char *to_copy) 
{
    int		len;
    char	*copy; 
	char	*start;

    while (*to_copy && (*to_copy == ' ' || *to_copy == '\t'
		|| (*to_copy >= 65 && *to_copy <= 90)))
        to_copy++;
    if (*to_copy == '\0' || !ft_isprint(*to_copy))
        return NULL;
    len = ft_strlen(to_copy) + 1;
    copy = (char *)malloc(sizeof(char) * len);
    if (!copy)
        return NULL;
    start = copy;
    while (*to_copy) 
	{
        if (*to_copy != ' ' && ft_isprint(*to_copy)) 
		{
            *copy = *to_copy;
            copy++;
        }
        to_copy++;
    }
    *copy = '\0';
    return (start);
}