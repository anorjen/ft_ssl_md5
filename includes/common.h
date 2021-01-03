/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:40:49 by anorjen           #+#    #+#             */
/*   Updated: 2020/12/15 16:08:42 by anorjen          ###   ########.fr       */
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

typedef struct	s_data
{
	char		*name;
	t_input		type;
	int			fd;
	char		*hash;
	char		*error;
	int			state;
	uint64_t	length;
}				t_data;

typedef struct	s_ssl
{
	int				flags;
	char			*password;
	char			*key;
	char			*vector;
	char			*salt;
	char			*input;
	char			*output;
	int				out_fd;
	unsigned long	master_key;
	unsigned long	master_iv;
	unsigned long	des3_key1;
	unsigned long	des3_key2;
	unsigned long	des3_key3;
	t_dlist			*datalist;
	const t_handler	*handler;
}				t_ssl;

t_ssl	*g_ssl;

extern uint8_t	g_pc1_table[];
extern uint8_t	g_pc2_table[];
extern uint8_t	g_ip1_table[];
extern uint8_t	g_ip2_table[];
extern uint8_t	g_ebit_table[];
extern uint8_t	g_pperm_table[];
extern uint8_t	g_left_shifts[];
extern uint8_t	g_s1_box[];
extern uint8_t	g_s2_box[];
extern uint8_t	g_s3_box[];
extern uint8_t	g_s4_box[];
extern uint8_t	g_s5_box[];
extern uint8_t	g_s6_box[];
extern uint8_t	g_s7_box[];
extern uint8_t	g_s8_box[];
extern uint8_t	*g_s_boxes[];

#endif
