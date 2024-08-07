/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:35:04 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/06/24 12:50:36 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
 
#include "../../inc/cube3d.h"
/************************PRIMO PASSAGGIO DI NORMINETTATURA******************* */

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
 * 
 * Note: This function ensures that texture paths are properly formatted and counted, 
 */
static int parse_texture(char *line, char **texture, int *count_info)
{
    *texture = remove_space_strcpy(line);
    if (!(*texture))
        return (0);
    (*count_info)++;
    return (1);
}

/**
 * Function: parse_color
 * ---------------------
 * Extracts the RGB color from a given line. If the RGB color is successfully 
 * extracted, the function increments the `count_info` variable and returns 1; 
 * otherwise, it returns 0.
 * 
 * Parameters:
 *  - line: A string containing the line from which the RGB color should be extracted.
 *  - color: A pointer to the `t_rgb` structure that will be updated with the extracted 
 *           RGB values.
 *  - count_info: A pointer to an integer that tracks the number of successfully parsed 
 *                color values. This variable is incremented if the RGB color is 
 *                extracted successfully.
 *
 * Returns:
 *  - An integer indicating the success or failure of the RGB color extraction:
 *    - Returns 1 if the RGB color is extracted successfully.
 *    - Returns 0 if the extraction fails.
 *
 * Process:
 *  - Calls `extract_rgb` to parse the RGB values from the line and store them in the `color` structure.
 *  - Checks if the RGB extraction was successful (i.e., the `extract_rgb` function returns a non-zero value).
 *  - Increments the `count_info` variable if the extraction was successful.
 *  - Returns 1 for successful extraction or 0 for failure.
 */
static int parse_color(char *line, t_rgb *color, int *count_info)
{
    if (!extract_rgb(color, line))
        return (0);
    (*count_info)++;
    return (1);
}

/**
 * Function: parse_line
 * --------------------
 * Parses a line extracted from the file to determine if it is a texture or color line. 
 * Depending on the line type, the function calls either `parse_texture` to extract the 
 * texture path or `parse_color` to extract the RGB color.
 * 
 * Parameters:
 *  - line: A string containing the line to be parsed.
 *  - g_s: A pointer to the `t_game` structure where the parsed information will be stored.
 *  - count_info: A pointer to an integer that tracks the number of successfully parsed 
 *                texture and color values. This variable is incremented if the extraction 
 *                is successful.
 *  - split_line: An array of strings resulting from splitting the line, used to identify 
 *                the type of line (texture or color).
 *
 * Returns:
 *  - An integer indicating the success or failure of the parsing:
 *    - Returns 1 if the line is successfully parsed.
 *    - Returns 0 if the parsing fails (e.g., due to invalid format or memory allocation failure).
 *
 * Process:
 *  - Checks the first two characters of `split_line[0]` to determine the type of texture
 *  - Calls `parse_texture` with the appropriate texture path if the line is a texture line.
 *  - Checks the first character of `split_line[0]` to determine the type of color
 *  - Calls `parse_color` with the appropriate RGB color if the line is a color line.
 *  - Returns 1 if the line is successfully parsed and the corresponding value is extracted.
 *  - Returns 0 if the extraction fails.
 */
static int  parse_line(char *line, t_game *g_s, int *count_info, char **split_line)
{
    if (split_line[0][0] == 'N' && split_line[0][1] == 'O')
        return (parse_texture(line + 2, &g_s->map.text.north, count_info));
    else if (split_line[0][0] == 'S' && split_line[0][1] == 'O')
        return (parse_texture(line + 2, &g_s->map.text.south, count_info));
    else if (split_line[0][0] == 'E' && split_line[0][1] == 'A')
        return (parse_texture(line + 2, &g_s->map.text.east, count_info));
    else if (split_line[0][0] == 'W' && split_line[0][1] == 'E')
        return (parse_texture(line + 2, &g_s->map.text.west, count_info));
    else if (split_line[0][0] == 'F')
        return (parse_color(line + 1, &g_s->map.text.f_rgb, count_info));
    else if (split_line[0][0] == 'C')
        return (parse_color(line + 1, &g_s->map.text.c_rgb, count_info));
    return (1);
}

/**
 * Function: rgb_to_int
 * --------------------
 * Converts the RGB values stored in the `t_rgb` structure into a single integer value
 * for both the ceiling and floor colors. The resulting integer values are stored in
 * the game structure.
 *
 * Parameters:
 *  - g: A pointer to the `t_game` structure containing the RGB values for the ceiling 
 *       and floor colors.
 *
 * Process:
 *  - The function retrieves the RGB values for the ceiling and floor from `g->map.text.c_rgb`
 *    and `g->map.text.f_rgb`, respectively.
 *  - Each color component (red, green, blue) is shifted to its appropriate position:
 *    - Red is shifted left by 16 bits.
 *    - Green is shifted left by 8 bits.
 *    - Blue remains in its original position.
 *  - The shifted values are combined using the bitwise OR operator to form a single 
 *    integer value representing the color.
 *  - The resulting integer values are stored in `g->map.c_color` for the ceiling color 
 *    and `g->map.f_color` for the floor color.
 */
static void rgb_to_int(t_game *g)
{
    g->map.c_color = (g->map.text.c_rgb.r << 16) + (g->map.text.c_rgb.g << 8) +\
        g->map.text.c_rgb.b;
    g->map.f_color = (g->map.text.f_rgb.r << 16) + (g->map.text.f_rgb.g << 8) +\
        g->map.text.f_rgb.b;
}

/**
 * Function: extract_info
 * ----------------------
 * Extracts necessary information from the map file and saves it into the game structure.
 * The function reads the file line by line, parsing textures and colors, and checks for
 * the completeness of the information.
 *
 * Parameters:
 *  - g_s: A pointer to the `t_game` structure where the parsed information will be stored.
 *  - map_fd: The file descriptor of the map file to be read.
 *
 * Returns:
 *  - 1 if the information is successfully extracted and complete.
 *  - 0 if there is an error or the information is incomplete.
 *
 * Process:
 *  - Reads the first line of the file.
 *  - While there are lines to read and the necessary information is incomplete:
 *    - Splits the line by spaces.
 *    - Parses the line to extract textures and colors.
 *    - Breaks the loop if a map line is encountered.
 *    - Cleans up the allocated memory for the line and the split result.
 *    - Reads the next line.
 *  - Cleans up the remaining line and split result after exiting the loop.
 *  - Checks if all required information is collected and complete.
 *  - Converts the RGB values to integer colors for the ceiling and floor.
 */
int extract_info(t_game *g_s, int map_fd)
{
    char    *line;
    int		count_info;
	char	**split_line;

	count_info = 0;
    line = get_next_line(map_fd);
    if (!line)
        return (0);
    while (line != NULL && check_missing_info(g_s))
    {
		split_line = ft_split(line, ' ');
		if (!split_line)
			break;	
        if (!parse_line(line, g_s, &count_info, split_line))
            break;
        if (is_map_line(line))
            break;
        cleanup(&line, &split_line, 1);
        line = get_next_line(map_fd);
    }
    cleanup(&line, &split_line, 2);
    if (count_info != 6 || check_missing_info(g_s))
        return (0);
    rgb_to_int(g_s);
    return (1);
}