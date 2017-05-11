#include "noise.h"
#include "noise.cl"
#include "wood.cl"
#include "marbre.cl"
#include "noise_1d.cl"


float3	get_shaders(float3 pos, int shader, float3 col)
{
	if (shader == WOOD)
		return (wood_shaders(pos));
	if (shader == STAR)
		return (twocolor_lerp((float3){240.0/255, 10.0/255, 10.0/255},
		(float3){255.0 / 255, 204.0 / 255, 40.0/255}, perlin(OCTAVE, FREQUENCY, PERSIS, pos)));
	if (shader >= MARBRE1 && shader <= MARBRE7)
		return (marbre_shaders(pos, shader, col));
	return (0);
}

float3	set_biosphere(float3 pos)
{
	double v;

	if (v == 1.0)
		return ((float3){1.0f, 1.0f, 1.0f});
	if (v >= 0.95 && v < 1.0)
		return ((float3){0.8f, 1.0f, 1.0f});
	if (v >= 0.92 && v < 0.95)
		return ((float3){1.0f, 0.8f, 1.0f});
	if (v >= 0.90 && v < 0.92)
		return ((float3){1.0f, 1.0f, 0.8f});
	return ((float3){0.0f, 0.0f, 0.0f});
}
