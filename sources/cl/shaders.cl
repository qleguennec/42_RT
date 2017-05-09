#include "noise.h"

float3	get_shaders(float3 pos, int shader)
{
	// v = perlin(OCTAVE, FREQUENCY, PERSIS, pos);
	// v = cos(perlin(OCTAVE, FREQUENCY, PERSIS, pos / 1500.0f) + pos.z + pos.x);
	return (wood_shaders(pos));
}

float3	wood_shaders(float3 pos)
{
	double		v;
	t_shader	colors;

	// colors.col3 = (float3){176.0f, 100.f, 20.0f};
	colors.col1 = (float3){50.2f, 26.4f, 2.5f};
	colors.col2 = (float3){102.0f, 51.0f, 5.0f};
	colors.col3 = (float3){176.0f, 100.f, 20.0f};
	colors.col1 /= 255.0f;
	colors.col2 /= 255.0f;
	colors.col3 /= 255.0f;
	v = 20 * perlin(OCTAVE, FREQUENCY, PERSIS, pos / 5.0f);
	// if (v < 0)
		// v = -v;
	v = v - (int)v;
	return (lerp_wood(v, colors));
}

float3	lerp_wood(float v, t_shader colors)
{
	float	v1 = -1.0f;
	float	v2 = 0.75f;
	float	v3 = 0.90f;
	float	v4 = 1.0f;
	if (v >= v1 && v < v2)
		return ((colors.col3 * (v - v1) / (v2 - v1) + colors.col1 * (v2 - v) / (v2 - v1)));
	else if (v >= v2 && v < v3)
		return ((colors.col1 * (v - v2) / (v3 - v2) + colors.col2 * (v3 - v) / (v3 - v2)));
	return ((colors.col2 * (v - v3) / (v4 - v3) + colors.col3 * (v4 - v) / (v4 - v3)));
}
