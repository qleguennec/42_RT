/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_gen_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/12 14:16:41 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/12 16:40:57 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libvect.h"
#include "malloc.h"
#include "rt.h"
#include "obj_type.h"

// TODO remove debug includes
#include <assert.h>

#define TESTSCENE_N_OBJS	5
#define TESTSCENE_N_LGTS	1
#define TESTSCENE_SEED		34023784

static void
	rand1
	(cl_float *x)
{
	*x = (float)rand() / (float)RAND_MAX;
}

static void
	rand3
	(cl_float3 *v3)
{
	rand1(&v3->x);
	rand1(&v3->y);
	rand1(&v3->z);
}

static void
	rand_obj
	(t_obj *obj)
{
	obj->type = 'O';
	rand3(&obj->pos);
	rand3(&obj->rot);
	rand1(&obj->width);
}

static void
	rand_lgt
	(t_obj *obj)
{
	obj->type = 'L';
	rand3(&obj->pos);
	rand3(&obj->rot);
}

void
	test_gen_scene
	(t_scene *scene)
{
	size_t	i;
	t_obj	*obj;
	t_obj	*lgt;

	i = 0;
	srand(TESTSCENE_SEED);
	assert(scene->b_objs == NULL);
	assert(scene->b_lgts == NULL);
	while (i < TESTSCENE_N_OBJS)
	{
		MALLOC1(obj);
		obj->next = scene->b_objs;
		scene->b_objs = obj;
		rand_obj(scene->b_objs);
		i++;
	}
	i = 0;
	while (i < TESTSCENE_N_LGTS)
	{
		MALLOC1(lgt);
		lgt->next = scene->b_lgts;
		scene->b_lgts = lgt;
		rand_lgt(scene->b_lgts);
		i++;
	}
	scene->n_objs = TESTSCENE_N_OBJS;
	scene->n_lgts = TESTSCENE_N_LGTS;
}
