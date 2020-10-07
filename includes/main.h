/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:05:56 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/06 14:14:35 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>

# include "libft.h"
# include "ft_dlist.h"
# include "common.h"

# include "md5.h"
# include "sha256.h"

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
