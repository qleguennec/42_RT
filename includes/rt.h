/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 17:26:10 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/08 16:34:18 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <math.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <pthread.h>

# include "../libraries/fsdl/include/fsdl.h"
# include "../libraries/libft/include/libft.h"
# include "../libraries/libvec/include/libvec.h"

# include "../frameworks/SDL2.framework/headers/SDL.h"
# include "../frameworks/SDL2_ttf.framework/headers/SDL_ttf.h"
# include "../frameworks/SDL2_image.framework/headers/SDL_image.h"

# ifdef __APPLE__
#  include "OpenCL/opencl.h"
# else
#  include "CL/cl.h"
# endif

/*
** -----------------------------------------------------------------------------
** ------------------------------- Parameters ----------------------------------
** -----------------------------------------------------------------------------
*/

# define WIN_TITLE "Raytracer Renderer - Scene : "

# define WIN_ICON "./assets/images/icon.png"

# define WIN_VERSION "Ver. ALPHA 0.64 \"CRASH\""

# define WIN_BG (unsigned)0xFF252525
# define PAN_BG (unsigned)0xFF353535
# define LOL_BG (unsigned)0x8f8f8fFF
# define OUT_BG (unsigned)0xFF2b2b2b

# define NAV_BG (unsigned)0xFF2a2a2a
# define NAV_FG (unsigned)0xFF848484

# define INFO_BG (unsigned)0xFF2f2f2f

# define WHITE_BG (unsigned)0xFFbdbdbd
# define YELLOW_BG (unsigned)0xFFffd500
# define BLUE_BG (unsigned)0xFF006fff

# define WIN_W 1280
# define WIN_H 720

# define WIN_W_MID 640
# define WIN_H_MID 360

# define N_CAMS	40
# define N_LGTS	15
# define N_OBJS 80

# define SDL_PF 373694468

# define IMG "Image"

# define RECT_OUTLINER rt->ui->c_elem->r_ol

# define MAX_FPS 30

/*
** -----------------------------------------------------------------------------
** ----------------------------- Errors Messages -------------------------------
** -----------------------------------------------------------------------------
*/

# define MSG0	"error: Dynamic memory allocation failed.\n"
# define MSG1	"usage: ./rt scene_file [-V | -Verbose]\n"

# define MSG2	"error: The input file haven't the right extension (.rt).\n"
# define MSG4	"error: The input file isn't a valid RT scene.\n"

# define MSG5	"error: XML symbols \"-->\" is missing in config file (.rt).\n"
# define MSG6	"error: XML symbols \"<!--\" is missing in config file (.rt).\n"

# define MSG7	" is missing in config file (.rt).\n"
# define MSG8	"error: Invalid character(s) or balise(s) name in file (.rt).\n"
# define MSG9	"error: Nothing found inside balises "
# define MSG10	"error: Invalid element(s) inside balises "

# define MSG11	"error: Ambient (AO) value must be set between 0. and 1.\n"
# define MSG12	"error: Anti-Aliasing (AA) value must be : 0, 2, 4, 8 or 16.\n"
# define MSG13	"error: Max-Reflexion value must be set between 0 and 10.\n"
# define MSG14	"error: Invalid value inside balises "
# define MSG15A	" is missing inside "
# define MSG15B	" balises in config file (.rt).\n"
# define MSG16	"error: Focal Lenght value must be set between 18 and 200.\n"

# define MSG17	"error: At least one camera is needed in config file (.rt).\n"
# define MSG18	"error: At least one light is needed in config file (.rt).\n"
# define MSG19	"error: At least one object is needed in config file (.rt).\n"

# define MSG20	"error: Too many cameras in config file (.rt).\n"
# define MSG21	"error: Too many lights in config file (.rt).\n"
# define MSG22	"error: Too many objects in config file (.rt).\n"

# define MSG23	"error: Opacity value must be set between 0. and 1.0.\n"

# define MSG24	"error: Tag <position> is needed for every camera.\n"
# define MSG25	"error: Tag <rotation> is needed for every camera.\n"
# define MSG26	"error: Tag <position> is needed for every light.\n"
# define MSG27	"error: Tag <position> is needed for every object.\n"

# define MSG28	"error: Tag <type> is needed for every object.\n"

# define MSG29	"error: Failed to initialize the SDL Framework.\n"
# define MSG30	"error: Failed to create the SDL window struct.\n"
# define MSG31	"error: Failed to create the SDL renderer struct.\n"
# define MSD32	"error: Failed to find or import image.\n"

/*
** -----------------------------------------------------------------------------
** ----------------------------- Infos Messages --------------------------------
** -----------------------------------------------------------------------------
*/

# define INF0	"Info : Program successfully launched."

