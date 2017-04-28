/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgatibel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 11:16:13 by lgatibel          #+#    #+#             */
/*   Updated: 2017/04/27 11:16:20 by lgatibel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

short       cone_caps(t_data *data, float3 *rot, short *index)
{
    float	div;
	float	t;

    data->type = T_DISK;
    data->pos = data->objs[(int)*index].pos + *rot *
        data->objs[(int)*index].height;
    data->offset = data->ray_pos - data->pos;
    div = dot(*rot, data->ray_dir);
    if (div == 0.0f)
        return (0);
    t = (-dot(*rot, data->offset)) / div;
    if (t < 0.0f)
        return (0);
    calc_intersect(&t, data);
    if (fast_distance(data->intersect, data->pos) >
    15)//data->objs[(int)*index].radius)// probleme de caps voir benj
        return (0);
    return (1);
}

short       cylinder_caps(t_data *data, float3 *rot, short *index, float m)
{
    float	div;
	float	t;

    if (m < 0.0f)
        data->pos = data->objs[(int)*index].pos;
    else if (m > data->objs[(int)*index].height)
    {
        data->pos = data->objs[(int)*index].pos + *rot *
            data->objs[(int)*index].height;
        data->offset = data->ray_pos - data->pos;
    }
    data->type = T_DISK;
    div = dot(*rot, data->ray_dir);
    if (div == 0.0f)
        return (0);
    t = (-dot(*rot, data->offset)) / div;
    if (t < 0.0f)
        return (0);
    calc_intersect(&t, data);
    if (fast_distance(data->intersect, data->pos) >
    data->objs[(int)*index].radius)
        return (0);
    return (1);
}
