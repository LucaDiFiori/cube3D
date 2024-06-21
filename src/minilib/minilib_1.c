/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-21 12:44:52 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-21 12:44:52 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc((sizeof(char)) * (ft_strlen(src) + 1));
	if (dest == NULL)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char *s, int start, int len)
{
	char	*ptr;

	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_memcpy(ptr, s + start, len);
	ptr[len] = '\0';
	return (ptr);
}

static int	count_words(char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != c && str[i])
			i++;
	}
	return (count);
}

char	**ft_split(char *str, char c)
{
	int		end_wrd;
	int		index;
	char	**ptr_ret;

	if (!str)
		return (NULL);
	ptr_ret = malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (ptr_ret == NULL)
		return (NULL);
	index = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			end_wrd = 0;
			while (*str && *str != c && ++end_wrd)
				str++;
			ptr_ret[index++] = ft_substr(str - end_wrd, 0, end_wrd);
		}
	}
	ptr_ret[index] = NULL;
	return (ptr_ret);
}