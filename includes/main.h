/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:05:56 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/30 17:56:17 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>

# include "libft.h"
# include "ft_dlist.h"
# include "hash_common.h"

# include "md5.h"
# include "sha256.h"
# include "sha512.h"

// typedef struct	s_ssl
// {
// 	int			r_flag;
// 	int			q_flag;
// 	int			p_flag;
// 	int			s_flag;
// 	t_dlist		*datalist;
// 	char		*alg;
// }				t_ssl;

typedef void		(*t_process)(t_ssl *ssl);

typedef struct	s_handler
{
	char		*name;
	char		*type;
	t_process	process;
}				t_handler;

t_ssl			*g_ssl;

/*
** hash_handler.c
*/

void	hash_handler(t_ssl *g_ssl);

/*
** ft_print.c
*/

void	ft_print(t_dlist *datalist);

#endif
