/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 13:10:22 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-08-07 13:10:22 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../inc/cube3d.h"

/**
 * Function: join_lines
 * --------------------
 * Reads the map line by line from the file descriptor and joins them into a single 
 * string. The map reading starts from the provided first line.
 *
 * Parameters:
 *  - map_fd: The file descriptor of the map file to be read.
 *  - first_line: The first line of the map that has already been read.
 *
 * Returns:
 *  - A pointer to a single string containing the entire map if successful.
 *  - NULL if an error occurs during the process.
 *
 * Process:
 *  1. Initializes the join_map string to NULL and sets the current line to first_line.
 *  2. Loops through the lines until a line is empty or a newline character is encountered.
 *  3. Joins the current line to the join_map string using ft_strjoin.
 *  4. Handles any memory allocation errors during the joining process.
 *  5. Frees the current line and reads the next line from the file.
 *  6. After exiting the loop, ensures the last line read is freed.
 *  7. Clears the static variable in get_next_line and returns the joined map string.
 */
char *join_lines(int map_fd, char *first_line)
{
    char *join_map;
    char *line;
    char *temp;

	join_map = NULL;
	line = first_line;
    while (line && line[0] != '\n')
    {
        temp = ft_strjoin(join_map, line);
        if (!temp)
        {
            if (join_map)
                free(join_map);
            free(line);
            get_next_line(-2);
            return (NULL);
        }
        join_map = temp;
        free(line);
        line = get_next_line(map_fd);
    }
    if(line)
        free(line);
    get_next_line(-2);
    return join_map;
}

/**
 * Function: find_map
 * ------------------
 * Searches for the beginning of the map within the file by skipping empty lines.
 *
 * Parameters:
 *  - map_fd: The file descriptor of the map file to be read.
 *
 * Returns:
 *  - A pointer to the first line of the map if found.
 *  - NULL if the map is not found before the end of the file.
 *
 * Process:
 *  1. Continuously reads lines from the file, skipping empty lines or lines containing 
 *     only a newline character, until the first line of the map is found or the end of 
 *     the file is reached.
 *  2. If the end of the file is reached before finding the map, frees the current line 
 *     and clears the static variable in get_next_line, then returns NULL.
 *  3. If the map is found, clears the static variable in get_next_line and returns the 
 *     first line of the map.
 */
char  *find_map( int map_fd)
{
	char	*line;

	line = get_next_line(map_fd);
	while (line && (!*line || line[0] == '\n'))
	{
		free(line);
		line = get_next_line(map_fd);
	}
	if (!line)
	{
		free(line);
		get_next_line(-2);
		return (NULL);
	}
	get_next_line(-2);
	return (line);
}