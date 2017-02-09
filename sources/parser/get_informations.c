/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_informations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 01:56:36 by bsouchet          #+#    #+#             */
/*   Updated: 2017/01/07 11:13:01 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Function to get a string (Char *) from a position in my buffer (v->buf)
*/

char		*get_s(t_parser *r, int b_end, int b_size)
{
	char	*str;

	str = ft_getstr(r->buf, r->i, b_end);
	r->i = b_end + b_size;
	return (str);
}

/*
** Function to get the material of an object from a position in my buffer
*/

int			get_m(t_rt *rt, int b_end, char *s, char *e)
{
	char	*str;

	rt->prs->t_i = -1;
	rt->prs->b_o = s;
	rt->prs->b_c = e;
	str = ft_getstr(rt->prs->buf, rt->prs->i, b_end);
	if (ft_strlcmp(str, "lambert"))
		rt->prs->t_i = 1;
	else if (ft_strlcmp(str, "blinn"))
		rt->prs->t_i = 2;
	else if (ft_strlcmp(str, "phong"))
		rt->prs->t_i = 3;
	else if (ft_strlcmp(str, "custom"))
		rt->prs->t_i = 4;
	free(str);
	rt->prs->i = b_end + ft_strlen(e);
	return ((rt->prs->t_i == -1) ? (error(rt, 14, 2) + 1) : 1);
}

/*
** Function to get the type of an object from a position in my buffer
*/

int			get_t(t_rt *rt, int b_end, char *s, char *e)
{
	char	*str;

	rt->prs->t_i = -1;
	rt->prs->b_o = s;
	rt->prs->b_c = e;
	str = ft_getstr(rt->prs->buf, rt->prs->i, b_end);
	if (ft_strlcmp(str, "plane"))
		rt->prs->t_i = 1;
	else if (ft_strlcmp(str, "sphere"))
		rt->prs->t_i = 2;
	else if (ft_strlcmp(str, "cube"))
		rt->prs->t_i = 3;
	else if (ft_strlcmp(str, "cylinder"))
		rt->prs->t_i = 4;
	else if (ft_strlcmp(str, "cone"))
		rt->prs->t_i = 5;
	free(str);
	rt->prs->i = b_end + ft_strlen(e);
	return ((rt->prs->t_i == -1) ? (error(rt, 14, 2) + 1) : 1);
}
