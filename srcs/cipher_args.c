/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 21:03:35 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/08 17:35:38 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

const t_cipher_flag	g_flags[] = {
	{"-a", FLAG_A},
	{"-d", FLAG_D},
	{"-e", FLAG_E},
	{"-i", FLAG_I},
	{"-o", FLAG_O},
	{"-p", FLAG_P},
	{"-k", FLAG_K},
	{"-s", FLAG_S},
	{"-v", FLAG_V},
	{NULL, 0}
};

static int	save_option(int flag, char **av, int ac, int i)
{
	SET_FLAG(g_ssl->flags, flag);
	if (flag & (FLAG_I | FLAG_K | FLAG_O | FLAG_S | FLAG_V| FLAG_P))
	{
		if (!(i + 1 < ac))
			ft_fatal_error("Missed option value!", 0);
		if (flag == FLAG_I)
			g_ssl->input = av[++i];
		else if (flag == FLAG_K)
			g_ssl->key = av[++i];
		else if (flag == FLAG_O)
			g_ssl->output = av[++i];
		else if (flag == FLAG_P)
			g_ssl->password = av[++i];
		else if (flag == FLAG_S)
			g_ssl->salt = av[++i];
		else if (flag == FLAG_V)
			g_ssl->vector = av[++i];
	}
	return (i);
}

void		read_cipher_args(int ac, char **av)
{
	int	i;
	int	j;
	int	is_find;

	i = 1;
	while (++i < ac)
	{
		is_find = 0;
		j = -1;
		while (g_flags[++j].flag)
		{
			if (ft_strcmp(g_flags[j].flag, av[i]) == 0)
			{
				is_find = 1;
				i = save_option(g_flags[j].value, av, ac, i);
				break ;
			}
		}
		if (is_find == 0)
			ft_fatal_error(ft_strjoin("Unrecognized option ", av[i]), 1);
	}
}