# define INF1	"Info : New camera added to the scene."
# define INF2	"Info : New point light added to the scene."
# define INF3	"Info : New directional light added to the scene."
# define INF4	"Info : New spot light added to the scene."
# define INF5	"Info : New sphere added to the scene."
# define INF6	"Info : New cube added to the scene."
# define INF7	"Info : New cylinder added to the scene."
# define INF8	"Info : New plane added to the scene."
# define INF9	"Info : New cone added to the scene."

# define INF14	"Info : Lambert Material successfully set to the object."
# define INF15	"Info : Phong Material successfully set to the object."
# define INF16	"Info : Blinn Material successfully set to the object."
# define INF17	"Info : Wood Material successfully set to the object."

# define INF21	"Info : Render frame successfully exported in PNG."

# define INF24	"Info : Special mode disabled."
# define INF25	"Info : Special mode changed to Sepia."
# define INF26	"Info : Special mode changed to Black & white."
# define INF27	"Info : Special mode changed to Cartoon."

# define INF30	"Info : Editor mode actived (edit value with + or -)."

# define INF32	"Info : \"%s\" selected."
# define INF33	"Info : \"%s\" is now set as the current camera."
# define INF34	"Info : \"%s\" is now hidden."
# define INF35	"Info : \"%s\" is now visible."

# define REND00	"Rendering in progress... (Frame %03d/%d)"
# define REND01	"Render paused (Frame %03d/%d)"

/*
** -----------------------------------------------------------------------------
** ------------------------------ XML Balises ----------------------------------
** -----------------------------------------------------------------------------
*/

# define BO_S	"<scene>"
# define BC_S	"</scene>"

# define BO_C	"<camera>"
# define BC_C	"</camera>"

# define BO_L	"<light>"
# define BC_L	"</light>"

# define BO_O	"<object>"
# define BC_O	"</object>"

# define BO_N	"<name>"
# define BC_N	"</name>"

# define BO_A	"<ambient>"
# define BC_A	"</ambient>"

# define BO_AA	"<anti-aliasing>"
# define BC_AA	"</anti-aliasing>"

# define BO_MR	"<max-reflexion>"
# define BC_MR	"</max-reflexion>"

# define BO_P	"<position>"
# define BC_P	"</position>"

# define BO_R	"<rotation>"
# define BC_R	"</rotation>"

# define BO_FL	"<focal>"
# define BC_FL	"</focal>"

# define BO_V	"<visibility>"
# define BC_V	"</visibility>"

# define BO_I	"<intensity>"
# define BC_I	"</intensity>"

# define BO_T	"<type>"
# define BC_T	"</type>"

# define BO_M	"<material>"
# define BC_M	"</material>"

# define BO_OP	"<opacity>"
# define BC_OP	"</opacity>"

# define BO_CR	"<color-rgb>"
# define BC_CR	"</color-rgb>"

# define BO_CH	"<color-hex>"
# define BC_CH	"</color-hex>"

/*
** -----------------------------------------------------------------------------
** ------------------------------ Structures -----------------------------------
** -----------------------------------------------------------------------------
*/

typedef struct s_scene	t_scene;
typedef struct s_rt		t_rt;

/*
** ---------------------------- Scene Elements ---------------------------------
*/

typedef struct		s_iter
{
	int				s;
	int				x;
	int				y;
	struct s_iter	*next;
}					t_iter;

typedef	struct		s_obj
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
}					t_obj;

/*
** ---------------------------- Multithreading ---------------------------------
*/

typedef struct		s_tharg
{
	t_rt			*rt;
	t_scene			*scn;
	int				*i;
	int				*j;
	int				*s;
	t_vec3			***tab;
}					t_tharg;

typedef struct		s_thread
{
	pthread_t		thread;
	pthread_attr_t	attr;
	t_tharg			arg;
	struct s_thread	*next;
}					t_thread;

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
	t_vec3			vec;
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
	//t_skybox		*skybox;
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

/*
** -----------------------------------------------------------------------------
** --------------------------------- Parser ------------------------------------
** -----------------------------------------------------------------------------
*/

void				init_cam(t_rt *rt, short pos, short t);
void				init_light(t_rt *rt, short pos, short t);
void				init_object(t_rt *rt, short pos, short t);
int					init_structures(t_rt *rt);

char				*clear_line(t_parser *p, char *str, int i, int n);

int					check_balises(t_rt *rt, char *b_open, char *b_close);

int					check_scene(t_rt *rt);
int					check_camera(t_rt *rt, short i);
int					check_light(t_rt *rt, short i);
int					check_object(t_rt *rt);

int					get_i(t_rt *rt, int b_end, char *s, char *e);
int					get_d(t_rt *rt, int b_end, char *s, char *e);
int					get_v(t_rt *rt, int b_e, char *s, char *e);
int					get_b(t_rt *rt, int b_end, char *s, char *e);
int					get_h(t_rt *rt, int b_end, char *s, char *e);

