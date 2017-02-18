/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 22:06:56 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/16 22:07:05 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	export_object_part2(t_obj *obj, int fd)
{
	write(fd, "\t<rotation>", 11);
	ft_putfloat_fd((float)obj->rot.x, fd);
	write(fd, " ", 1);
	ft_putfloat_fd((float)obj->rot.y, fd);
	write(fd, " ", 1);
	ft_putfloat_fd((float)obj->rot.z, fd);
	write(fd, "</rotation>\n", 12);
	write(fd, "\t<color-rgb>", 12);
	ft_putfloat_fd((float)obj->clr.x, fd);
	write(fd, " ", 1);
	ft_putfloat_fd((float)obj->clr.y, fd);
	write(fd, " ", 1);
	ft_putfloat_fd((float)obj->clr.z, fd);
	write(fd, "</color-rgb>\n", 13);
	write(fd, "\t<opacity>", 10);
	ft_putfloat_fd((float)obj->opacity, fd);
	write(fd, "</opacity>\n", 11);
	if (obj->forme == T_SPHERE || obj->forme == T_CYLINDER ||
	obj->forme == T_CONE || obj->forme == T_TORUS)
	{
		write(fd, "\t<radius>", 9);
		ft_putfloat_fd((float)obj->radius, fd);
		write(fd, "</radius>\n", 10);
	}
	write(fd, "</object>\n\n", 11);
}

void		export_object(t_obj *obj, int fd)
{
	write(fd, "<object>\n", 9);
	write(fd, "\t<name>", 7);
	write(fd, (char *)obj->n, ft_strlen((char *)obj->n));
	write(fd, "</name>\n", 8);
	write(fd, "\t<type>", 7);
	export_shape_object(obj->forme, fd);
	write(fd, "</type>\n", 8);
	write(fd, "\t<material>", 11);
	export_material_object(obj->material, fd);
	write(fd, "</material>\n", 12);
	write(fd, "\t<visibility>", 13);
	(obj->visibility == 1) ? write(fd, "True", 4) : write(fd, "False", 5);
	write(fd, "</visibility>\n", 14);
	write(fd, "\t<position>", 11);
	ft_putfloat_fd((float)obj->pos.x, fd);
	write(fd, " ", 1);
	ft_putfloat_fd((float)obj->pos.y, fd);
	write(fd, " ", 1);
	ft_putfloat_fd((float)obj->pos.z, fd);
	write(fd, "</position>\n", 12);
	export_object_part2(obj, fd);
}
