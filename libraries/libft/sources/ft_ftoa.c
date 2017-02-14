/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 19:38:08 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/02 17:37:42 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_ftoa(float num)
{
	short	i;
	int		tmp;
	short	size;
	char	*str;

	i = 0;
	size = 1;
	tmp = (int)round(num * 100);
	if (num == .0)
		return (ft_strdup("0.00"));
	(num < .0 && (tmp *= -1.) > 0) ? ++size : 1;
	num = tmp;
	while (tmp != 0 && ++size != 0)
		tmp /= 10;
	if (!(str = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	str[size--] = 0;
	while ((int)num != 0 && ++i > 0)
		(i != 3 && (str[size--] = ((int)num % 10) + '0')) ?
		(num /= 10) : (str[size--] = '.');
	(size == 0 && i == 2) ? str[0] = '.' : 1;
	(size == 0 && i != 2) ? str[0] = '-' : 1;
	return (str);
}

char		*ft_dtoa(double num)
{
	short	i;
	int		tmp;
	short	size;
	char	*str;

	i = 0;
	size = 1;
	tmp = (int)round(num * 100);
	if (num == .0)
		return (ft_strdup("0.00"));
	(num < .0 && (tmp *= -1.) > 0) ? ++size : 1;
	(num < 1.) ? size++ : 1;
	num = tmp;
	while (tmp != 0 && ++size != 0)
		tmp /= 10;
	if (!(str = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	str[size--] = 0;
	while ((int)num != 0 && ++i > 0)
		(i != 3 && (str[size--] = ((int)num % 10) + '0')) ?
		(num /= 10) : (str[size--] = '.');
	(size == 1 && i == 2) ? str[size--] = '.' : 1;
	(size == 1 && i != 2) ? str[size--] = '-' : 1;
	(size == 0) ? str[0] = '0' : 1;
	return (str);
}