char				*get_s(t_parser *r, int b_end, int b_size);
int					get_m(t_rt *rt, int b_end, char *s, char *e);
int					get_t(t_rt *rt, int b_end, char *s, char *e);

int					set_scene(t_rt *rt, int b_end, int e);
int					add_element(t_rt *rt, int b_end, int e, char type);

t_obj				*assign_default_obj_values(t_obj *obj, char t, int type);
t_obj				*assign_obj_values(t_obj *obj, t_obj *tmp, char t,
					int type);

/*
** -----------------------------------------------------------------------------
** ---------------------------------- GUI --------------------------------------
** -----------------------------------------------------------------------------
*/

void				init_gui_structure(t_rt *rt);

void				draw_panel(t_rt *rt, int p, int type);
void				draw_button(t_rt *rt, int b_num, int type);

int					draw_renderer_info(t_rt *rt);
void				draw_current_camera_name(t_rt *rt, short type);
int					draw_state_frame(t_rt *rt);
int					draw_info_bar(t_rt *rt);

void				draw_scene_parameters(t_rt *rt);

void				draw_outliner(t_rt *rt, int i, int max);
void				draw_outliner_element(t_rt *rt, t_obj *obj, int state);
void				draw_nav_element(t_rt *rt, int state);
void				draw_top_nav_button(t_rt *rt, int state);
void				draw_bottom_nav_button(t_rt *rt, int state);

void				draw_selected_element(t_rt *rt);

void				draw_materials(t_rt *rt, char type);

void				draw_special_mode(t_rt *rt, int r_num, int type);

void				save_to_png(t_rt *rt);

/*
** -----------------------------------------------------------------------------
** ------------------------------- Renderer ------------------------------------
** -----------------------------------------------------------------------------
*/

void				init_renderer(t_rt *rt);

int					create_window(t_rt *rt);

void				render_frame(t_rt *rt);
void				render_loop(t_rt *rt);

void				thread_render(t_tharg *arg);

/*
** -----------------------------------------------------------------------------
** -------------------------------- Handle -------------------------------------
** -----------------------------------------------------------------------------
*/

/*
** ---------------------------- Handle Events ----------------------------------
*/

void				handle_events(t_rt *rt);

/*
** --------------------------- Handle Elements ---------------------------------
*/

void				add_new_element(t_rt *rt, char type);

/*
** ------------------------------ Handle GUI -----------------------------------
*/

void				handle_buttons(t_rt *rt);
void				handle_buttons_down(t_rt *rt);

void				execute_button(t_rt *rt, int button);

/*
** --------------------------- Handle Outliner ---------------------------------
*/

void				handle_outliner(t_rt *rt, int pos, int tmp, int type);
void				handle_outliner_down(t_rt *rt);

/*
** ------------------------- Handle Special Mode -------------------------------
*/

void				handle_special_modes_down(t_rt *rt);
void				handle_special_mode(t_rt *rt, int i);

/*
** ----------------------------- Handle Mouse ----------------------------------
*/

void				handle_left_click_up(t_rt *rt);
void				handle_left_click_down(t_rt *rt);

void				handle_right_click_down(t_rt *rt);

void				handle_double_click_down(t_rt *rt);

void				handle_motion_mouse(t_rt *rt);

/*
** --------------------------- Handle Keyboard ---------------------------------
*/

void				handle_keyboard(t_rt *rt);

/*
** -------------------------- Handle Multithread -------------------------------
*/

void				set_thread(t_thread *t, t_rt *rt, int *i, int *j, int *s);
char				join_thread(t_thread *t);
char				destroy_thread_attr(t_thread *t);

/*
** ------------------------- Handle Linked Lints -------------------------------
*/

t_iter				*lst_new_iter(t_iter **iter, int i, int x, int y);
t_thread			*lst_new_thread(t_thread **thread);

t_obj				*lst_new_camera(t_rt *rt, t_obj *objs, int type);
t_obj				*lst_new_light(t_rt *rt, t_obj *objs, int type);
t_obj				*lst_new_object(t_rt *rt, t_obj *objs, int type);

/*
** ---------------------------- Handle Errors ----------------------------------
*/

void				init_errors(t_rt *r, int i);
int					error(t_rt *rt, int t, int f);

/*
** --------------------------- Handle Info Bar ---------------------------------
*/

void				init_informations(t_rt *r, int i);

/*
** -----------------------------------------------------------------------------
** --------------------------------- Misc --------------------------------------
** -----------------------------------------------------------------------------
*/

void				print_verbose(t_rt *rt);

int					free_elements(t_rt *rt);

#endif
