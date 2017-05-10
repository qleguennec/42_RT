/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 11:17:15 by lgatibel          #+#    #+#             */
/*   Updated: 2017/05/10 10:45:12 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void		init_data(t_data *data, global t_obj *objs,
global t_lgt *lgts, short n_objs, short n_lgts, float3 ray_pos,
float3 ray_dir, global unsigned int *pixel)
{
	data->objs = objs;
	data->lights = lgts;
	data->pixel = pixel;
	data->n_objs = n_objs;
	data->n_lgts = n_lgts;
	data->ray_pos = ray_pos;
	data->ray_dir = ray_dir;

	data->intersect = 0.0f;
	data->inter = 0.0f;
	data->is_light = 0;
	data->offset = 0.0f;
	data->type = -1;
	data->through = -1;

	data->test = 0;

	// data->clr = 0.0f;
	data->light_pow = 1.0f;
	data->light_obj_pow = 0.0f;
	data->rd_light = 0.0f;
	data->id = -1;
	data->reflex = MAX_REFLECTION;
	data->nl = 0;
	data->normale = 0;
}
