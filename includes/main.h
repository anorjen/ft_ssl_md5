/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:05:56 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/13 18:52:23 by anorjen          ###   ########.fr       */
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
# include "sha512.h"

extern const t_hash	g_hashs[];

/*
** ft_print.c
*/

void	ft_print(t_dlist *datalist);

#endif
