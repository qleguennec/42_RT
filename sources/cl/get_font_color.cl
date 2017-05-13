float3            get_font_color(t_data *data, float *light_pow)
{
	if (data->skytype == CAM_SKYDAY)
	{
		return (twocolor_lerp((float3){240.0f / 255.0f, 240.0f /
			255.0f, 240.0f / 255.0f}, (float3){0.4235f, 0.851f, 0.98f},
			perlin(OCTAVE, FREQUENCY, PERSIS,
			data->ray_dir * 100.0f)) * (*light_pow));
	}
	else if (data->skytype == CAM_SKYNIGHT)
	{
		return (get_font(data->ray_dir) * (*light_pow));
	}
	return (FONT);
}
