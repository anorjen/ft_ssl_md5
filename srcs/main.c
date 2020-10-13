/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:05:39 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/13 12:02:04 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

const t_hash	g_hashs[] = {
	{"md5", md5_calc, MD5_OUTPUT_SIZE, MD5_BLOCK_SIZE, MD5_OUTPUT_BLOCK_AMOUNT, NULL},
	{"sha256", sha256_calc, SHA256_OUTPUT_SIZE, SHA256_BLOCK_SIZE, SHA256_OUTPUT_BLOCK_AMOUNT, g_sha256_init},
	{"sha224", sha256_calc, SHA224_OUTPUT_SIZE, SHA256_BLOCK_SIZE, SHA224_OUTPUT_BLOCK_AMOUNT, g_sha224_init},
	{"sha512", sha512_calc, SHA512_OUTPUT_SIZE, SHA512_BLOCK_SIZE, SHA512_OUTPUT_BLOCK_AMOUNT, g_sha512_init},
	{"sha384", sha512_calc, SHA384_OUTPUT_SIZE, SHA512_BLOCK_SIZE, SHA384_OUTPUT_BLOCK_AMOUNT, g_sha384_init},
	{"sha512-224", sha512_calc, SHA512_224_OUTPUT_SIZE, SHA512_BLOCK_SIZE, SHA512_224_OUTPUT_BLOCK_AMOUNT, g_sha512_224_init},
	{"sha512-256", sha512_calc, SHA512_256_OUTPUT_SIZE, SHA512_BLOCK_SIZE, SHA512_256_OUTPUT_BLOCK_AMOUNT, g_sha512_256_init},
	{NULL, NULL, 0, 0, 0, NULL}
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
	g_ssl->hash_type = av[1];
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

static int	hash_calc(t_data *data, const t_hash *hash_handler)
{
	uint8_t	*hash;

	hash = hash_handler->t_function(data, hash_handler);
	if (hash == NULL)
		return (1);
	data->hash = hash_to_string(hash, hash_handler->output_size);
	free(hash);
	return (0);
}

static void	input_handler(void)
{
	int				i;
	t_dlist			*input;
	const t_hash	*hash_handler;

	hash_handler = NULL;
	i = -1;
	while (g_hashs[++i].name)
	{
		if (ft_strcmp(g_hashs[i].name, g_ssl->hash_type) == 0)
		{
			hash_handler = &(g_hashs[i]);
			break ;
		}
	}
	if (!hash_handler)
		ft_fatal_error("Hash type not supported!", 0);
	input = g_ssl->datalist;
	while (input)
	{
		hash_calc((t_data*)(input->content), hash_handler);
		input = input->next;
	}
}

int			main(int ac, char **av)
{
	if (ac < 2)
	{
		usage();
	}
	read_args(ac, av);
	input_handler();
	ft_print(g_ssl->datalist);
	ft_clean();
	return (0);
}
