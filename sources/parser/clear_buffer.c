/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_buffer_new.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 01:19:47 by bsouchet          #+#    #+#             */
/*   Updated: 2017/01/06 18:43:07 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Function to delete spaces, tabs & comments of lines from get_next_line
*/

char		*clear_line(t_parser *p, char *str, int pos, int n)
{
	int		j;
	char	*new;

	j = 0;
	while (str[pos] && (str[pos] == ' ' || str[pos] == '\t'))
		pos++;
	if (!str[pos] || (str[pos] == '/' && str[pos + 1] == '/'))
	{
		free(str);
		return (NULL);
	}
	--pos;
	new = (char *)malloc(sizeof(char) * ft_strlen(str));
	while (str[++pos] && !ft_strcmp(str, "//", pos))
	{
		(ft_strcmp(str, "<!--", pos) && i(&j, 3) > 0) ? (p->copy = 0) : 1;
		(j == 0 && ft_strcmp(str, "-->", pos)) ? (p->copy = 4) : 1;
		(p->copy == 1) ? (new[n++] = str[pos]) : 1;
		(p->copy > 1) ? (p->copy--) : 1;
		(j > 0) ? j-- : 1;
	}
	new[n] = 0;
	free(str);
	return (new);
}
