/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:05:39 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/08 16:14:19 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

const t_handler	g_handlers[] = {
	{"md5", "hash", hash_handler},
	{"sha256", "hash", hash_handler},
	{"sha224", "hash", hash_handler},
	{"sha512", "hash", hash_handler},
	{"sha384", "hash", hash_handler},
	{"sha512-224", "hash", hash_handler},
	{"sha512-256", "hash", hash_handler},
	{"base64", "cipher", base64},
	// {"des", "cipher", des_cbc},
	// {"des-ecb", "cipher", des_ecb},
	// {"des-cbc", "cipher", des_cbc},
	{NULL, NULL, NULL}
};

static t_ssl	*ssl_init()
{
	t_ssl	*ssl;

	if ((ssl = (t_ssl*)malloc(sizeof(t_ssl))) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	ssl->flags = 0;
	return (ssl);
}

static void	input_handler(char *alg)
{
	int				i;
	const t_handler	*handler;

	handler = NULL;
	i = -1;
	while (g_handlers[++i].name)
	{
		if (ft_strcmp(g_handlers[i].name, alg) == 0)
		{
			handler = &(g_handlers[i]);
			break ;
		}
	}
	if (!handler)
		ft_fatal_error(ft_strjoin(alg, " Not supported!"), 1);
	g_ssl->handler = handler;
}

static void	read_args(int ac, char **av)
{
	if (ft_strcmp(g_ssl->handler->type, "hash") == 0)
		read_hash_args(ac, av);
	else if (ft_strcmp(g_ssl->handler->type, "cipher") == 0)
		read_cipher_args(ac, av);
	else
	{
		ft_fatal_error("Not supported!", 0);
	}
}

int			main(int ac, char **av)
{
	if (ac < 2)
	{
		usage();
	}
	g_ssl = ssl_init();
	input_handler(av[1]);
	read_args(ac, av);
	g_ssl->handler->process(g_ssl);
	ft_clean();
	return (0);
}
