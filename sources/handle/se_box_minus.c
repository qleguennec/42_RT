/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   se_box_minus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/28 16:41:58 by bsouchet          #+#    #+#             */
/*   Updated: 2017/03/01 18:02:28 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	update_se_camera_box(t_rt *rt, t_cl *cl)
{
	if (rt->ui->case_active == 1 && rt->scn->s_elem->focal > 18)
		rt->scn->s_elem->focal -= 1;
	else if (rt->ui->case_active == 2 && rt->scn->s_elem->pos.x > -1000.0)
		rt->scn->s_elem->pos.x -= 1.0;
	else if (rt->ui->case_active == 3 && rt->scn->s_elem->pos.y > -1000.0)
		rt->scn->s_elem->pos.y -= 1.0;
	else if (rt->ui->case_active == 4 && rt->scn->s_elem->pos.z > -1000.0)
		rt->scn->s_elem->pos.z -= 1.0;
	else if (rt->ui->case_active == 5 && rt->scn->s_elem->rot.x > 0.0)
		rt->scn->s_elem->rot.x -= 1.0;
	else if (rt->ui->case_active == 6 && rt->scn->s_elem->rot.y > 0.0)
		rt->scn->s_elem->rot.y -= 1.0;
	else if (rt->ui->case_active == 7 && rt->scn->s_elem->rot.z > 0.0)
		rt->scn->s_elem->rot.z -= 1.0;
	redraw_case_active(rt, cl, 1);
}

static void	update_se_light_box(t_rt *rt, t_cl *cl)
{
	if (rt->ui->case_active == 1 && rt->scn->s_elem->intensity > 0)
		rt->scn->s_elem->intensity -= 1;
	else if (rt->ui->case_active == 2 && rt->scn->s_elem->flare_v > 0)
		rt->scn->s_elem->flare_v -= 1;
	else if (rt->ui->case_active == 3 && rt->scn->s_elem->clr.x >= 0.05)
		rt->scn->s_elem->clr.x -= 0.002;
	else if (rt->ui->case_active == 4 && rt->scn->s_elem->clr.y >= 0.05)
		rt->scn->s_elem->clr.y -= 0.002;
	else if (rt->ui->case_active == 5 && rt->scn->s_elem->clr.z >= 0.05)
		rt->scn->s_elem->clr.z -= 0.002;
	else if (rt->ui->case_active == 6 && rt->scn->s_elem->pos.x > -1000.0)
		rt->scn->s_elem->pos.x -= 1.0;
	else if (rt->ui->case_active == 7 && rt->scn->s_elem->pos.y > -1000.0)
		rt->scn->s_elem->pos.y -= 1.0;
	else if (rt->ui->case_active == 8 && rt->scn->s_elem->pos.z > -1000.0)
		rt->scn->s_elem->pos.z -= 1.0;
	else if (rt->ui->case_active == 9 && rt->scn->s_elem->rot.x > 0.0)
		rt->scn->s_elem->rot.x -= 1.0;
	else if (rt->ui->case_active == 10 && rt->scn->s_elem->rot.y > 0.0)
		rt->scn->s_elem->rot.y -= 1.0;
	else if (rt->ui->case_active == 11 && rt->scn->s_elem->rot.z > 0.0)
		rt->scn->s_elem->rot.z -= 1.0;
	redraw_case_active(rt, cl, 1);
}

static void	update_se_object_box(t_rt *rt, t_cl *cl)
{
	if (rt->ui->case_active == 1 && rt->scn->s_elem->opacity >= 0.05)
		rt->scn->s_elem->opacity -= 0.05;
	else if (rt->ui->case_active == 5 && rt->scn->s_elem->radius <= 2.0)
		rt->scn->s_elem->radius -= 2.0;
	else if (rt->ui->case_active == 9 && rt->scn->s_elem->clr.x >= 0.05)
		rt->scn->s_elem->clr.x -= 0.002;
	else if (rt->ui->case_active == 10 && rt->scn->s_elem->clr.y >= 0.05)
		rt->scn->s_elem->clr.y -= 0.002;
	else if (rt->ui->case_active == 11 && rt->scn->s_elem->clr.z >= 0.05)
		rt->scn->s_elem->clr.z -= 0.002;
	else if (rt->ui->case_active == 12 && rt->scn->s_elem->pos.x > -1000.0)
		rt->scn->s_elem->pos.x -= 1.0;
	else if (rt->ui->case_active == 13 && rt->scn->s_elem->pos.y > -1000.0)
		rt->scn->s_elem->pos.y -= 1.0;
	else if (rt->ui->case_active == 14 && rt->scn->s_elem->pos.z > -1000.0)
		rt->scn->s_elem->pos.z -= 1.0;
	else if (rt->ui->case_active == 15 && rt->scn->s_elem->rot.x > 0.0)
		rt->scn->s_elem->rot.x -= 1.0;
	else if (rt->ui->case_active == 16 && rt->scn->s_elem->rot.y > 0.0)
		rt->scn->s_elem->rot.y -= 1.0;
	else if (rt->ui->case_active == 17 && rt->scn->s_elem->rot.z > 0.0)
		rt->scn->s_elem->rot.z -= 1.0;
	redraw_case_active(rt, cl, 1);
}

void		update_se_box_minus(t_rt *rt, t_cl *cl)
{
	if (rt->scn->s_elem->type == 'C')
		update_se_camera_box(rt, cl);
	else if (rt->scn->s_elem->type == 'L')
		update_se_light_box(rt, cl);
	else
		update_se_object_box(rt, cl);
}
