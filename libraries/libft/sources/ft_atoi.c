/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 02:25:28 by bsouchet          #+#    #+#             */
/*   Updated: 2016/11/19 02:48:15 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(char *str, int i)
{
	int		s;
	int		r;

	r = 0;
	s = (str[i] == '-') ? -1 : 1;
	(str[i] == '-' || str[i] == '+') ? i++ : i;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		r = r * 10 + str[i++] - '0';
	return (s * r);
}
