/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:00:14 by anorjen           #+#    #+#             */
/*   Updated: 2020/09/30 19:08:09 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_TYPES_H
# define FT_SSL_TYPES_H
# include "ft_dlist.h"

typedef struct	s_ssl
{
	int			r_flag;
	int			q_flag;
	int			p_flag;
	int			s_flag;
	t_dlist		*datalist;
	char		*hash_type;
}				t_ssl;

typedef struct	s_data
{
	char		*name;
	int			type;
	int			fd;
	char		*block;
	char		*hash;
}				t_data;

#endif
