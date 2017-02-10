/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:33:17 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/10 10:05:09 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct s_scene	t_scene;
typedef struct s_rt		t_rt;

/*
** ---------------------------- Scene Elements ---------------------------------
*/

/*typedef	struct		s_obj
{
	short			id;
	short			e;
	char			t;
	short			title;
	short			ot;
	short			m;
	short			v;
	short			i;
	short			fl;
	char			*n;
	double			op;
	SDL_Rect		r_ol;
	t_vec3			pos;
	t_vec3			rot;
	t_vec3			rgb;
	struct s_obj	*next;
}					t_obj;*/

typedef struct		s_obj
{
	cl_short		id;
	cl_char			*n;			//Nom de l'élément, reécupéré par parsing
	cl_short		title;		//Pour GUI, BOOL pour savoir si c'est un separateur entre type d'élément
	cl_short		active;		//Pour GUI, 1 si c'est la cam active sinon 0
	cl_char			type;		//Type d'élément ('C' pour Camera, 'L' pour Light et 'O' pour object)
	cl_short		forme;		//Type d'objet ()
	cl_float3		pos;		//Position
	cl_float3		rot;		//Rotation
	cl_float3		clr;		//Couleur
	cl_float		opacity;	//opacité de l'élément
	cl_short		focal;		//Focal de la camera
	cl_float		radius;		//Radius pour sphere, cylindre, cone
	cl_float		width;		//Pour plane
	cl_float 		height;		//Pour cone et cylindre
	cl_short		visibility;	//Lumiere visible ou non
	cl_float		intensity;	//Intensité de la lumière
	cl_float		shiness;	//Brillance de l'objet. 0 = null & 1 = max
	cl_float		mshiness;	//Puissance de brillance utiliser avec le paramettre precedent
	cl_float		specolor;	//Specular color rattachée a la brillance
	cl_float		reflex;		//Coefficient de reflextion de l'objet
	cl_float		refract;	//Coefficient de refraction de l'objet
	SDL_Rect		r_ol;		//Pour GUI, Rectangle pour Outliner
	struct s_obj	*next;		//Next element of the linked list
}					t_obj;

/*
** -------------------------- Global Structures --------------------------------
*/

typedef struct		s_parser
{
	int				i;
	int				t_i;
	double			t_d;
	unsigned		t_u;
	int				copy;
	cl_float3		vec;
	char			*buf;
	char			*line;
	short			n[50];
	short			t[6];
	char			*b_o;
	char			*b_c;
	t_obj			*obj_tmp;
}					t_parser;

struct				s_scene
{
	int				aa;
	double			ambient;
	int				m_ref;
	char			*name;
	t_obj			*o;
	t_obj			*b_lgts;
	t_obj			*b_objs;
	short			n_cams;
	short			n_lgts;
	short			n_objs;
	short			n_elms;
	t_obj			*b_outliner;
	t_obj			*s_elem;
	t_obj			*c_cam;
	char			sp_mode;
	char			t[10];
};

typedef struct		s_ui
{
	short			t_c;
	char			c_num;
	char			*tmp;
	char			*c_name;
	char			*r_dim;
	char			m_visible;
	char			b_hover;
	char			b_down;
	char			c_hover;
	char			c_down;
	char			ra_hover;
	char			ra_down;
	char			*n_save;
	char			save_num;
	char			b_state[19];
	char			nav_state;
	short			id;
	t_obj			*c_elem;
	SDL_Point		p_tmp;
	SDL_Rect		t_rect;
	SDL_Color		c_clr[3];
	SDL_Rect		area[13];
	SDL_Rect		ra_rect[7];
	SDL_Rect		b_rect[20];
	SDL_Rect		r_hover;
	SDL_Surface		*s_tmp;
	SDL_Surface		*s_ui;
	SDL_Surface		*s_ver;
	SDL_Surface		*s_cam;
	TTF_Font		**font;
}					t_ui;

struct				s_rt
{
	char			*filename;
	char			*w_title;
	char			verbose;
	char			**err;
	char			**inf;

	t_obj			*s_elem;

	char			run;

	SDL_Window		*win;

	t_parser		*prs;
	t_scene			*scn;

	t_timer			*fps;

	SDL_Event		event;
	SDL_Point		m_pos;
	t_ui			*ui;

	char			n_info;

	SDL_Rect		r_info;
	int				t_info;

	SDL_Cursor		**cursor;

	SDL_Surface		*w_icon;

	SDL_Surface		*s_back;

	SDL_Surface		*s_temp;

	SDL_Rect		r_view;
	SDL_Rect		r_view_m;
	SDL_Surface		*s_rend;
	SDL_Surface		*s_process;
	SDL_Texture		*t_rend;

	char			render;
};

#endif
