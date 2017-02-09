/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/21 19:50:49 by bsouchet          #+#    #+#             */
/*   Updated: 2016/11/24 17:52:28 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_bzero(char *str, short size)
{
	while (--size >= 0)
		str[size] = 0;
	return (str);
}

short	*ft_short_bzero(short *array, short size)
{
	while (--size >= 0)
		array[size] = 0;
	return (array);
}
