/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:05:56 by anorjen           #+#    #+#             */
/*   Updated: 2020/09/30 19:06:16 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include "libft.h"
# include "ft_dlist.h"
# include "ft_ssl_types.h"
# include "md5.h"

# define STDIN 1
# define STRING 2
# define FILE 3

// typedef struct	s_ssl
// {
// 	int			r_flag;
// 	int			q_flag;
// 	int			p_flag;
// 	int			s_flag;
// 	t_dlist		*datalist;
// 	char		*hash_type;
// }				t_ssl;

// typedef struct	s_data
// {
// 	char		*name;
// 	int			type;
// 	int			fd;
// 	char		*block;
// 	char		*hash;
// }				t_data;

typedef int	(*t_function)(t_data *data);

typedef struct	s_hash
{
	char		*name;
	t_function	function;
}				t_hash;

t_hash	g_hashs[2] = {
	{"md5", ft_md5},
	{"null", NULL}
};

t_ssl	*g_ssl;

/*
** ft_error.c
*/

void	ft_error(char *message);
void	ft_fatal_error(char *message);
void	usage(void);
void	ft_clean(void);

/*
** ft_data.c
*/

t_data	*new_data(char *name, int type);
void	del_data(t_data *data);

#endif
