/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:35:11 by bsouchet          #+#    #+#             */
/*   Updated: 2017/03/01 22:11:32 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMETERS_H
# define PARAMETERS_H

# include "obj_types.h"

# define WIN_TITLE "Raytracer Renderer - Scene : "

# define WIN_VERSION "Version : ALPHA 0.71.7"

# define WIN_ICON "./assets/images/icon.png"

# define WIN_BG (unsigned)0xFF252c34
# define PAN_BG (unsigned)0xFF343e4d
# define OUT_BG (unsigned)0xFF2c3540

# define NAV_BG (unsigned)0xFF2a2a2a
# define NAV_FG (unsigned)0xFF848484

# define HOVER_SE (unsigned)0xFF3f697e
# define FOCUS_SE (unsigned)0xFF4e8ea8
# define LEFT_SE (unsigned)0xFF29323e

# define BOX_BG (unsigned)0xFF2a3440

# define INFO_BG (unsigned)0xFF2c3540

# define WHITE_BG (unsigned)0xFFbdbdbd
# define YELLOW_BG (unsigned)0xFFffd500
# define BLUE_BG (unsigned)0xFF006fff

# define REND_W 1244
# define REND_H 588

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

# define CK_DOWN rt->event.key.keysym.sym

# define DRAW_C draw_case_active

# define DELETE_RECT &(SDL_Rect){874, 370, 170, 22}

# define MAX_FPS 30

#endif
