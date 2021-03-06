/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 23:16:46 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/07 13:02:18 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"
#include "../libft/libft.h"

void
	vect_del
	(t_vect *v)
{
	if (!v)
		return ;
	if (v->total)
		free(v->data);
	free(v);
}
