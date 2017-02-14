/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsdl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 16:01:42 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/03 18:40:42 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FSDL_H
# define FSDL_H

# include "../../../frameworks/SDL2.framework/headers/SDL.h"

/*
** -----------------------------------------------------------------------------
** ------------------------------ Structures -----------------------------------
** -----------------------------------------------------------------------------
*/

typedef struct	s_line
{
	int			x1;
	int			y1;
	int			x2;
	int			y2;
}				t_line;

/*
** -------------------------------- Timer --------------------------------------
*/

typedef	struct		s_timer
{
	int				fps;
	int				current;
	int				update;
	int				limit;
	char			title[128];
	unsigned		framelimit;
}					t_timer;

/*
** -----------------------------------------------------------------------------
** ------------------------------ Functions ------------------------------------
** -----------------------------------------------------------------------------
*/

void			fsdl_draw_pixel(SDL_Surface *dst, int x, int y, size_t clr);
//void			fsdl_draw_pixels(SDL_Surface *dst, int *x, int *y, size_t clr);

//void			fsdl_draw_pt(SDL_Surface *dst, SDL_Point *p, size_t clr);
void			fsdl_draw_pt(SDL_Surface *dst, size_t clr, int x, int y);
//void			fsdl_draw_points(SDL_Surface *dst, SDL_Point *p, size_t clr);

//void			fsdl_draw_line(SDL_Surface *dst, t_line *l, size_t clr);
//void			fsdl_draw_lines(SDL_Surface *dst, t_line *l, size_t clr);

//void			fsdl_draw_rect(SDL_Surface *dst, SDL_rect *r, size_t clr);
//void			fsdl_draw_rects(SDL_Surface *dst, SDL_rect *r, size_t clr);

void			fsdl_fill_rect(SDL_Surface *dst, SDL_Rect r, size_t clr);
//void			fsdl_fill_rects(SDL_Surface *dst, SDL_Rect r, size_t clr);

//size_t			fsdl_read_pixel(SDL_Surface *s, int x, int y);

int				fsdl_pt_in_rect(SDL_Point *p, SDL_Rect r);
//int				fsdl_pts_in_rect(SDL_Point *p, SDL_Rect r);

//int				fsdl_clr_to_hex(SDL_Color clr);
//SDL_Color		fsdl_hex_to_clr(int clr);

void			fsdl_fps_counter(t_timer *fps);
void			fsdl_fps_limit(t_timer *fps);

#endif
