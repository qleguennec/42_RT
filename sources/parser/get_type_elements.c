/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_elements.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 22:09:34 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/14 11:18:18 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char		*shape_object(short shape)
{
	if (shape == T_SPHERE)
		return ("Sphere ");
	else if (shape == T_CUBE)
		return ("Cube ");
	else if (shape == T_CYLINDER)
		return ("Cylinder ");
	else if (shape == T_PLANE)
		return ("Plane ");
	else if (shape == T_CONE)
		return ("Cone ");
	else if (shape == T_TORUS)
		return ("Torus ");
	else if (shape == T_PYRAMID)
		return ("Pyramid ");
	else if (shape == T_TETRAHEDRON)
		return ("Tetrahedron ");
	else if (shape == T_OCTAHEDRON)
		return ("Octahedron ");
	else if (shape == T_MOEBIUS)
		return ("Moebius ");
	return ("Object ");
}

int			export_shape_object(short shape, int fd)
{
	if (shape == T_SPHERE)
		return (write(fd, "Sphere", 6));
	else if (shape == T_CUBE)
		return (write(fd, "Cube", 4));
	else if (shape == T_CYLINDER)
		return (write(fd, "Cylinder", 8));
	else if (shape == T_PLANE)
		return (write(fd, "Plane", 5));
	else if (shape == T_CONE)
		return (write(fd, "Cone", 4));
	else if (shape == T_TORUS)
		return (write(fd, "Torus", 5));
	else if (shape == T_PYRAMID)
		return (write(fd, "Pyramid", 7));
	else if (shape == T_TETRAHEDRON)
		return (write(fd, "Tetrahedron", 11));
	else if (shape == T_OCTAHEDRON)
		return (write(fd, "Octahedron", 10));
	else if (shape == T_MOEBIUS)
		return (write(fd, "Moebius", 7));
	return (write(fd, "Object", 6));
}

int			export_material_object(short material, int fd)
{
	if (material == T_LAMBERT)
		return (write(fd, "Lambert", 7));
	else if (material == T_BLINN)
		return (write(fd, "Blinn", 5));
	else if (material == T_PHONG)
		return (write(fd, "Phong", 5));
	else if (material == T_CUSTOM)
		return (write(fd, "Custom", 6));
	return (write(fd, "Custom", 6));
}

char		*light_type(short type)
{
	if (type == T_DIFFUSE)
		return ("Point Light ");
	else if (type == T_DIRECTIONAL)
		return ("Directional Light ");
	else if (type == T_SPOT)
		return ("Spot Light ");
	return ("Light ");
}
