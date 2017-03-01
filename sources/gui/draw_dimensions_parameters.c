/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_dimensions_parameters.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 15:02:08 by bsouchet          #+#    #+#             */
/*   Updated: 2017/03/01 15:05:38 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	draw_dimensions_parameter_part2(t_rt *rt, t_obj *obj)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	if ((obj->forme == T_CYLINDER || obj->forme == T_CONE) &&
	(tmp1 = ft_dtoa(obj->radius * 2.0f)))
	{
		tmp2 = ft_dtoa(obj->radius * 2.0f);
		tmp3 = ft_dtoa(obj->height);
	}
	else if (obj->forme == T_PLANE && (tmp1 = ft_dtoa(obj->lenght)) &&
	(tmp2 = ft_dtoa(obj->width)))
		tmp3 = ft_strf("-----");
	else if (obj->forme == T_TORUS && (tmp1 = ft_dtoa(obj->lenght)) &&
	(tmp2 = ft_dtoa(obj->width)))
		tmp3 = ft_dtoa(obj->radius * 2.0f);
	draw_parameter(rt, tmp1, rt->ui->obj_b_rect[6], 2);
	draw_parameter(rt, tmp2, rt->ui->obj_b_rect[7], 2);
	draw_parameter(rt, tmp3, rt->ui->obj_b_rect[8], 2);
}

void		draw_dimensions_parameter(t_rt *rt, t_obj *o)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;

	tmp1 = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	if (o->forme == T_SPHERE && (tmp1 = ft_dtoa(o->radius * 2.0f)) &&
	(tmp2 = ft_dtoa(o->radius * 2.0f)))
		tmp3 = ft_dtoa(o->radius * 2.0f);
	else if (o->forme == T_CUBE && (tmp1 = ft_dtoa(o->lenght)) &&
	(tmp2 = ft_dtoa(o->width)))
		tmp3 = ft_dtoa(o->height);
	else
	{
		draw_dimensions_parameter_part2(rt, o);
		return ;
	}
	draw_parameter(rt, tmp1, rt->ui->obj_b_rect[6], 2);
	draw_parameter(rt, tmp2, rt->ui->obj_b_rect[7], 2);
	draw_parameter(rt, tmp3, rt->ui->obj_b_rect[8], 2);
}
