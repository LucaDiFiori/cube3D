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


/**
 * Function: check_missing_info
 * ------------------------------
 * Checks if all the necessary information to start the game has been saved in 
 * the game structure. The function verifies the presence of texture paths and 
 * color values for the ceiling and floor. If any required information is missing, 
 * the function returns 1; otherwise, it returns 0.
 * 
 * Parameters:
 *  - g_s: A pointer to the game structure (`t_game`) containing the map and 
 *         texture information.
 *
 * Returns:
 *  - An integer indicating whether any required information is missing:
 *    - Returns 1 if any texture paths (north, south, east, west) or RGB values 
 *      for the ceiling or floor are missing or not set.
 *    - Returns 0 if all required information is present.
 *
 * Process:
 *  - Checks if the texture paths for north, south, east, and west walls are set.
 *  - Checks if the RGB values for the ceiling (`c_rgb`) and floor (`f_rgb`) are set. 
 *    RGB values are considered set if none of the components (r, g, b) are equal to -1.
 *  - Returns 1 if any of these checks fail, indicating missing information.
 *  - Returns 0 if all required information is available.
 */
int check_missing_info(t_game *g_s)
{
	if (!g_s->map.text.north || !g_s->map.text.south
		|| !g_s->map.text.east || !g_s->map.text.west
		|| g_s->map.text.c_rgb.r == -1 || g_s->map.text.c_rgb.g == -1 
		|| g_s->map.text.c_rgb.b == -1 || g_s->map.text.f_rgb.r == -1
		|| g_s->map.text.f_rgb.g == -1 || g_s->map.text.f_rgb.b == -1)
		return (1);
	return (0);
}

/**
 * Function: cleanup
 * -------------------
 * Frees memory allocated for a line of text and a matrix of strings, as well 
 * as handling additional cleanup tasks based on the provided flag. This function 
 * is used in conjunction with `get_next_line` and `split` functions to ensure 
 * proper deallocation of resources and avoid memory leaks.
 * 
 * Parameters:
 *  - line: A pointer to the line of text to be freed.
 *  - split_line: A pointer to a matrix of strings to be freed.
 *  - flag: An integer indicating the type of cleanup required:
 *    - 1: Frees the line and matrix of strings. Sets `split_line` to NULL.
 *    - 2: Frees the line and matrix of strings. Calls `get_next_line(-2)` to 
 *         free static variables in `get_next_line`.
 *
 * Process:
 *  - If `flag` is 1:
 *    - Frees the memory allocated for the line of text.
 *    - Frees the memory allocated for the matrix of strings using `free_matrix`.
 *    - Sets the `split_line` pointer to NULL.
 *  - If `flag` is 2:
 *    - Frees the memory allocated for the line of text if it is not NULL.
 *    - Frees the memory allocated for the matrix of strings if it is not NULL.
 *    - Calls `get_next_line(-2)` to release any static variables used by 
 *      `get_next_line`.
 */
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


/**
 * Function: is_map_line
 * ------------------------
 * Determines if a given line from the map file is a valid map line based on its 
 * content. The function checks if the line, after ignoring leading spaces and tabs, 
 * starts with a valid map character ('1' for walls or '0' for empty spaces).
 * 
 * Parameters:
 *  - line: A string representing a single line from the map file.
 *
 * Returns:
 *  - An integer indicating whether the line is a valid map line:
 *    - Returns 1 if the line starts with '1' or '0' (valid map characters).
 *    - Returns 0 if the line does not start with a valid map character.
 *
 * Process:
 *  - Skips leading spaces and tabs in the line.
 *  - Checks the first non-skipped character to see if it is '1' or '0'.
 *  - Returns 1 if it matches a valid map character; otherwise, returns 0.
 * 
 * Note: This function helps in filtering out irrelevant lines and ensuring that
 *       only lines with valid map data are considered in the map processing.
 */
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

/**
 * Function: remove_space_strcpy
 * -------------------------------
 * Creates a copy of a string with all leading spaces and tabs removed, and
 * all remaining spaces within the string removed. This function allocates 
 * memory for the new string and returns it. If the input string is empty or
 * contains only non-printable characters, it returns NULL.
 * 
 * Parameters:
 *  - to_copy: The input string from which leading spaces and internal spaces 
 *    will be removed.
 *
 * Returns:
 *  - A pointer to the newly allocated string with spaces removed. 
 *    - Returns NULL if the input string is empty or contains only spaces or if 
 *      memory allocation fails.
 *
 * Process:
 *  - Skips leading spaces and tabs in the input string.
 *  - Checks if the string becomes empty or non-printable after removing leading 
 *    spaces; returns NULL if so.
 *  - Allocates memory for the new string, including space for the null terminator.
 *  - Copies characters from the original string to the new string, excluding 
 *    spaces and non-printable characters.
 *  - Adds a null terminator to the end of the new string.
 *  - Returns the pointer to the newly allocated string.
 * 
 * Note: The function helps in cleaning up the input string by removing unnecessary 
 *       spaces and ensuring only printable characters are included in the output.
 */
char *remove_space_strcpy(char *to_copy) 
{
    int     len;
    char    *copy; 
	char    *start;

    while (*to_copy && (*to_copy == ' ' || *to_copy == '\t'))
        to_copy++;
    if (*to_copy == '\0' || !ft_isprint(*to_copy))
        return (NULL);
    len = ft_strlen(to_copy) + 1;
    copy = (char *)malloc(sizeof(char) * len);
    if (!copy)
        return (NULL);
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