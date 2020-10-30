/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:05:39 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/30 18:12:32 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

// const t_hash	g_hashs[] = {
// 	{"md5", md5_calc, MD5_OUTPUT_SIZE, MD5_BLOCK_SIZE,
// 		MD5_OUTPUT_BLOCK_AMOUNT, NULL},
// 	{"sha256", sha256_calc, SHA256_OUTPUT_SIZE, SHA256_BLOCK_SIZE,
// 		SHA256_OUTPUT_BLOCK_AMOUNT, g_sha256_init},
// 	{"sha224", sha256_calc, SHA224_OUTPUT_SIZE, SHA256_BLOCK_SIZE,
// 		SHA224_OUTPUT_BLOCK_AMOUNT, g_sha224_init},
// 	{"sha512", sha512_calc, SHA512_OUTPUT_SIZE, SHA512_BLOCK_SIZE,
// 		SHA512_OUTPUT_BLOCK_AMOUNT, g_sha512_init},
// 	{"sha384", sha512_calc, SHA384_OUTPUT_SIZE, SHA512_BLOCK_SIZE,
// 		SHA384_OUTPUT_BLOCK_AMOUNT, g_sha384_init},
// 	{"sha512-224", sha512_calc, SHA512_224_OUTPUT_SIZE, SHA512_BLOCK_SIZE,
// 		SHA512_224_OUTPUT_BLOCK_AMOUNT, g_sha512_224_init},
// 	{"sha512-256", sha512_calc, SHA512_256_OUTPUT_SIZE, SHA512_BLOCK_SIZE,
// 		SHA512_256_OUTPUT_BLOCK_AMOUNT, g_sha512_256_init},
// 	{NULL, NULL, 0, 0, 0, NULL}
// };

const t_handler	g_handlers[] = {
	{"md5", "hash", hash_handler},
	{"sha256", "hash", hash_handler},
	{"sha224", "hash", hash_handler},
	{"sha512", "hash", hash_handler},
	{"sha384", "hash", hash_handler},
	{"sha512-224", "hash", hash_handler},
	{"sha512-256", "hash", hash_handler},
	// {"base64", "cipher", base64},
	// {"des", "cipher", des_cbc},
	// {"des-ecb", "cipher", des_ecb},
	// {"des-cbc", "cipher", des_cbc},
	{NULL, NULL, NULL}
};

static int	read_flags(int ac, char **av)
{
	int		i;

	i = 1;
	while (++i < ac)
	{
		if (ft_strcmp(av[i], "-r") == 0)
			g_ssl->r_flag = 1;
		else if (ft_strcmp(av[i], "-p") == 0)
			g_ssl->p_flag = 1;
		else if (ft_strcmp(av[i], "-q") == 0)
			g_ssl->q_flag = 1;
		else if (ft_strcmp(av[i], "-s") == 0)
		{
			g_ssl->s_flag = 1;
			return (++i);
		}
		else
		{
			if (av[i][0] == '-')
				ft_fatal_error(
					ft_strjoin("Unrecognized flag ", &(av[i][1])), 1);
			return (i);
		}
	}
	return (i);
}

static void	read_args(int ac, char **av)
{
	int		i;
	t_dlist	*datalist;

	datalist = NULL;
	if ((g_ssl = (t_ssl*)malloc(sizeof(t_ssl))) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	g_ssl->alg = av[1];
	i = read_flags(ac, av);
	if ((i == ac && !(g_ssl->s_flag)) || g_ssl->p_flag)
		ft_dlist_addback(&datalist, ft_dlist_new_elem(
			new_data("stdin", (t_input)IN_STDIN), sizeof(t_data), 1));
	if (g_ssl->s_flag && i < ac)
	{
		ft_dlist_addback(&datalist, ft_dlist_new_elem(
			new_data(av[i], (t_input)IN_STRING), sizeof(t_data), 1));
		++i;
	}
	else if (g_ssl->s_flag && i == ac)
		ft_fatal_error("String not found!", 0);
	i -= 1;
	while (++i < ac)
		ft_dlist_addback(&datalist, ft_dlist_new_elem(
			new_data(av[i], (t_input)IN_FILE), sizeof(t_data), 1));
	g_ssl->datalist = datalist;
}

static void	input_handler(void)
{
	int				i;
	t_process		handler;

	handler = NULL;
	i = -1;
	while (g_handlers[++i].name)
	{
		if (ft_strcmp(g_handlers[i].name, g_ssl->alg) == 0)
		{
			handler = g_handlers[i].process;
			break ;
		}
	}
	if (!handler)
		ft_fatal_error(ft_strjoin(g_ssl->alg, " not supported!"), 1);
	handler(g_ssl);
}

int			main(int ac, char **av)
{
	if (ac < 2)
	{
		usage();
	}
	read_args(ac, av);
	input_handler();
	ft_clean();
	return (0);
}
