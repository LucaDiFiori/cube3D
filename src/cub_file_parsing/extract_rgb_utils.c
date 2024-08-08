/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rgb_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-07 13:30:22 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-08-07 13:30:22 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

/**
 * Function: parse_rgb_value
 * --------------------------
 * Parses an RGB value from a given string. The function checks if the string consists 
 * solely of digits, converts it to an integer, and stores it in the provided `value` 
 * pointer. If the string contains any non-digit characters or is empty, the function 
 * returns 0. Otherwise, it returns 1.
 * 
 * Parameters:
 *  - temp_ptr: A string containing the RGB value to be parsed. It is expected to be 
 *               composed only of digits.
 *  - value: A pointer to an integer where the parsed RGB value will be stored.
 *
 * Returns:
 *  - An integer indicating the success or failure of the RGB value parsing:
 *    - Returns 1 if the RGB value is successfully parsed and stored.
 *    - Returns 0 if the string contains non-digit characters or is empty.
 *
 * Process:
 *  - Iterates through the characters in the string pointed to by `temp_ptr`.
 *  - Checks if each character is a digit. If any character is not a digit, returns 0.
 *  - If the string is valid (contains only digits and is not empty), converts the 
 *    string to an integer using `ft_atoi` and stores the result in the `value` pointer.
 *  - Returns 1 if the parsing was successful.
 */
int parse_rgb_value(char *temp_ptr, int *value)
{
    int	j;

	j = 0;
    while (temp_ptr[j] && temp_ptr[j] != '\n')
    {
        if (!ft_isdigit(temp_ptr[j]))
            return (0);
        j++;
    }
    if (!*temp_ptr)
        return 0;
    *value = ft_atoi(temp_ptr);
    return (1);
}

/**
 * Function: process_single_rgb_value
 * -----------------------------------
 * Processes a single RGB value from a given string based on the provided index. 
 * The function parses the value as an integer and assigns it to the appropriate 
 * field (red, green, or blue) in the `t_rgb` structure. If the index is invalid 
 * or the parsing fails, the function returns 0; otherwise, it returns 1.
 * 
 * Parameters:
 *  - temp_ptr: A string containing the RGB value to be processed. It should be 
 *               composed only of digits.
 *  - index: An integer indicating which RGB component to assign the parsed value to:
 *           - 0 for red component (`color->r`)
 *           - 1 for green component (`color->g`)
 *           - 2 for blue component (`color->b`)
 *  - color: A pointer to the `t_rgb` structure where the parsed value will be stored.
 *
 * Returns:
 *  - An integer indicating the success or failure of the RGB value processing:
 *    - Returns 1 if the RGB value is successfully parsed and assigned.
 *    - Returns 0 if the index is invalid or the parsing fails.
 *
 * Process:
 *  - Based on the provided index, calls `parse_rgb_value` to parse the RGB value 
 *    from the string pointed to by `temp_ptr`.
 *  - Assigns the parsed value to the corresponding field in the `t_rgb` structure:
 *    - For index 0, assigns to the red component.
 *    - For index 1, assigns to the green component.
 *    - For index 2, assigns to the blue component.
 *  - Returns 1 if the processing was successful, otherwise returns 0.
 */
int process_single_rgb_value(char *temp_ptr, int index, t_rgb *color)
{
    if (index == 0)
        return parse_rgb_value(temp_ptr, &color->r);
    else if (index == 1)
        return parse_rgb_value(temp_ptr, &color->g);
    else if (index == 2)
        return parse_rgb_value(temp_ptr, &color->b);
    else
        return (0);
}