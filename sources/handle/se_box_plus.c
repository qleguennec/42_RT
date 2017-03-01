/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_box_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 15:37:50 by bsouchet          #+#    #+#             */
/*   Updated: 2017/03/01 20:21:44 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	update_se_camera_box(t_rt *rt)
{
	if (rt->ui->case_active == 1 && rt->scn->s_elem->focal < 200)
		rt->scn->s_elem->focal += 1;
	else if (rt->ui->case_active == 2 && rt->scn->s_elem->pos.x < 1000.0)
		rt->scn->s_elem->pos.x += 0.5;
	else if (rt->ui->case_active == 3 && rt->scn->s_elem->pos.y < 1000.0)
		rt->scn->s_elem->pos.y += 0.5;
	else if (rt->ui->case_active == 4 && rt->scn->s_elem->pos.z < 1000.0)
		rt->scn->s_elem->pos.z += 0.5;
	else if (rt->ui->case_active == 5 && rt->scn->s_elem->rot.x < 360.0)
		rt->scn->s_elem->rot.x += 0.5;
	else if (rt->ui->case_active == 6 && rt->scn->s_elem->rot.y < 360.0)
		rt->scn->s_elem->rot.y += 0.5;
	else if (rt->ui->case_active == 7 && rt->scn->s_elem->rot.z < 360.0)
		rt->scn->s_elem->rot.z += 0.5;
	redraw_case_active(rt, 1);
}

static void	update_se_light_box(t_rt *rt)
{
	if (rt->ui->case_active == 1 && rt->scn->s_elem->intensity < 50)
		rt->scn->s_elem->intensity += 1;
	else if (rt->ui->case_active == 2 && rt->scn->s_elem->flare_v < 1)
		rt->scn->s_elem->flare_v += 1;
	else if (rt->ui->case_active == 3 && rt->scn->s_elem->clr.x <= 0.95)
		rt->scn->s_elem->clr.x += 0.002;
	else if (rt->ui->case_active == 4 && rt->scn->s_elem->clr.y <= 0.95)
		rt->scn->s_elem->clr.y += 0.002;
	else if (rt->ui->case_active == 5 && rt->scn->s_elem->clr.z <= 0.95)
		rt->scn->s_elem->clr.z += 0.002;
	else if (rt->ui->case_active == 6 && rt->scn->s_elem->pos.x < 1000.0)
		rt->scn->s_elem->pos.x += 0.5;
	else if (rt->ui->case_active == 7 && rt->scn->s_elem->pos.y < 1000.0)
		rt->scn->s_elem->pos.y += 0.5;
	else if (rt->ui->case_active == 8 && rt->scn->s_elem->pos.z < 1000.0)
		rt->scn->s_elem->pos.z += 0.5;
	else if (rt->ui->case_active == 9 && rt->scn->s_elem->rot.x < 360.0)
		rt->scn->s_elem->rot.x += 0.5;
	else if (rt->ui->case_active == 10 && rt->scn->s_elem->rot.y < 360.0)
		rt->scn->s_elem->rot.y += 0.5;
	else if (rt->ui->case_active == 11 && rt->scn->s_elem->rot.z < 360.0)
		rt->scn->s_elem->rot.z += 0.5;
	redraw_case_active(rt, 1);
}

static void	update_se_object_box(t_rt *rt)
{
	if (rt->ui->case_active == 1 && rt->scn->s_elem->opacity <= 0.95)
		rt->scn->s_elem->opacity += 0.05;
	else if (rt->ui->case_active == 5 && rt->scn->s_elem->radius <= 398.0)
		rt->scn->s_elem->radius += 1.0;
	else if (rt->ui->case_active == 9 && rt->scn->s_elem->clr.x < 255.0)
		rt->scn->s_elem->clr.x += 0.5;
	else if (rt->ui->case_active == 10 && rt->scn->s_elem->clr.y < 255.0)
		rt->scn->s_elem->clr.y += 0.5;
	else if (rt->ui->case_active == 11 && rt->scn->s_elem->clr.z < 255.0)
		rt->scn->s_elem->clr.z += 0.5;
	else if (rt->ui->case_active == 12 && rt->scn->s_elem->pos.x < 1000.0)
		rt->scn->s_elem->pos.x += 0.5;
	else if (rt->ui->case_active == 13 && rt->scn->s_elem->pos.y < 1000.0)
		rt->scn->s_elem->pos.y += 0.5;
	else if (rt->ui->case_active == 14 && rt->scn->s_elem->pos.z < 1000.0)
		rt->scn->s_elem->pos.z += 0.5;
	else if (rt->ui->case_active == 15 && rt->scn->s_elem->rot.x < 360.0)
		rt->scn->s_elem->rot.x += 0.5;
	else if (rt->ui->case_active == 16 && rt->scn->s_elem->rot.y < 360.0)
		rt->scn->s_elem->rot.y += 0.5;
	else if (rt->ui->case_active == 17 && rt->scn->s_elem->rot.z < 360.0)
		rt->scn->s_elem->rot.z += 0.5;
	redraw_case_active(rt, 1);
}

void		update_se_box_plus(t_rt *rt, t_cl *cl)
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
