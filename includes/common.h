/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:40:49 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/08 16:23:10 by anorjen          ###   ########.fr       */
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
# define FLAG_R 0x1
# define FLAG_Q 0x2
# define FLAG_P 0x4
# define FLAG_S 0x8
# define FLAG_A 0x10
# define FLAG_D 0x20
# define FLAG_E 0x40
# define FLAG_I 0x80
# define FLAG_K 0x100
# define FLAG_O 0x200
# define FLAG_V 0x800
# define SET_FLAG(a, f) ((a) = ((a) | (f)))
# define IS_FLAG(a, f) ((a) & (f))

typedef enum	e_input
{
	IN_STDIN = 1,
	IN_STRING = 2,
	IN_FILE = 3
}				t_input;

struct	s_ssl;

typedef struct	s_cipher_flag
{
	char	*flag;
	int		value;
}				t_cipher_flag;

typedef void	(*t_process)(struct s_ssl *ssl);

typedef struct	s_handler
{
	char		*name;
	char		*type;
	t_process	process;
}				t_handler;

typedef struct	s_ssl
{
	int				flags;
	char			*password;
	char			*key;
	char			*vector;
	char			*salt;
	char			*input;
	char			*output;
	t_dlist			*datalist;
	const t_handler	*handler;
}				t_ssl;

t_ssl	*g_ssl;

#endif
