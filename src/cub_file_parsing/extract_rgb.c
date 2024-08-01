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

/*split function use to split the rgb values from the cub file
  RETURN: - 1 if success
		  - 0 if fail */
int	split_and_validate_line(char *line, char ***split_line) 
{
    *split_line = ft_split(line, ',');
    if (!*split_line)
        return (0);
    return (1);
}

/*Funtion to extract (convert to int) the rgb values from the cub file
  RETURN: - 1 if success
		  - 0 if fail

  NOTE: I'm using a temp_ptr because otherwise I should modify the pointer
		split_line (for example doing split_line++) and this causes problems
		when I call the free() function:
		This is because being an array of pointers, by doing split_line++ I am
		pointing to the next string and no longer to the first element.

  44: for each string in the split_line array
  46: copy the i-th string of the split_line array in temp_ptr
  47: while the character pointed by temp_ptr is not a digit, increment temp_ptr
  48: if the character pointed by temp_ptr is '\0' return 0 (error: invalid string)
  54 - 58: if i is 0, 1 or 2, convert the string pointed by temp_ptr to an integer
           and assign it to the corresponding field of the color struct
  60: if i is different from 0, 1 or 2, return 0 (error: too many values)
  66-70: check if the number of values is extactly 3 and return 1 if true, 0 otherwise
*/
static int process_rgb_values(char **split_line, t_rgb *color) 
{
    char *temp_ptr;
    int j; 
    int i;

    i = 0;
    while (split_line[i] != NULL) 
	{
        temp_ptr = split_line[i];
        while (*temp_ptr && (*temp_ptr == ' ' || *temp_ptr == '\t'))
            temp_ptr++;
        j = 0;
        while (temp_ptr[j] && temp_ptr[j] != '\n')
        {
            if (!ft_isdigit(temp_ptr[j]))
                return (0);
            j++;
        }
        if (!*temp_ptr)
            return (0);
        if (i == 0)
            color->r = ft_atoi(temp_ptr);
        else if (i == 1)
            color->g = ft_atoi(temp_ptr);
        else if (i == 2)
            color->b = ft_atoi(temp_ptr);
        else
            return (0);
        i++;
    }
    if (i == 3)
		return 1;
	else
    	return 0;
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


/******************************************************************************/
/*                        		EXTRACT_RGB                                   */
/**************************************************************************** */
/*
** Function: extract_rgb
   RETURN: - 1 if success
		   - 0 if fail

   96: split the rgb values from the line
   99: extract the rgb values from the split_line array and convert them to int
   100: check if the values are in the range 0-255
   103: free the split_line array
*/
int extract_rgb(t_rgb *color, char *line) 
{
    char **split_line;

    if (!split_and_validate_line(line, &split_line))
        return (0); // Fallimento nell'allocazione
    if (!process_rgb_values(split_line, color)) 
    {
        free_matrix((void **)split_line);
        return (0); // Errore nell'elaborazione dei valori
    }
    if (!validate_rgb_range(*color)) 
    {
        free_matrix((void **)split_line);
        return (0); // Valori fuori range
    }
    free_matrix((void **)split_line);
    return (1);
}