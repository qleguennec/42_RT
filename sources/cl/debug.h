#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG 0
#define COLOR 1
#define ROTATE 1

#define PRINT3(v, a) printf(a ": %f %f %f\n", (v).x, (v).y, (v).z);
#define PRINT1(v, a) printf(a ": %f\n", (v));
#define _DEBUG 0
#define _PRINT3(v, a) if(_DEBUG){printf(a ": %f %f %f\n", (v).x, (v).y, (v).z);}
#define _PRINT1(v, a) if(_DEBUG){printf(a ": %f\n", (v));}

void	debug(global t_obj *objs, global t_lgt *lgts, global t_cam *cam
	, short nobjs, short nlgts);
#endif
