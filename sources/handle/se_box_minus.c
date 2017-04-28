/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_box_minus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:41:58 by bsouchet          #+#    #+#             */
/*   Updated: 2017/04/28 19:35:44 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	update_se_camera_box(t_rt *rt)
{
	if (rt->ui->case_active == 1 && rt->scn->s_elem->focal > 18)
		rt->scn->s_elem->focal -= 1;
	else if (rt->ui->case_active == 2 && rt->scn->s_elem->pos.x >= -999.50f)
		rt->scn->s_elem->pos.x -= 0.50f;
	else if (rt->ui->case_active == 3 && rt->scn->s_elem->pos.y >= -999.50f)
		rt->scn->s_elem->pos.y -= 0.50f;
	else if (rt->ui->case_active == 4 && rt->scn->s_elem->pos.z >= -999.50f)
		rt->scn->s_elem->pos.z -= 0.50f;
	else if (rt->ui->case_active == 5 && rt->scn->s_elem->rot.x >= -719.50f)
		rt->scn->s_elem->rot.x -= 0.50f;
	else if (rt->ui->case_active == 6 && rt->scn->s_elem->rot.y >= -719.50f)
		rt->scn->s_elem->rot.y -= 0.50f;
	else if (rt->ui->case_active == 7 && rt->scn->s_elem->rot.z >= -719.50f)
		rt->scn->s_elem->rot.z -= 0.50f;
	redraw_case_active(rt, 1);
}

static void	update_se_light_box(t_rt *rt)
{
	if (rt->ui->case_active == 1 && rt->scn->s_elem->intensity > 0)
		rt->scn->s_elem->intensity -= 1;
	else if (rt->ui->case_active == 2 && rt->scn->s_elem->flare_v > 0)
		rt->scn->s_elem->flare_v -= 1;
	else if (rt->ui->case_active == 3 && rt->scn->s_elem->clr.x >= 0.0020f)
		rt->scn->s_elem->clr.x -= 0.0020f;
	else if (rt->ui->case_active == 4 && rt->scn->s_elem->clr.y >= 0.0020f)
		rt->scn->s_elem->clr.y -= 0.0020f;
	else if (rt->ui->case_active == 5 && rt->scn->s_elem->clr.z >= 0.0020f)
		rt->scn->s_elem->clr.z -= 0.0020f;
	else if (rt->ui->case_active == 6 && rt->scn->s_elem->pos.x >= -999.50f)
		rt->scn->s_elem->pos.x -= 0.50f;
	else if (rt->ui->case_active == 7 && rt->scn->s_elem->pos.y >= -999.50f)
		rt->scn->s_elem->pos.y -= 0.50f;
	else if (rt->ui->case_active == 8 && rt->scn->s_elem->pos.z >= -999.50f)
		rt->scn->s_elem->pos.z -= 0.50f;
	else if (rt->ui->case_active == 9 && rt->scn->s_elem->rot.x >= -719.50f)
		rt->scn->s_elem->rot.x -= 0.50f;
	else if (rt->ui->case_active == 10 && rt->scn->s_elem->rot.y >= -719.50f)
		rt->scn->s_elem->rot.y -= 0.50f;
	else if (rt->ui->case_active == 11 && rt->scn->s_elem->rot.z >= -719.50f)
		rt->scn->s_elem->rot.z -= 0.50f;
	redraw_case_active(rt, 1);
}

static void	update_se_object_box_part2(t_rt *rt)
{
	if (rt->ui->case_active == 3 && rt->scn->s_elem->reflex >= 0.050f)
		rt->scn->s_elem->reflex -= 0.050f;
	else if (rt->ui->case_active == 4 && rt->scn->s_elem->refrac_y >= 0.050f)
		rt->scn->s_elem->refrac_y -= 0.050f;
	else if (rt->ui->case_active == 5 && rt->scn->s_elem->radius >= 1.0f)
		rt->scn->s_elem->radius -= 1.0f;
	else if (rt->ui->case_active == 6 && rt->scn->s_elem->width >= -999.50f)
		rt->scn->s_elem->width -= 0.50f;
	else if (rt->ui->case_active == 7 && rt->scn->s_elem->height >= -999.50f)
		rt->scn->s_elem->height -= 0.50f;
	else if (rt->scn->s_elem->lenght >= -999.50f)
		rt->scn->s_elem->lenght -= 0.50f;
}

static void	update_se_object_box(t_rt *rt)
{
	if (rt->ui->case_active == 1 && rt->scn->s_elem->opacity >= 0.050f)
	{
		rt->scn->s_elem->opacity -= 0.050f;
		rt->scn->s_elem->opacity = roundf(rt->scn->s_elem->opacity * 100) / 100;
	}
	else if (rt->ui->case_active == 2 && rt->scn->s_elem->specular >= 0.050f)
		rt->scn->s_elem->specular -= 0.050f;
	else if (rt->ui->case_active > 2 && rt->ui->case_active < 9)
		update_se_object_box_part2(rt);
	else if (rt->ui->case_active == 9 && rt->scn->s_elem->clr.x >= 0.0020f)
		rt->scn->s_elem->clr.x -= 0.0020f;
	else if (rt->ui->case_active == 10 && rt->scn->s_elem->clr.y >= 0.0020f)
		rt->scn->s_elem->clr.y -= 0.0020f;
	else if (rt->ui->case_active == 11 && rt->scn->s_elem->clr.z >= 0.0020f)
		rt->scn->s_elem->clr.z -= 0.0020f;
	else if (rt->ui->case_active == 12 && rt->scn->s_elem->pos.x >= -999.50f)
		rt->scn->s_elem->pos.x -= 0.50f;
	else if (rt->ui->case_active == 13 && rt->scn->s_elem->pos.y >= -999.50f)
		rt->scn->s_elem->pos.y -= 0.50f;
	else if (rt->ui->case_active == 14 && rt->scn->s_elem->pos.z >= -999.50f)
		rt->scn->s_elem->pos.z -= 0.50f;
	else if (rt->ui->case_active == 15 && rt->scn->s_elem->rot.x >= -719.50f)
		rt->scn->s_elem->rot.x -= 0.50f;
	else if (rt->ui->case_active == 16 && rt->scn->s_elem->rot.y >= -719.50f)
		rt->scn->s_elem->rot.y -= 0.50f;
	else if (rt->ui->case_active == 17 && rt->scn->s_elem->rot.z >= -719.50f)
		rt->scn->s_elem->rot.z -= 0.50f;
	redraw_case_active(rt, 1);
}

void		update_se_box_minus(t_rt *rt, t_cl *cl)
{
	if (rt->scn->s_elem->type == 'C')
		update_se_camera_box(rt);
	else if (rt->scn->s_elem->type == 'L')
		update_se_light_box(rt);
	else
		update_se_object_box(rt);
	if (rt->scn->s_elem == rt->scn->c_cam)
		cl_main_krl_update_camera(cl, rt->scn->c_cam);
	else
		cl_main_krl_update_buffers(cl, rt->scn);
	cl_main_krl_exec(cl);
	cl_copy_image_buffer(cl, rt->s_rend->pixels);
	add_render_frame(rt);
}
