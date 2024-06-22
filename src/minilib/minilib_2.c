/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-21 18:23:20 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-21 18:23:20 by ldi-fior         ###   ########.fr       */
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