/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilib_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <marvin@42.fr>                    #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-06-23 09:47:28 by ldi-fior          #+#    #+#             */
/*   Updated: 2024-06-23 09:47:28 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

static int	handle_initial_chars(const char **nptr, int *sign)
{
    while (**nptr == ' ' || (**nptr >= 9 && **nptr <= 13))
        (*nptr)++;
    if (**nptr == '-')
    {
        *sign *= -1;
        (*nptr)++;
    }
    else if (**nptr == '+')
        (*nptr)++;
    return (0);
}

static int	convert_to_int(const char *nptr, int sign)
{
    long	result;

    result = 0;
    while (*nptr && *nptr >= '0' && *nptr <= '9')
    {
        if (result > (INT_MAX - (*nptr - '0')) / 10)
        {
            if (sign == 1)
                return INT_MAX;
            else
                return INT_MIN;
        }
        result = result * 10 + (*nptr - '0');
        nptr++;
    }
    return (result * sign);
}

int	ft_atoi(const char *nptr)
{
    int	result;
    int	sign;

    sign = 1;
    handle_initial_chars(&nptr, &sign);
    result = convert_to_int(nptr, sign);
    return result;
}