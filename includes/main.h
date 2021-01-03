/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:05:56 by anorjen           #+#    #+#             */
/*   Updated: 2020/12/15 16:37:17 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdlib.h>
# include <fcntl.h>

# include <sys/types.h>
# include <sys/stat.h>

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

/*
** des
*/

void		des_ecb(t_ssl *ssl);
void		des_ecb_encrypt_input(t_ssl *ssl);
void		des_ecb_decrypt_input(t_ssl *ssl);

void		des_ecb_crypt(uint8_t **input, size_t size, uint64_t mk, int enc);
void		make_keys(uint64_t keys[16], uint64_t master_key, int rev);
void		make_half_keys(uint64_t half_keys[16], uint64_t starter);
uint64_t	circular_shift_left(uint64_t key, int bits);
uint64_t	des_ecb_get_eight_bytes(uint8_t *data);
uint64_t	des_ecb_process_block(uint64_t input, uint64_t keys[16]);
void		des_ecb_put_eight_bytes(uint8_t *data, uint64_t ul64);



void		des_ecb_hex_key_invalid_format(void *memory);
uint64_t	des_ecb_get_key(t_ssl *ssl);
void		des_ecb_print_key(uint64_t master_key);

uint64_t	make_ip1(uint64_t m);
uint64_t	make_ip2(uint64_t rxlx);
uint64_t	make_ebit(uint64_t r0);
uint64_t	get_s_boxes_value(uint64_t xor0);
uint64_t	make_pperm(uint64_t sb0);
uint64_t	make_pc1(uint64_t k);
uint64_t	make_pc2(uint64_t c_half, uint64_t d_half);

int			is_valid_hex_key(unsigned char *s);
uint64_t	text_to_ul64(unsigned char *s);
uint64_t	hex_to_ul64(unsigned char *s);
void		ul64hex_to_stdout(uint64_t ul64);

uint8_t		*stdin_read_eof(size_t *count);
uint8_t		*stdin_read_line(size_t *count);


#endif
