/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/02 13:30:40 by bsouchet          #+#    #+#             */
/*   Updated: 2017/02/09 15:45:51 by qle-guen         ###   ########.fr       */
/*   Updated: 2017/02/09 13:31:14 by bsouchet         ###   ########.fr       */
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

# include <stdbool.h>

# include "types.h"

# include "ft_printf.h"

# define BUFF_SIZE 1

# define D (double)

# define AO 0x000000

# define BZERO(a)		ft_bzero(&a, sizeof(a))
# define MEMCHR(a, b)	ft_memchr((a), (b), sizeof(a) - 1)
# define VSPLIT(v, x)	ft_nsplit((v).data, (v).used, x, sizeof(x) - 1)
# define STRTOB10(s, x)	fmt_atoi(s, (unsigned long *)&x, 10, 0)

# define MIN(a,b)	((a <= b) ? a : b)
# define MAX(a,b)	((a > b) ? a : b)
# define ABS(x)		(((x) < 0) ? (-x) : (x))

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

char			*ft_name(char *file, char *extension);

char			*ft_strunc(char *str, int len);

char			*ft_itoa(int n);

unsigned int	ft_shtoi(const char *s);

void			ft_bzero(void *s, size_t n);

short			*ft_short_bzero(short *array, short size);

char			*ft_edit_end(char *s1, char *s2);

int				ft_checkstr(char *s1, char *s2);

void			*ft_memcpy(void *dst, const void *src, size_t len);

void			*ft_memmove(void *dst, void *src, size_t len);

void			*ft_memset(void *s, int c, size_t n);

void			*ft_mempcpy(void *dest, const void *src, size_t len);

void			*ft_memchr(const void *s, int c, size_t n);

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

unsigned char	**ft_nsplit(void *s, size_t n1, void *match, size_t n2);
unsigned char	*ft_word(void **p, size_t *n1, void *match, size_t n2);

int				vc(t_vec3 *vec1, t_vec3 vec2);
int				h(t_vec3 *vec, unsigned hex);

#endif
