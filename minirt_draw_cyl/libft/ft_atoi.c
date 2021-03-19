/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrake <pdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:41:52 by pdrake            #+#    #+#             */
/*   Updated: 2020/11/10 18:08:25 by pdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_space(char symbol)
{
	if (symbol == ' ' || symbol == '\t' || symbol == '\n' || symbol == '\v' || \
		symbol == '\f' || symbol == '\r')
		return (1);
	return (0);
}

int				ft_atoi(const char *str)
{
	unsigned long long	max;
	unsigned long long	res;
	char				sign;

	max = 922337203685477580;
	sign = 1;
	res = 0;
	while (*str && is_space(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*(str++) == '-')
			sign = -1;
	while (ft_isdigit(*str))
	{
		if (sign == 1)
			if (res > max || (res == max && *str > '7'))
				return (-1);
		if (sign == -1)
			if (res > max || (res == max && *str > '8'))
				return (0);
		res = 10 * res + (*str - '0');
		str++;
	}
	return ((int)(sign * res));
}
