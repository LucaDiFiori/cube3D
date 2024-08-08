/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-26 09:31:22 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-26 09:31:22 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

/*
	IDEA:
	1: Find the first line of the map
	2: Read the map line by line and join them into a single string
	3: Split the string into a matrix of strings
	4: Assign the matrix to the map_mat field of the game struct
	5: Return 1 if the map was successfully extracted, 0 otherwise */



/**
 * Function: find_and_read_first_line
 * ----------------------------------
 * This function finds and reads the first line of the map from the file descriptor.
 * It uses the find_map function to locate the first line of the map and returns 
 * it as a string.
 *
 * Parameters:
 *  - map_fd: The file descriptor of the map file to be read.
 *
 * Returns:
 *  - A pointer to the first line of the map if successful.
 *  - NULL if the map is not found or an error occurs.
 *
 * Process:
 *  1. Calls the find_map function to locate the first line of the map.
 *  2. If the line is not found, returns NULL.
 *  3. Returns the found line.
 */
static char *find_and_read_first_line(int map_fd)
{
    char	*line;

    line = find_map(map_fd);
    if (!line)
        return (NULL);
    return (line);
}

/**
 * Function: check_for_missing_line
 * -------------------------------
 * This function checks if there is a missing line in the map by reading the next line
 * from the file descriptor and verifying if the first character is a digit. 
 * It is used to ensure that all lines in the map are properly formatted and 
 * no lines are missing.
 *
 * Parameters:
 *  - map_fd: The file descriptor of the map file to be read.
 *
 * Returns:
 *  - 1 if a line is found and the first character is a digit (indicating a missing line).
 *  - 0 if no such line is found or if the line does not start with a digit.
 *
 * Process:
 *  1. Reads the next line from the file descriptor using get_next_line.
 *  2. Checks if the line exists and if its first character is a digit using ft_isdigit.
 *  3. If the conditions are met, the function frees the line, resets the get_next_line
 *     static variable, and returns 1 to indicate a missing line.
 *  4. If the conditions are not met, the function frees the line and returns 0.
 */
static int check_for_missing_line(int map_fd)
{
    char	*line;

    line = get_next_line(map_fd);
    if (line && ft_isdigit(line[0]))
    {
        free(line);
        get_next_line(-2);
        return (1);
    }
    free(line);
    get_next_line(-2);
    return (0);
}

/**
 * Function: split_and_assign_map
 * -------------------------------
 * This function splits the concatenated map string into a matrix of strings 
 * based on newline characters and assigns the resulting matrix to the 
 * `map_mat` field of the `t_game` structure. After assignment, it frees the 
 * memory allocated for the joined map string. If memory allocation for the 
 * matrix fails, it calls the `quit_and_free` function to handle the error.
 *
 * Parameters:
 *  - g_s: A pointer to the `t_game` structure where the map matrix will be assigned.
 *  - join_map: A single string containing the entire map, which will be split into lines.
 *
 * Process:
 *  1. Splits the `join_map` string into a matrix of strings using `ft_split`, 
 *     where each line of the map becomes an element in the matrix.
 *  2. Frees the `join_map` string as it is no longer needed after splitting.
 *  3. Checks if the `map_mat` field of the `t_game` structure has been successfully 
 *     allocated. If the allocation failed (i.e., `map_mat` is NULL), it calls 
 *     `quit_and_free` with an appropriate error message and code to handle the error.
 */
static void split_and_assign_map(t_game *g_s, char *join_map)
{
    g_s->map.map_mat = ft_split(join_map, '\n');
    free(join_map);
    if (!g_s->map.map_mat)
        quit_and_free(MALLOC_ERR, 2, g_s);
}

/**
 * Function: parse_texture
 * -----------------------
 * Extracts the texture path from a given line by removing spaces at the beginning 
 * and within the line using the `remove_space_strcpy` function. If the texture 
 * path is successfully extracted, the function increments the `count_info` variable 
 * and returns 1; otherwise, it returns 0.
 * 
 * Parameters:
 *  - line: A string containing the line from which the texture path should be extracted.
 *  - texture: A pointer to the texture path string to be updated with the extracted path.
 *  - count_info: A pointer to an integer that tracks the number of successfully parsed 
 *                texture paths. This variable is incremented if the texture path is 
 *                extracted successfully.
 *
 * Returns:
 *  - An integer indicating the success or failure of the texture path extraction:
 *    - Returns 1 if the texture path is extracted successfully.
 *    - Returns 0 if the extraction fails (e.g., due to memory allocation failure).
 *
 * Process:
 *  - Calls `remove_space_strcpy` to remove leading and internal spaces from the line 
 *    and extract the texture path.
 *  - Checks if the texture path was successfully extracted (i.e., the result is not NULL).
 *  - Increments the `count_info` variable if the extraction was successful.
 *  - Returns 1 for successful extraction or 0 for failure.
 */
int extract_map(t_game *g_s, int map_fd)
{
    char	*first_line;
    char	*join_map;

    first_line = find_and_read_first_line(map_fd);
    if (!first_line)
        return (0);

    join_map = join_lines(map_fd, first_line);
    if (!join_map)
    {
        quit_and_free(MALLOC_ERR, 2, g_s);
        return (0);
    }

    if (check_for_missing_line(map_fd))
    {
        free(join_map);
        return (0);
    }
    split_and_assign_map(g_s, join_map);
    return (1);
}