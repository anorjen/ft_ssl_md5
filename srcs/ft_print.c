/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:07:52 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/07 22:15:21 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_common.h"

static void	ft_print_data_error(t_data *data)
{
	char	*message;
	char	*tmp;

	message = ft_strjoin(data->name, ": ");
	tmp = message;
	message = ft_strjoin(message, data->error);
	ft_error(message);
	free(tmp);
	free(message);
}

static void	ft_print_data_name(t_data *data)
{
	if (data->type == (t_input)IN_STRING)
	{
		write(1, "\"", 1);
		write(1, data->name, ft_strlen(data->name));
		write(1, "\"", 1);
	}
	else if (data->type == (t_input)IN_FILE)
	{
		write(1, data->name, ft_strlen(data->name));
	}
}

static void	ft_print_recursive(t_data *data)
{
	write(1, data->hash, ft_strlen(data->hash));
	write(1, " ", 1);
	ft_print_data_name(data);
}

static void	ft_print_right(t_data *data)
{
	if (data->type != (t_input)IN_STDIN)
	{
		ft_write_upper(1, g_ssl->handler->name, ft_strlen(g_ssl->handler->name));
		write(1, " (", 2);
		ft_print_data_name(data);
		write(1, ") = ", 4);
	}
	write(1, data->hash, ft_strlen(data->hash));
}

void		ft_print(t_dlist *datalist)
{
	t_data	*data;

	while (datalist)
	{
		data = (t_data*)datalist->content;
		if (data->state == 0)
		{
			if (IS_FLAG(g_ssl->flags, FLAG_Q))
				write(1, data->hash, ft_strlen(data->hash));
			else if (IS_FLAG(g_ssl->flags, FLAG_R))
				ft_print_recursive(data);
			else
				ft_print_right(data);
			write(1, "\n", 1);
		}
		else
			ft_print_data_error(data);
		datalist = datalist->next;
	}
}
