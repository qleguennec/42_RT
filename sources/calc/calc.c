/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 17:50:51 by lgatibel          #+#    #+#             */
/*   Updated: 2017/02/09 18:06:44 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <structure.h>
//#include <lionel.h>

t_lionel			calc(t_scene *scene, t_ray *ray)
{
	short	index;
	t_obj	*obj;

	index = -1;
	obj = scene->g_list;
	while (index++ < scene->n_objs)
	{
		obj = scene->g_list;
		if (obj->type == PLANE)
			calc_plane();
		else if (obj->type == CONE)
			calc_cone();
		else if (obj->type == CYLINDER)
			calc_cylinder();
		else if (obj->type == SPHERE)
			calc_sphere();
		if ()
		{
		}
	}
}
