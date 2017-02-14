/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 15:10:20 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/14 11:17:08 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		export_scene_parameters(t_scene *scn, int fd)
{
	write(fd, "<!--------- Global Settings ---------->\n\n", 41);
	write(fd, "<scene>\n", 8);
	write(fd, "\t<name>", 7);
	write(fd, (char *)scn->name, ft_strlen((char *)scn->name));
	write(fd, "</name>\n", 8);
	write(fd, "\t<ambient>", 10);
	ft_putfloat_fd((float)scn->ambient, fd);
	write(fd, "</ambient>\n", 11);
	write(fd, "\t<anti-aliasing>", 16);
	ft_putint_fd((int)scn->aa, fd);
	write(fd, "</anti-aliasing>\n", 17);
	write(fd, "\t<max-reflexion>", 16);
	ft_putint_fd((int)scn->m_ref, fd);
	write(fd, "</max-reflexion>\n", 17);
	write(fd, "</scene>\n\n", 10);
}

void		export_camera(t_obj *cam, int fd)
{
	write(fd, "<camera>\n", 9);
	write(fd, "\t<name>", 7);
	write(fd, (char *)cam->n, ft_strlen((char *)cam->n));
	write(fd, "</name>\n", 8);
	write(fd, "\t<position>", 11);
	ft_putfloat_fd((float)cam->pos.x, fd);
	write(fd, " ", 1);
	ft_putfloat_fd((float)cam->pos.y, fd);
	write(fd, " ", 1);
	ft_putfloat_fd((float)cam->pos.z, fd);
	write(fd, "</position>\n", 12);
	write(fd, "\t<rotation>", 11);
	ft_putfloat_fd((float)cam->rot.x, fd);
	write(fd, " ", 1);
	ft_putfloat_fd((float)cam->rot.y, fd);
	write(fd, " ", 1);
	ft_putfloat_fd((float)cam->rot.z, fd);
	write(fd, "</rotation>\n", 12);
	write(fd, "\t<focal>", 8);
	ft_putshort_fd((short)cam->focal, fd);
	write(fd, "</focal>\n", 9);
	write(fd, "</camera>\n\n", 11);
}

void		export_light(t_obj *light, int fd)
{
	write(fd, "<light>\n", 8);
	write(fd, "\t<name>", 7);
	write(fd, (char *)light->n, ft_strlen((char *)light->n));
	write(fd, "</name>\n", 8);
	write(fd, "\t<type>", 7);
	if (light->forme == T_DIFFUSE)
		write(fd, "Diffuse", 7);
	else if (light->forme == T_DIRECTIONAL)
		write(fd, "Directionnal", 12);
	else
		write(fd, "Spot", 4);
	write(fd, "</type>\n", 8);
	write(fd, "\t<visibility>", 13);
	(light->visibility == 1) ? write(fd, "True", 4) : write(fd, "False", 5);
	write(fd, "</visibility>\n", 14);
	write(fd, "\t<position>", 11);
	ft_putfloat_fd((float)light->pos.x, fd);
	write(fd, " ", 1);
	ft_putfloat_fd((float)light->pos.y, fd);
	write(fd, " ", 1);
	ft_putfloat_fd((float)light->pos.z, fd);
	write(fd, "</position>\n", 12);
	write(fd, "\t<color-rgb>", 12);
	ft_putfloat_fd((float)light->clr.x, fd);
	write(fd, " ", 1);
	ft_putfloat_fd((float)light->clr.y, fd);
	write(fd, " ", 1);
	ft_putfloat_fd((float)light->clr.z, fd);
	write(fd, "</color-rgb>\n", 13);
	write(fd, "\t<intensity>", 12);
	ft_putfloat_fd((float)light->intensity, fd);
	write(fd, "</intensity>\n", 13);
	write(fd, "</light>\n\n", 10);
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

void		export_elements(t_rt *rt, int fd)
{
	t_obj		*objs;
	
	export_scene_parameters(rt->scn, fd);
	write(fd, "<!------------ Camera(s) ------------->\n\n", 41);
	objs = rt->scn->o->next;
	while (objs != NULL && objs->type == 'C')
	{
		export_camera(objs, fd);
		objs = objs->next;
	}
	write(fd, "<!------------ Light(s) -------------->\n\n", 41);
	objs = rt->scn->b_lgts->next;
	while (objs != NULL && objs->type == 'L')
	{
		export_light(objs, fd);
		objs = objs->next;
	}
	write(fd, "<!------------ Object(s) ------------->\n\n", 41);
	objs = rt->scn->b_objs->next;
	while (objs != NULL)
	{
		export_object(objs, fd);
		objs = objs->next;
	}
}

void		export_config_file(t_rt *rt)
{
	static int	value = 1;
	static int	fd = 1;
	char		*tmp;
	char		*scene_name;

	scene_name = (char *)ft_name(rt->filename, ".rt");
	tmp = ft_strf("test -e scenes/%s_%d.rt", scene_name, value);
	while (system(tmp) == 0)
	{
		free(tmp);
		tmp = ft_strf("test -e scenes/%s_%d.rt", scene_name, ++value);
	}
	free(tmp);
	tmp = ft_strf("touch scenes/%s_%d.rt", scene_name, value);
	system(tmp);
	free(tmp);
	tmp = ft_strf("scenes/%s_%d.rt", scene_name, value);
	fd = open(tmp, O_WRONLY | O_APPEND);
	free(tmp);
	export_elements(rt, fd);
	free(scene_name);
	close(fd);
}
