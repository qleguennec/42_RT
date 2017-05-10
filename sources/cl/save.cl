/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save->cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                     +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 11:31:03 by lgatibel          #+#    #+#             */
/*   Updated: 2017/05/09 11:31:04 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

	void    save(t_data *data)
  {
			data->save_id = data->id;
    	data->save_dir = data->ray_dir;
			data->save_pos = data->ray_pos;
			data->save_inter = data->intersect;
			data->save_clr = data->objs[data->id].clr;
  }

	void    load(t_data *data)
  {
			data->id = data->save_id;
   		data->ray_dir = data->save_dir;
			data->ray_pos = data->save_pos;
			data->inter = data->save_inter;
			data->clr = data->save_clr;
  }

	
