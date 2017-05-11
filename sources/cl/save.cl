/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 11:31:03 by lgatibel          #+#    #+#             */
/*   Updated: 2017/05/11 18:15:06 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "noise.h"

void	save(t_data *data)
{
	data->save_id = data->id;
	data->save_dir = data->ray_dir;
	data->save_pos = data->ray_pos;
	data->save_inter = data->intersect;
	if (data->objs[data->id].shader != 0)
		data->save_clr = get_shaders(data->intersect,
		data->objs[data->id].shader, data->objs[data->id].clr);
	else
		data->save_clr = data->objs[data->id].clr;
}

void	load(t_data *data)
{
	data->id = data->save_id;
	data->ray_dir = data->save_dir;
	data->ray_pos = data->save_pos;
	data->intersect = data->save_inter;
	data->clr = data->save_clr;
}
