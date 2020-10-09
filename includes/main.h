/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:05:56 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/09 21:52:35 by anorjen          ###   ########.fr       */
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
# include "sha224.h"
# include "sha512.h"
# include "sha384.h"
# include "sha512-224.h"
# include "sha512-256.h"

typedef uint8_t	*(*t_function)(t_data *data);

typedef struct	s_hash
{
	char		*name;
	t_function	function;
	size_t		output_size;
}				t_hash;

extern const t_hash	g_hashs[];

/*
** ft_print.c
*/

void	ft_print(t_dlist *datalist);

#endif
