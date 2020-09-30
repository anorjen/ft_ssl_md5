/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:05:39 by anorjen           #+#    #+#             */
/*   Updated: 2020/09/30 18:58:19 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	read_flags(int ac, char	*av)
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

void	read_args(int ac, char	*av)
{
	int		i;
	t_list	*datalist;

	datalist = NULL;
	g_ssl->hash_type = av[1];
	i = read_flags(ac, av);
	if (i == ac || g_ssl->p_flag)
		ft_dlist_addback(datalist, new_data("stdin", STDIN));
	if (g_ssl->s_flag && i < ac)
	{
		ft_dlist_addback(datalist, new_data(av[i], STRING));
		++i;
	}
	else
		ft_error("String not found!");
	i -= 1;
	while (++i < ac)
		ft_dlist_addback(datalist, new_data(av[i], FILE));
	g_ssl->datalist = datalist;
}

void	input_handler(void)
{
	int			i;
	t_function	*func;
	t_dlist		*input;

	func = NULL;
	i = -1;
	while (g_hashs[++i].name)
	{
		if (ft_strcmp(g_hashs[i].name, g_ssl->hash_type))
		{
			func = &(g_hashs[i].function);
			break ;
		}
	}
	if (!func)
		ft_error("Hash type not supported!");
	input = g_ssl->datalist;
	while (input)
	{
		(*func)(input);
		input = input->next;
	}
}

int		main(int ac, char **av)
{
	if (ac < 2)
		usage();
	read_args(ac, av);
	input_handler();
	printer(g_ssl->datalist);
	ft_clean();
	return (0);
}
