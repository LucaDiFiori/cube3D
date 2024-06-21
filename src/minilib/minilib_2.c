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