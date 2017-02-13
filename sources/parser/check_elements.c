/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/19 01:19:11 by bsouchet          #+#    #+#             */
/*   Updated: 2017/01/30 16:52:06 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Fonctions to check all elements (balises, cameras, lights, objects)
*/

int			check_scene(t_rt *rt)
{
	if (rt->scn->ambient < 0. || rt->scn->ambient > 1.)
		return (error(rt, 11, 2));
	if (rt->scn->aa != 0 && rt->scn->aa != 2 && rt->scn->aa != 4
		&& rt->scn->aa != 8 && rt->scn->aa != 16)
		return (error(rt, 12, 2));
	if (rt->scn->m_ref < 0 || rt->scn->m_ref > 10)
		return (error(rt, 13, 2));
	rt->prs->i += 8;
	return (1);
}

int			check_camera(t_rt *rt, short i)
{
	if (rt->prs->obj_tmp->pos.x != rt->prs->obj_tmp->pos.x)
		return (error(rt, 24, 2));
	if (rt->prs->obj_tmp->rot.x != rt->prs->obj_tmp->rot.x)
		return (error(rt, 25, 2));
	if (!rt->prs->obj_tmp->n)
		rt->prs->obj_tmp->n =
		ft_strjoin("Camera ", ft_itoa(i), 'R');
	if (rt->prs->obj_tmp->fl < 18 ||
	rt->prs->obj_tmp->fl > 200)
		return (error(rt, 16, 2));
	rt->prs->obj_tmp->e = 1;
	rt->prs->obj_tmp->t = 'C';
	rt->scn->o = lst_new_camera(rt, rt->scn->o, 1);
	rt->prs->i += 9;
	return (1);
}

int			check_light(t_rt *rt, short i)
{
	(void)i;
	if (rt->prs->obj_tmp->pos.x != rt->prs->obj_tmp->pos.x)
		return (error(rt, 26, 2));
	if (rt->prs->obj_tmp->rgb.x != rt->prs->obj_tmp->rgb.x)
	{
		rt->prs->obj_tmp->rgb.x = 255.0;
		rt->prs->obj_tmp->rgb.y = 255.0;
		rt->prs->obj_tmp->rgb.z = 255.0;
	}
	if (!rt->prs->obj_tmp->n)
		rt->prs->obj_tmp->n =
		ft_strjoin("Light ", ft_itoa(i), 'R');
	rt->prs->obj_tmp->e = 1;
	rt->prs->obj_tmp->t = 'L';
	rt->scn->o = lst_new_light(rt, rt->scn->o, 1);
	rt->prs->i += 8;
	return (1);
}

static void	add_name_object(t_rt *rt)
{
	char	*tmp;

	tmp = NULL;
	++rt->scn->t[(int)rt->prs->obj_tmp->ot];
	tmp = ft_itoa(rt->scn->t[(int)rt->prs->obj_tmp->ot]);
	if (rt->prs->obj_tmp->ot == 1)
		rt->prs->obj_tmp->n = ft_strjoin("Plane ", tmp, 'R');
	else if (rt->prs->obj_tmp->ot == 2)
		rt->prs->obj_tmp->n = ft_strjoin("Sphere ", tmp, 'R');
	else if (rt->prs->obj_tmp->ot == 3)
		rt->prs->obj_tmp->n = ft_strjoin("Cube ", tmp, 'R');
	else if (rt->prs->obj_tmp->ot == 4)
		rt->prs->obj_tmp->n = ft_strjoin("Cylinder ", tmp, 'R');
	else if (rt->prs->obj_tmp->ot == 5)
		rt->prs->obj_tmp->n = ft_strjoin("Cone ", tmp, 'R');
}

int			check_object(t_rt *rt)
{
	if (rt->prs->obj_tmp->pos.x != rt->prs->obj_tmp->pos.x)
		return (error(rt, 27, 2));
	if (rt->prs->obj_tmp->rgb.x != rt->prs->obj_tmp->rgb.x)
	{
		rt->prs->obj_tmp->rgb.x = 255.0;
		rt->prs->obj_tmp->rgb.y = 255.0;
		rt->prs->obj_tmp->rgb.z = 255.0;
	}
	if (rt->prs->obj_tmp->ot == -1)
		return (error(rt, 28, 2));
	if (rt->prs->obj_tmp->op < 0. ||
	rt->prs->obj_tmp->op > 1.)
		return (error(rt, 23, 2));
	if (!rt->prs->obj_tmp->n)
		add_name_object(rt);
	rt->prs->obj_tmp->e = 1;
	rt->prs->obj_tmp->t = 'O';
	rt->scn->o = lst_new_object(rt, rt->scn->o, 1);
	rt->prs->i += 9;
	return (1);
}
