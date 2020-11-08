/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 21:01:05 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/08 15:12:35 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "main.h"

static int	read_hash_flags(int ac, char **av)
{
	int		i;

	i = 1;
	while (++i < ac)
	{
		if (ft_strcmp(av[i], "-r") == 0)
			SET_FLAG(g_ssl->flags, FLAG_R);
		else if (ft_strcmp(av[i], "-p") == 0)
			SET_FLAG(g_ssl->flags, FLAG_P);
		else if (ft_strcmp(av[i], "-q") == 0)
			SET_FLAG(g_ssl->flags, FLAG_Q);
		else if (ft_strcmp(av[i], "-s") == 0)
		{
			SET_FLAG(g_ssl->flags, FLAG_S);
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

void		read_hash_args(int ac, char **av)
{
	int		i;
	t_dlist	*datalist;

	datalist = NULL;
	i = read_hash_flags(ac, av);
	if ((i == ac && !IS_FLAG(g_ssl->flags, FLAG_S))
				|| IS_FLAG(g_ssl->flags, FLAG_P))
		ft_dlist_addback(&datalist, ft_dlist_new_elem(
			new_data("stdin", (t_input)IN_STDIN), sizeof(t_data), 1));
	if (IS_FLAG(g_ssl->flags, FLAG_S) && i < ac)
	{
		ft_dlist_addback(&datalist, ft_dlist_new_elem(
			new_data(av[i], (t_input)IN_STRING), sizeof(t_data), 1));
		++i;
	}
	else if (IS_FLAG(g_ssl->flags, FLAG_S) && i == ac)
		ft_fatal_error("String not found!", 0);
	i -= 1;
	while (++i < ac)
		ft_dlist_addback(&datalist, ft_dlist_new_elem(
			new_data(av[i], (t_input)IN_FILE), sizeof(t_data), 1));
	g_ssl->datalist = datalist;
}
