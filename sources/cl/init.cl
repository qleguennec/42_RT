/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 11:17:15 by lgatibel          #+#    #+#             */
/*   Updated: 2017/04/27 11:17:19 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void     init_laputain_desamere(t_data *data)
{
	// data->objs[0].reflex = 1.0f;
	data->objs[0].type = T_TORUS;
	// data->objs[1].reflex = 1.0f;
	// data->objs[2].reflex = 1.0f;
	// data->objs[3].reflex = 1.0f;
	// data->objs[4].reflex = 1.0f;
	// data->objs[4].refract = 1.55f;
	// data->objs[5].reflex = 1.0f;
	// data->objs[6].reflex = 1.0f;
}

static void		init_data(t_data *data, global t_obj *objs,
global t_lgt *lgts, short n_objs, short n_lgts, float3 ray_pos,
float3 ray_dir, float ambiant, global unsigned int *pixel)
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
	data->rot = (float3){0.0f, 1.0f, 0.0f};
	data->is_light = 0;
	data->offset = 0.0f;
	data->type = -1;

	data->ambiant = ambiant;
	data->light_pow = 1.0f;
	data->rd_light = 0.0f;
	data->id = -1;
	data->safe = SAFE;
	data->nl = 0;
}

void		init(t_data *data, global t_obj *objs, global t_lgt *lgts,
 short n_objs, short n_lgts, float3 ray_pos, float3 ray_dir, float ambiant,
  global unsigned int *pixel)
{
	init_data(data, objs, lgts, n_objs, n_lgts, ray_pos, ray_dir, ambiant,
     pixel);
	init_laputain_desamere(data);
}
