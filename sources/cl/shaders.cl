#include "noise.h"

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
