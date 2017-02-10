/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:47:35 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/10 11:51:03 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_cl_interface.h"

kernel void
	test
	(global unsigned int *img_buffer
	, global t_obj *objs
	, global t_lgts *lgts
	, t_cam cam
	, short nobjs
	, short nlgts)
{
	printf("%lu objects\n", nobjs);
	printf("%lu lights\n", nlgts);
}
