/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:05:56 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/14 23:17:30 by anorjen          ###   ########.fr       */
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

// typedef void		(*t_process)(t_ssl *ssl);

// typedef struct	s_handler
// {
// 	char		*name;
// 	char		*type;
// 	t_process	process;
// }				t_handler;

t_ssl			*g_ssl;

/*
** hash_handler.c
*/

void	hash_handler(t_ssl *g_ssl);

/*
** ft_print.c
*/

void	ft_print(t_dlist *datalist);

/*
** hash_args.c
*/

void	read_hash_args(int ac, char **av);

/*
** cipher_args.c
*/

void	read_cipher_args(int ac, char **av);

/*
** base64.c
*/

void	base64(t_ssl *ssl);
void	base64_encode(t_ssl *ssl);
void	base64_decode(t_ssl *ssl);
int		trim_end(char *str, int size);

#endif
