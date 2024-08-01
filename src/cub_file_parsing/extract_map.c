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
	5: Return 1 if the map was successfully extracted, 0 otherwise
*/


/*This function checks if the map is present in the file

1: Keep skipping empty lines until the first line of the map is found or the 
	  end of the file is reached.
2: If the file ends before the map is found, return NULL
3: If the map is found, return line */
static char  *find_map( int map_fd)
{
	char	*line;

	line = get_next_line(map_fd);			//1
	while (line && (!*line || line[0] == '\n'))
	{
		free(line);
		line = get_next_line(map_fd);
	}
	if (!line)			//2
	{
		free(line);
		get_next_line(-2);
		return (NULL);
	}
	get_next_line(-2);
	return (line);			//3
}

/*This function reads the first line of the map (if it exists) and returns it as a string. */
static char *find_and_read_first_line(int map_fd)
{
    char *line;

    line = find_map(map_fd);
    if (!line)
        return (NULL);
    return (line);
}

/*trova la linea piu lunga della mappa*/
/*static void max_width_extractor(t_game *g, char *line)
{
    int len;

    len = ft_strlen(line);
    if (g->map.map_x < len)
        g->map.map_x = len;
}*/

/*This function reads the map line by line and joins them into a single string. */
static char *join_lines(/*t_game *g, */int map_fd, char *first_line)
{
    char *join_map = NULL;
    char *line = first_line;
    char *temp;

    while (line && line[0] != '\n')
    {
        //max_width_extractor(g, line);
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

/*This function checks if any line is missing. It extracts a line and checks if 
  the first character is a digit */
static int check_for_missing_line(int map_fd)
{
    char *line = get_next_line(map_fd);
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

/*This function splits the joined map into a matrix of strings and assigns it to 
  the map_mat field of the game struct. */
static void split_and_assign_map(t_game *g_s, char *join_map)
{
    g_s->map.map_mat = ft_split(join_map, '\n');
    free(join_map);
    if (!g_s->map.map_mat)
        quit_and_free(MALLOC_ERR, 2, g_s);
}

/*This function extracts the map from the file and assigns it to the map_mat field 
  of the game struct. It returns 1 if the map was successfully extracted, 0 otherwise. 
  
  NOTE: After calling the join_lines function, we exit the while loop that reads 
        the map line by line. This can happen either when the map is finished or 
		if we encounter an '\n' character.
		We then check if the last line is missing by calling the 
		check_for_missing_line function, which reads the next line and checks 
		if the first character is a digit. If the first character is a digit, 
		it means we have a missing line inside the map*/
int extract_map(t_game *g_s, int map_fd)
{
    char *first_line = find_and_read_first_line(map_fd);
    if (!first_line)
        return (0);

    char *join_map = join_lines(/*g_s,*/ map_fd, first_line);
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