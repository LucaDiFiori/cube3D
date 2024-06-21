/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-21 12:07:14 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-21 12:07:14 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*update_line(char *line)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	temp = (char *)malloc(sizeof(char) * (ft_strlen_gnl(line) - i + 1));
	if (!temp)
		return (NULL);
	i++;
	j = 0;
	while (line[i])
		temp[j++] = line[i++];
	temp[j] = '\0';
	free(line);
	return (temp);
}

static char	*print_line(char *line)
{
	char	*output;
	int		i;

	i = 0;
	if (!line[0])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	output = (char *)malloc(sizeof(char) * i + 2);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		output[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		output[i] = '\n';
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	*get_line(int fd, char *line)
{
	char	*buffer;
	int		j;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	j = 1;
	while (!ft_strchr_gnl(line, '\n') && j > 0)
	{
		j = read(fd, buffer, BUFFER_SIZE);
		if (j == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[j] = '\0';
		line = ft_strjoin_gnl(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*output;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = get_line(fd, line);
	if (!line)
		return (NULL);
	output = print_line(line);
	line = update_line(line);
	return (output);
}