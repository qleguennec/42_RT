/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_informations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 01:56:36 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/14 13:01:37 by bsouchet         ###   ########.fr       */
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
		rt->prs->t_i = T_LAMBERT;
	else if (ft_strlcmp(str, "blinn"))
		rt->prs->t_i = T_BLINN;
	else if (ft_strlcmp(str, "phong"))
		rt->prs->t_i = T_PHONG;
	else if (ft_strlcmp(str, "custom"))
		rt->prs->t_i = T_CUSTOM;
	free(str);
	rt->prs->i = b_end + ft_strlen(e);
	return ((rt->prs->t_i == -1) ? (error(rt, 14) + 1) : 1);
}

/*
** Function to get the type of a object from a position in my buffer
*/

int			get_t(t_rt *rt, int b_end, char *s, char *e)
{
	char	*str;

	rt->prs->t_i = -1;
	rt->prs->b_o = s;
	rt->prs->b_c = e;
	str = ft_getstr(rt->prs->buf, rt->prs->i, b_end);
	if (ft_strlcmp(str, "sphere"))
		rt->prs->t_i = T_SPHERE;
	else if (ft_strlcmp(str, "cube"))
		rt->prs->t_i = T_CUBE;
	else if (ft_strlcmp(str, "cylinder"))
		rt->prs->t_i = T_CYLINDER;
	else if (ft_strlcmp(str, "plane"))
		rt->prs->t_i = T_PLANE;
	else if (ft_strlcmp(str, "cone"))
		rt->prs->t_i = T_CONE;
	else if (ft_strlcmp(str, "torus"))
		rt->prs->t_i = T_TORUS;
	else if (ft_strlcmp(str, "pyramid"))
		rt->prs->t_i = T_PYRAMID;
	else if (ft_strlcmp(str, "tetrahedron"))
		rt->prs->t_i = T_TETRAHEDRON;
	else if (ft_strlcmp(str, "octahedron"))
		rt->prs->t_i = T_OCTAHEDRON;
	free(str);
	rt->prs->i = b_end + ft_strlen(e);
	return ((rt->prs->t_i == -1) ? (error(rt, 14) + 1) : 1);
}

/*
** Function to get the type of a light from a position in my buffer
*/

int			get_lt(t_rt *rt, int b_end, char *s, char *e)
{
	char	*str;

	rt->prs->t_i = -1;
	rt->prs->b_o = s;
	rt->prs->b_c = e;
	str = ft_getstr(rt->prs->buf, rt->prs->i, b_end);
	if (ft_strlcmp(str, "diffuse") || ft_strlcmp(str, "point"))
		rt->prs->t_i = T_DIFFUSE;
	else if (ft_strlcmp(str, "directional"))
		rt->prs->t_i = T_DIRECTIONAL;
	else if (ft_strlcmp(str, "spot"))
		rt->prs->t_i = T_SPOT;
	free(str);
	rt->prs->i = b_end + ft_strlen(e);
	return ((rt->prs->t_i == -1) ? (error(rt, 14) + 1) : 1);
}
