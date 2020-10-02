/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:05:39 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/02 18:24:05 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

const t_hash	g_hashs[2] = {
	{"md5", ft_md5},
	{NULL, NULL}
};

static int		read_flags(int ac, char **av)
{
	int	i;

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
			g_ssl->s_flag = 1;
		else
			return (i);
	}
	return (i);
}

static void		read_args(int ac, char **av)
{
	int		i;
	t_dlist	*datalist;

	datalist = NULL;
	if ((g_ssl = (t_ssl*)malloc(sizeof(t_ssl))) == NULL)
		ft_fatal_error("Malloc ERROR!");
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
		ft_fatal_error("String not found!");
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
		ft_fatal_error("Hash type not supported!");
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
		usage();
	read_args(ac, av);
	input_handler();
	ft_print(g_ssl->datalist);
	ft_clean();
	return (0);
}
