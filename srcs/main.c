/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:05:39 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/06 18:43:28 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

const t_hash	g_hashs[3] = {
	{"md5", md5},
	{"sha256", sha256},
	{NULL, NULL}
};

static int		read_flags(int ac, char **av)
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

static void		read_args(int ac, char **av)
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

static void		input_handler(void)
{
	int			i;
	t_function	func;
	t_dlist		*input;

	func = NULL;
	i = -1;
	while (g_hashs[++i].name)
	{
		if (ft_strcmp(g_hashs[i].name, g_ssl->hash_type) == 0)
		{
			func = g_hashs[i].function;
			break ;
		}
	}
	if (!func)
		ft_fatal_error("Hash type not supported!", 0);
	input = g_ssl->datalist;
	while (input)
	{
		(func)((t_data*)(input->content));
		input = input->next;
	}
}

int				main(int ac, char **av)
{
	if (ac < 2)
	{
		printf("%d\n", l_to_b_endian(1));
		// printf("%d\n", rotate_right(1, 24));
		usage();
	}
	read_args(ac, av);
	input_handler();
	ft_print(g_ssl->datalist);
	ft_clean();
	return (0);
}