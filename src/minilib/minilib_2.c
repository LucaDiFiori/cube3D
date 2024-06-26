/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:23:20 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/06/24 09:28:09 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	*ft_memcpy(void *dest, void *src, int n)
{
	int					i;
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_src;

	ptr_dest = (unsigned char *)dest;
	ptr_src = (unsigned char *)src;
	i = 0;
	if (!dest && !src)
		return (0);
	while (i < n)
	{
		ptr_dest[i] = ptr_src[i];
		i++;
	}
	return (dest);
}

char	*ft_strstr(const char *source, const char *to_find)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!(*to_find))
		return ((char *)source);
	if (!(*source))
		return (NULL);
	while (source[i])
	{
		while ((to_find[j] && to_find[j] == source[i + j]))
			j++;
		if (to_find[j] == '\0')
			return ((char *)&source[i]);
		i++;
		j = 0;
	}
	return (NULL);
}

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

char *ft_strcpy(char *to_copy) 
{
    int		len;
    char	*copy; 
    char	*start;

    if (!to_copy)
        return NULL;
    len = ft_strlen(to_copy) + 1; 
    copy = (char *)malloc(sizeof(char) * len);
    if (!copy)
        return NULL;
    start = copy;
    while (*to_copy)
    {
        *copy = *to_copy;
        copy++;
        to_copy++;
    }
    *copy = '\0';
    return (start);
}