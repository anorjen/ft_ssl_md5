/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:40:49 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/30 17:56:07 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include "ft_dlist.h"

# define READ_BLOCK_SIZE 1024
# define L_ENDIAN 0
# define B_ENDIAN 1
# define ROTR64(x, s) (((x) >> (s)) | ((x) << (64 - (s))))
# define ROTR32(x, s) (((x) >> (s)) | ((x) << (32 - (s))))
# define ROTL32(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

typedef enum	e_input
{
	IN_STDIN = 1,
	IN_STRING = 2,
	IN_FILE = 3
}				t_input;

typedef struct	s_ssl
{
	int			r_flag;
	int			q_flag;
	int			p_flag;
	int			s_flag;
	t_dlist		*datalist;
	char		*alg;
}				t_ssl;

t_ssl	*g_ssl;

#endif
