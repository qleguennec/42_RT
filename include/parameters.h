/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 15:35:11 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/11 20:12:06 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMETERS_H
# define PARAMETERS_H

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

# define T_SPHERE		0
# define T_CUBE			1
# define T_CYLINDER		2
# define T_PLANE		3
# define T_CONE			4
# define T_TORUS		5
# define T_PYRAMID		6
# define T_TETRAHEDRON	7
# define T_OCTAHEDRON	8
# define T_MOEBIUS		9

# define T_DIFFUSE		0
# define T_DIRECTIONAL	1
# define T_SPOT			2

#endif
