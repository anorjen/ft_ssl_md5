/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:05:56 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/01 17:28:52 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include "libft.h"
# include "ft_dlist.h"
# include "ft_ssl_types.h"
# include "md5.h"

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

extern const t_hash	g_hashs[];




/*
** ft_print.c
*/

void	ft_print(t_dlist *datalist);

#endif
