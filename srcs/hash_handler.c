/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:42:54 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/30 18:42:46 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

const t_hash	g_hashs[] = {
	{"md5", md5_calc, MD5_OUTPUT_SIZE, MD5_BLOCK_SIZE, NULL},
	{"sha256", sha256_calc, SHA256_OUTPUT_SIZE, SHA256_BLOCK_SIZE, g_sha256_init},
	{"sha224", sha256_calc, SHA224_OUTPUT_SIZE, SHA256_BLOCK_SIZE, g_sha224_init},
	{"sha512", sha512_calc, SHA512_OUTPUT_SIZE, SHA512_BLOCK_SIZE, g_sha512_init},
	{"sha384", sha512_calc, SHA384_OUTPUT_SIZE, SHA512_BLOCK_SIZE, g_sha384_init},
	{"sha512-224", sha512_calc, SHA512_224_OUTPUT_SIZE, SHA512_BLOCK_SIZE, g_sha512_224_init},
	{"sha512-256", sha512_calc, SHA512_256_OUTPUT_SIZE, SHA512_BLOCK_SIZE, g_sha512_256_init},
	{NULL, NULL, 0, 0, NULL}
};

// const t_hash	g_hashs[] = {
// 	{"md5", md5_calc},
// 	{"sha256", sha256_calc},
// 	{"sha224", sha256_calc},
// 	{"sha512", sha512_calc},
// 	{"sha384", sha512_calc},
// 	{"sha512-224", sha512_calc},
// 	{"sha512-256", sha512_calc},
// 	{NULL, NULL}
// };

static const t_hash	*find_hash(t_ssl *ssl)
{
	int	i;

	i = -1;
	while(g_hashs[++i].name)
	{
		if (ft_strcmp(g_hashs[i].name, ssl->alg) == 0)
			return (&(g_hashs[i]));
	}
	ft_fatal_error("hash not supported!", 0);
	return (NULL);
}

void	hash_handler(t_ssl *ssl)
{
	char			*hash;
	t_dlist			*input;
	const t_hash	*h;

	h = find_hash(ssl);
	input = ssl->datalist;
	while (input)
	{
		hash = h->t_hashfunc(input->content, h);
		((t_data*)input->content)->hash = hash;
		if (hash == NULL)
		{
			((t_data*)input->content)->state = 1;
			if (!((t_data*)input->content)->error)
				((t_data*)input->content)->error = " hash handler ERROR!";
		}
		input = input->next;
	}
	ft_print(ssl->datalist);
}
