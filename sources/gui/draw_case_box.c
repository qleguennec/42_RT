/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_case_box.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 17:29:24 by bsouchet          #+#    #+#             */
/*   Updated: 2017/03/01 20:11:59 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	redraw_case_box_camera(t_rt *rt, t_obj *obj, int m)
{
	if (rt->ui->case_active == 1)
		draw_case_active(rt, ft_itoa(obj->focal), rt->ui->cam_b_rect[1], m);
	else if (rt->ui->case_active == 2)
		draw_case_active(rt, ft_dtoa(obj->pos.x), rt->ui->cam_b_rect[2], m);
	else if (rt->ui->case_active == 3)
		draw_case_active(rt, ft_dtoa(obj->pos.y), rt->ui->cam_b_rect[3], m);
	else if (rt->ui->case_active == 4)
		draw_case_active(rt, ft_dtoa(obj->pos.z), rt->ui->cam_b_rect[4], m);
	else if (rt->ui->case_active == 5)
		draw_case_active(rt, ft_dtoa(obj->rot.x), rt->ui->cam_b_rect[5], m);
	else if (rt->ui->case_active == 6)
		draw_case_active(rt, ft_dtoa(obj->rot.y), rt->ui->cam_b_rect[6], m);
	else if (rt->ui->case_active == 7)
		draw_case_active(rt, ft_dtoa(obj->rot.z), rt->ui->cam_b_rect[7], m);
}

static void	redraw_case_box_light(t_rt *rt, t_obj *obj, char *tmp, int m)
{
	if (rt->ui->case_active == 1)
		draw_case_active(rt, ft_itoa(obj->intensity), rt->ui->lgt_b_rect[1], m);
	else if (rt->ui->case_active == 2)
	{
		tmp = (obj->flare_v == 0) ? ft_strf("NO") : ft_strf("YES");
		draw_case_active(rt, tmp, rt->ui->lgt_b_rect[2], m);
	}
	else if (rt->ui->case_active == 3)
		DRAW_C(rt, ft_dtoa(obj->clr.x * 255.0), rt->ui->lgt_b_rect[3], m);
	else if (rt->ui->case_active == 4)
		DRAW_C(rt, ft_dtoa(obj->clr.y * 255.0), rt->ui->lgt_b_rect[4], m);
	else if (rt->ui->case_active == 5)
		DRAW_C(rt, ft_dtoa(obj->clr.z * 255.0), rt->ui->lgt_b_rect[5], m);
	else if (rt->ui->case_active == 6)
		draw_case_active(rt, ft_dtoa(obj->pos.x), rt->ui->lgt_b_rect[6], m);
	else if (rt->ui->case_active == 7)
		draw_case_active(rt, ft_dtoa(obj->pos.y), rt->ui->lgt_b_rect[7], m);
	else if (rt->ui->case_active == 8)
		draw_case_active(rt, ft_dtoa(obj->pos.z), rt->ui->lgt_b_rect[8], m);
	else if (rt->ui->case_active == 9)
		draw_case_active(rt, ft_dtoa(obj->rot.x), rt->ui->lgt_b_rect[9], m);
	else if (rt->ui->case_active == 10)
		draw_case_active(rt, ft_dtoa(obj->rot.y), rt->ui->lgt_b_rect[10], m);
	else if (rt->ui->case_active == 11)
		draw_case_active(rt, ft_dtoa(obj->rot.z), rt->ui->lgt_b_rect[11], m);
}

static void	redraw_case_box_object(t_rt *rt, t_obj *obj, int m)
{
	if (rt->ui->case_active == 1)
		draw_case_active(rt, ft_dtoa(obj->opacity), rt->ui->obj_b_rect[1], m);
	else if (rt->ui->case_active == 5)
		draw_case_active(rt, ft_dtoa(obj->radius), rt->ui->obj_b_rect[5], m);
	else if (rt->ui->case_active == 9)
		DRAW_C(rt, ft_dtoa(obj->clr.x * 255.0), rt->ui->obj_b_rect[9], m);
	else if (rt->ui->case_active == 10)
		DRAW_C(rt, ft_dtoa(obj->clr.y * 255.0), rt->ui->obj_b_rect[10], m);
	else if (rt->ui->case_active == 11)
		DRAW_C(rt, ft_dtoa(obj->clr.z * 255.0), rt->ui->obj_b_rect[11], m);
	else if (rt->ui->case_active == 12)
		draw_case_active(rt, ft_dtoa(obj->pos.x), rt->ui->obj_b_rect[12], m);
	else if (rt->ui->case_active == 13)
		draw_case_active(rt, ft_dtoa(obj->pos.y), rt->ui->obj_b_rect[13], m);
	else if (rt->ui->case_active == 14)
		draw_case_active(rt, ft_dtoa(obj->pos.z), rt->ui->obj_b_rect[14], m);
	else if (rt->ui->case_active == 15)
		draw_case_active(rt, ft_dtoa(obj->rot.x), rt->ui->obj_b_rect[15], m);
	else if (rt->ui->case_active == 16)
		draw_case_active(rt, ft_dtoa(obj->rot.y), rt->ui->obj_b_rect[16], m);
	else if (rt->ui->case_active == 17)
		draw_case_active(rt, ft_dtoa(obj->rot.z), rt->ui->obj_b_rect[17], m);
}

void		redraw_case_active(t_rt *rt, int mode)
{
	if (rt->scn->s_elem->type == 'C')
		redraw_case_box_camera(rt, rt->scn->s_elem, mode);
	else if (rt->scn->s_elem->type == 'L')
		redraw_case_box_light(rt, rt->scn->s_elem, NULL, mode);
	else
		redraw_case_box_object(rt, rt->scn->s_elem, mode);
}
