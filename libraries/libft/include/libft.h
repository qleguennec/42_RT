/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 13:30:40 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/02 18:14:52 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <errno.h>
# include <math.h>

# include "ft_printf.h"
# include "../../libvec/include/libvec.h"

# define BUFF_SIZE 1

# define D (double)

# define AO 0x000000

char			*ft_name(char *file, char *extension);

char			*ft_strunc(char *str, int len);

char			*ft_itoa(int n);

unsigned int	ft_shtoi(const char *s);

char			*ft_bzero(char *str, short size);

short			*ft_short_bzero(short *array, short size);

char			*ft_edit_end(char *s1, char *s2);

int				ft_checkstr(char *s1, char *s2);

void			*ft_memcpy(void *dst, void *src, size_t len);

void			*ft_memmove(void *dst, void *src, size_t len);

char			*ft_strchr(char *str, int c);

int				ft_strlen(char *str);

int				ft_strlen_wspace(char *str);

char			*ft_strjoin(char *s1, char *s2, char type);

char			*ft_strdup(char *str);

int				ft_strchr_end(char *str, char *find);

int				get_next_line(int fd, char **line);

int				ft_shade_color(int clr, double val);

int				ft_gt_colors(int clr1, int clr2, double val);

int				ft_add_ao(int clr, double percent);

int				ft_strcmp(char *s1, char *s2, int s);

int				ft_strlcmp(char *s1, char *s2);

int				ft_lcmp(char *s1, char *s2);

int				ft_atoi(char *str, int i);

double			ft_atof(char *str, int i);

char			*ft_ftoa(float num);

char			*ft_dtoa(double num);

char			*ft_getstr(char *buf, int s, int e);

int				i(int *elem1, int elem2);

int				d(double *elem1, double elem2);

int				s(char **elem1, char *elem2);

int				vc(t_vec3 *vec1, t_vec3 vec2);

int				h(t_vec3 *vec, unsigned hex);

void			ft_putshort(short num);

void			ft_putint(int num);

void			ft_putfloat(float num);

void			ft_putdouble(double num);

size_t			ft_strlen_w(wchar_t *str);
void			ft_putnbrlong(long long int nb);
char			*ft_octal_itoa(unsigned long long n);
char			*ft_unsigned_itoa(unsigned long int n);
char			*ft_hexa_itoa(unsigned long long n);
int				ft_nbrlen(intmax_t nb);
int				ft_nbrlonglen(long long nb);

void			ft_putchar(char c);
void			ft_putstr(char const *str);
void			ft_putendl(char const *str);
void			ft_putnl(void);

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *str, int fd);
void			ft_putendl_fd(char const *str, int fd);

char			*comment(char *comment);

#endif
