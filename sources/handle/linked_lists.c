/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 10:41:16 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/02 19:10:29 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		*lst_new_camera(t_rt *rt, t_obj *objs, int type)
{
	t_obj	*new_cam;
	t_obj	*nav_list;

	new_cam = NULL;
	if (!(new_cam = (t_obj *)malloc(sizeof(t_obj))))
		return (NULL);
	new_cam = assign_obj_values(new_cam, rt->prs->obj_tmp, 'C', type);
	new_cam->next = NULL;
	if (objs == NULL && ++rt->scn->n_cams)
	{
		rt->scn->b_lgts = new_cam->next;
		rt->scn->n_elms++;
		new_cam->id = rt->ui->id++;
		return (new_cam);
	}
	nav_list = objs;
	while (nav_list->next != NULL && nav_list->next->t == 'C')
		nav_list = nav_list->next;
	new_cam->next = nav_list->next;
	nav_list->next = new_cam;
	rt->scn->b_lgts = new_cam->next;
	rt->scn->n_cams++;
	rt->scn->n_elms++;
	new_cam->id = rt->ui->id++;
	return (objs);
}

t_obj		*lst_new_light(t_rt *rt, t_obj *objs, int type)
{
	t_obj	*new_light;
	t_obj	*nav_list;

	new_light = NULL;
	if (!(new_light = (t_obj *)malloc(sizeof(t_obj))))
		return (NULL);
	new_light = assign_obj_values(new_light, rt->prs->obj_tmp, 'L', type);
	new_light->next = NULL;
	if (objs == NULL && ++rt->scn->n_lgts)
	{
		rt->scn->b_objs = new_light->next;
		rt->scn->n_elms++;
		new_light->id = rt->ui->id++;
		return (new_light);
	}
	nav_list = objs;
	while (nav_list->next != NULL && nav_list->next->t < 79)
		nav_list = nav_list->next;
	new_light->next = nav_list->next;
	nav_list->next = new_light;
	rt->scn->b_objs = new_light->next;
	rt->scn->n_lgts++;
	rt->scn->n_elms++;
	new_light->id = rt->ui->id++;
	return (objs);
}

t_obj		*lst_new_object(t_rt *rt, t_obj *objs, int type)
{
	t_obj	*new_obj;
	t_obj	*nav_list;

	new_obj = NULL;
	if (!(new_obj = (t_obj *)malloc(sizeof(t_obj))))
		return (NULL);
	new_obj = assign_obj_values(new_obj, rt->prs->obj_tmp, 'O', type);
	new_obj->next = NULL;
	if (objs == NULL && ++rt->scn->n_objs)
	{
		rt->scn->n_elms++;
		new_obj->id = rt->ui->id++;
		return (new_obj);
	}
	nav_list = objs;
	while (nav_list->next != NULL)
		nav_list = nav_list->next;
	nav_list->next = new_obj;
	rt->scn->n_objs++;
	rt->scn->n_elms++;
	new_obj->id = rt->ui->id++;
	return (objs);
}
