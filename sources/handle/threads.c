/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 13:44:28 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/02 18:35:31 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Need sufficient malloc on each pthread #pthread_attr_getstack()
** Need also a pthread_mutex handling as rt->tab is shared between threads
*/
