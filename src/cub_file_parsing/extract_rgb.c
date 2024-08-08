/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-26 07:25:59 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-26 07:25:59 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"


/**
 * Function: split_and_validate_line
 * ---------------------------------
 * Splits a given line of text into an array of strings based on the comma delimiter 
 * and validates the split operation.
 * 
 * Parameters:
 *  - line: A string containing the line to be split. This line is expected to contain 
 *          RGB values separated by commas.
 *  - split_line: A pointer to an array of strings that will be allocated and populated 
 *                 by splitting the `line` at each comma.
 * 
 * Returns:
 *  - An integer indicating the success or failure of the split operation:
 *    - Returns 1 if the line is successfully split into an array of strings.
 *    - Returns 0 if the split operation fails (e.g., due to memory allocation issues).
 * 
 * Process:
 *  - Calls `ft_split` to split the `line` into an array of strings using commas as delimiters.
 *  - Checks if the result of `ft_split` is NULL, indicating a failure in the split operation.
 *  - Returns 1 if the splitting was successful and `*split_line` is not NULL.
 *  - Returns 0 if `ft_split` fails and `*split_line` is NULL.

 */
int	split_and_validate_line(char *line, char ***split_line) 
{
    *split_line = ft_split(line, ',');
    if (!*split_line)
        return (0);
    return (1);
}

/**
 * Function: process_rgb_values
 * -----------------------------
 * Extracts and converts RGB values from the provided array of strings into 
 * integer values for the `t_rgb` structure. Each string in the array corresponds 
 * to one of the RGB components (red, green, or blue). The function processes 
 * these values and assigns them to the appropriate fields in the `t_rgb` structure.
 * 
 * Parameters:
 *  - split_line: An array of strings where each string represents a part of the 
 *                 RGB value. Each element of the array corresponds to one RGB 
 *                 component: red, green, or blue.
 *  - color: A pointer to the `t_rgb` structure where the extracted RGB values 
 *           will be stored.
 * 
 * Returns:
 *  - An integer indicating the success or failure of the RGB value extraction:
 *    - Returns 1 if all three RGB components are successfully processed.
 *    - Returns 0 if any of the components fails to be processed.
 * 
 * Process:
 *  - Iterates over the `split_line` array and processes each string to extract 
 *    the RGB value.
 *  - Uses `temp_ptr` to temporarily hold each string from `split_line` while 
 *    skipping leading spaces and tabs.
 *  - Calls `process_single_rgb_value` to parse and assign each RGB component based 
 *    on its index.
 *  - Returns 1 if all three RGB components (red, green, blue) are successfully 
 *    processed (i.e., the array has exactly three elements).
 *  - Returns 0 if the processing fails or if the array does not contain exactly 
 *    three elements.
 */
static int process_rgb_values(char **split_line, t_rgb *color) 
{
    char	*temp_ptr;
    int		i;

    i = 0;
    while (split_line[i] != NULL) 
    {
        temp_ptr = split_line[i];
        while (*temp_ptr && (*temp_ptr == ' ' || *temp_ptr == '\t'))
            temp_ptr++;

        if (!process_single_rgb_value(temp_ptr, i, color))
            return (0);
        i++;
    }
    if (i == 3)
        return (1);
    else
        return (0);
}



/*function to check if the rgb values are in the range 0-255
  RETURN: - 1 if the values are valid
		  - 0 if the values are not valid*/
static int validate_rgb_range(t_rgb color) 
{
    if (color.r < 0 || color.r > 255 || color.g < 0 || color.g > 255
		|| color.b < 0 || color.b > 255)
        return (0);
    return (1);
}


/**
 * Function: extract_rgb
 * ----------------------
 * Extracts and validates RGB color values from a given line of text.
 * The function splits the line into individual RGB values, converts these values 
 * to integers, and checks if they fall within the valid RGB range (0-255). 
 * It updates the `color` structure with the extracted RGB values if successful.
 * 
 * Parameters:
 *  - color: A pointer to a `t_rgb` structure where the extracted RGB values will be stored.
 *  - line: A string containing the line from which the RGB values should be extracted.
 * 
 * Returns:
 *  - An integer indicating the success or failure of the RGB extraction and validation:
 *    - Returns 1 if the RGB values are successfully extracted, converted, and validated.
 *    - Returns 0 if any of the following occur:
 *      - The line cannot be split into RGB values.
 *      - The RGB values cannot be processed or are out of the valid range.
 * 
 * Process:
 *  - Calls `split_and_validate_line` to split the line into RGB values based on commas.
 *  - If splitting fails, returns 0.
 *  - Uses `process_rgb_values` to convert the split values to integers and populate the `color` structure.
 *  - If processing fails, frees the allocated memory and returns 0.
 *  - Calls `validate_rgb_range` to ensure the RGB values fall within the valid range (0-255).
 *  - If validation fails, frees the allocated memory and returns 0.
 *  - Frees the allocated memory for the split line and returns 1 if all steps are successful.
 */
int extract_rgb(t_rgb *color, char *line) 
{
    char	**split_line;

    if (!split_and_validate_line(line, &split_line))
        return (0);
    if (!process_rgb_values(split_line, color)) 
    {
        free_matrix((void **)split_line);
        return (0);
    }
    if (!validate_rgb_range(*color)) 
    {
        free_matrix((void **)split_line);
        return (0);
    }
    free_matrix((void **)split_line);
    return (1);
}