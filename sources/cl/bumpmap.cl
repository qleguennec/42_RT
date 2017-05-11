void	get_bumpmapping(t_data *data)
{
	float3	bump;
	float3	pos1;
	float3	pos2;
	float	mod = 10.0f;

	pos1 = data->intersect;
	pos2 = data->intersect;
	pos1.x -= mod;
	pos2.x += mod;
	bump.x = perlin(OCTAVE, FREQUENCY, PERSIS, pos1);// - perlin(OCTAVE, FREQUENCY, PERSIS, pos1);
	pos1 = data->intersect;
	pos2 = data->intersect;
	pos1.y -= mod;
	pos2.y += mod;
	bump.y = perlin(OCTAVE, FREQUENCY, PERSIS, pos1);// - perlin(OCTAVE, FREQUENCY, PERSIS, pos1);
	pos1 = data->intersect;
	pos2 = data->intersect;
	pos1.z -= mod;
	pos2.z += mod;
	bump.z = perlin(OCTAVE, FREQUENCY, PERSIS, pos1);// - perlin(OCTAVE, FREQUENCY, PERSIS, pos1);
	bump = fast_normalize(bump);
	data->normal += bump;
}
