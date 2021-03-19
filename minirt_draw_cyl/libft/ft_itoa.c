/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdrake <pdrake@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:24:46 by pdrake            #+#    #+#             */
/*   Updated: 2020/11/10 16:33:20 by pdrake           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*s1;
	int		len;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = n;
	len = 1;
	while ((sign = sign / 10))
		len++;
	sign = (n < 0) ? 1 : 0;
	if (!(s1 = (char *)malloc(sizeof(char) * (len + 1 + sign))))
		return (0);
	if (n < 0)
	{
		s1[0] = '-';
		n *= -1;
	}
	s1[len + sign] = '\0';
	while (len--)
	{
		s1[len + sign] = n % 10 + '0';
		n = n / 10;
	}
	return (s1);
}
