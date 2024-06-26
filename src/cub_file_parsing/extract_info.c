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

/*
This function checks if the information needed to start the game has been saved 
in the game_struct. 
If any information is missing, the function returns 1; otherwise, it returns 0 */
static int check_missing_info(t_game *g_s)
{
	if (!g_s->map.wall_text.north || !g_s->map.wall_text.south
		|| !g_s->map.wall_text.east || !g_s->map.wall_text.west
		|| g_s->map.wall_text.c_rgb.r == -1 || g_s->map.wall_text.c_rgb.g == -1 
		|| g_s->map.wall_text.c_rgb.b == -1 || g_s->map.wall_text.f_rgb.r == -1
		|| g_s->map.wall_text.f_rgb.g == -1 || g_s->map.wall_text.f_rgb.b == -1)
		return (1);
	return (0);
}

/*
This function calls remove_space_strcpy to extract the texture path, 
removing spaces at the beginning and within the line. 

If the texture path is extracted correctly, the function increments the
count_info variable and returns 1; otherwise, it returns 0 */
static int parse_texture(char *line, char **texture, int *count_info)
{
    *texture = remove_space_strcpy(line);
    if (!(*texture))
        return (0);
    (*count_info)++;
    return (1);
}

/*
Function to extract the RGB color from the line.
If the RGB color is extracted correctly, the function increments the
count_info variable and returns 1; otherwise, it returns 0*/
static int parse_color(char *line, t_rgb *color, int *count_info)
{
    if (!extract_rgb(color, line))
        return (0);
    (*count_info)++;
    return (1);
}

/*
Function to parse the line extracted from the file.
If the line is a texture line, the function calls parse_texture to extract the
texture path.
If the line is a color line, the function calls parse_color to extract the RGB
color. */
static int  parse_line(char *line, t_game *g_s, int *count_info, char **split_line)
{
    if (split_line[0][0] == 'N' && split_line[0][1] == 'O')
        return (parse_texture(line + 2, &g_s->map.wall_text.north, count_info));
    else if (split_line[0][0] == 'S' && split_line[0][1] == 'O')
        return (parse_texture(line + 2, &g_s->map.wall_text.south, count_info));
    else if (split_line[0][0] == 'E' && split_line[0][1] == 'A')
        return (parse_texture(line + 2, &g_s->map.wall_text.east, count_info));
    else if (split_line[0][0] == 'W' && split_line[0][1] == 'E')
        return (parse_texture(line + 2, &g_s->map.wall_text.west, count_info));
    else if (split_line[0][0] == 'F')
        return (parse_color(line + 1, &g_s->map.wall_text.f_rgb, count_info));
    else if (split_line[0][0] == 'C')
        return (parse_color(line + 1, &g_s->map.wall_text.c_rgb, count_info));
    return (1);
}

/******************************************************************************/
/*                      		EXTRACT_INFO       		                      */
/******************************************************************************/
/*
Function to extract the information from the file and save it in the game_struct.
The function reads the file line by line and calls parse_line to extract the
information.
If the information is extracted correctly, the function returns 1; otherwise, it
returns 0 

116: extract the first line of the file
119: while the line is not NULL and the information is not complete
     121: split the line by space
     124: parse the line 
     126: if the line is a map line, break the loop
     128: cleanup the line and split_line
     129: read the next line
131: Otside the loop (if i foound all the information or something went wrong)
     cleanup the line and split_line
132: if the count_info is not 6 or the information is missing, return 0 */
int extract_info(t_game *g_s, int map_fd)
{
    char	*line;
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
    return (1);
}