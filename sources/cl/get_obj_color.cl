float3            get_obj_color(t_data *data)
{
    if (data->objs[data->id].shader > 0)
	{
		return (get_shaders(data->intersect, ((data->objs[data->id].shader & 1)
		? data->objs[data->id].shader + 1 : data->objs[data->id].shader) 
		 / 2, data->objs[data->id].clr));
	}
	else
		return (data->objs[data->id].clr);
}
