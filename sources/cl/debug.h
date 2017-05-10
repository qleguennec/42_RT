#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG 1
/*defini si le vrai calcul de couleur est realiser ou non*/
#define COLOR 1
/*active la rotation ou non*/
#define ROTATE 1
#define NATIVE 1
/**/

#define FONT 0x000000FF
// #define FONT 0xFFFFFFFF
#ifndef M_PI
#define M_PI 3.14f
#endif
#define FONT 0x000000FF
/*active l'affichage des define _PRINT...*/
#define _DEBUG 0

#define PRINT3(v, a) printf(a ": %f %f %f\n", (v).x, (v).y, (v).z);
#define PRINT1(v, a) printf(a ": %f\n", (v));
#define _PRINT3(v, a) if(_DEBUG){printf(a ": %f %f %f\n", (v).x, (v).y, (v).z);}
#define _PRINT1(v, a) if(_DEBUG){printf(a ": %f\n", (v));}

void	debug(global t_obj *objs, global t_lgt *lgts, global t_cam *cam
	, short nobjs, short nlgts);
void	print_obj_type(short type);
#endif
