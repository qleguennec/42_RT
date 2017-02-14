/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erodrigu <erodrigu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:39:48 by erodrigu          #+#    #+#             */
/*   Updated: 2017/02/09 15:39:48 by erodrigu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

include "light.h";
include ".h"

unsigned get_lighting(t_scene *scene, t_lionel pt)
{
	float	i = 0;
	float3	rd_light;
	float	size;
	float3	lightdir;
	rd_light.xyz = (scene->ambient, scene->ambient, scene->ambient);
	while (i < scene->n_lgts)
	{
		lightdir = normalize(pt->ray_pos - scene->b_lgts[i]->pos);
		rd_light += is_light(lightdir, scene->b_objs, scene->b_lgts,
		scene->n_lgts, scene->n_objs);
		i++;
	}
}
