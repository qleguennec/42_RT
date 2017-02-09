/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 17:58:11 by bsouchet          #+#    #+#             */
/*   Updated: 2017/01/07 23:18:40 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Function to init the tab that contain all errors
*/

void		init_errors(t_rt *r, int i)
{
	r->err = (char **)malloc(sizeof(char *) * 40);
	i = (
	s(&r->err[0], MSG0) && s(&r->err[1], MSG1) && s(&r->err[2], MSG2) &&
	s(&r->err[4], MSG4) && s(&r->err[5], MSG5) && s(&r->err[6], MSG6) &&
	s(&r->err[8], MSG8) && s(&r->err[11], MSG11) && s(&r->err[12], MSG12) &&
	s(&r->err[13], MSG13) && s(&r->err[16], MSG16) && s(&r->err[17], MSG17) &&
	s(&r->err[18], MSG18) && s(&r->err[19], MSG19) && s(&r->err[20], MSG20) &&
	s(&r->err[21], MSG21) && s(&r->err[22], MSG22) && s(&r->err[23], MSG23) &&
	s(&r->err[24], MSG24) && s(&r->err[25], MSG25) && s(&r->err[26], MSG26) &&
	s(&r->err[27], MSG27) && s(&r->err[28], MSG28) && s(&r->err[29], MSG29) &&
	s(&r->err[30], MSG30) && s(&r->err[31], MSG31)) ? 1 : 1;
}

/*
** Function to free all malloced elements
*/

static int	error_free(t_rt *rt, int f)
{
	(void)rt;
	(void)f;
	return (-1);
}

/*
** Function to call and print the error associated with the number (int)t
*/

int			error(t_rt *rt, int t, int f)
{
	char	*s;

	s = NULL;
	if (t == 3 && write(2, "error : ", 8) &&
	write(2, strerror(errno), ft_strlen(strerror(errno))))
		write(2, ".\n", 2);
	else if (t == 7)
		s = ft_strjoin(ft_strjoin("error : ", rt->prs->b_c, 'N'), MSG7, 'L');
	else if (t == 9)
		s = ft_strjoin(ft_strjoin(MSG9, rt->prs->b_o, 'N'),
		ft_strjoin(" and ", rt->prs->b_c, 'N'), 'B');
	else if (t == 10)
		s = ft_strjoin(ft_strjoin(MSG10, rt->prs->b_o, 'N'),
		ft_strjoin(" and ", rt->prs->b_c, 'N'), 'B');
	else if (t == 14)
		s = ft_strjoin(ft_strjoin(MSG14, rt->prs->b_o, 'N'),
		ft_strjoin(" and ", rt->prs->b_c, 'N'), 'B');
	else if (t == 15)
		s = ft_strjoin(ft_strjoin(ft_strjoin("error : ", rt->prs->b_o, 'N'),
		ft_strjoin(MSG15A, rt->prs->b_c, 'N'), 'B'), MSG15B, 'L');
	(!s) ? write(2, rt->err[t], ft_strlen(rt->err[t])) : 1;
	(s) ? write(2, s, ft_strlen(s)) : 1;
	if (s)
		free(s);
	return (error_free(rt, f));
}
