/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 16:08:04 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/08 17:25:34 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	get_data(t_ssl *ssl)
{
	t_data	*data;
	t_dlist	*datalist;

	datalist = NULL;
	if ((data = (t_data*)malloc(sizeof(data))) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	if (ssl->flags & FLAG_I)
	{
		ft_dlist_addback(&datalist, ft_dlist_new_elem(
			new_data(ssl->input, (t_input)IN_FILE), sizeof(t_data), 1));
	}
	else
	{
		ft_dlist_addback(&datalist, ft_dlist_new_elem(
			new_data("stdin", (t_input)IN_STDIN), sizeof(t_data), 1));
	}
	ssl->datalist = datalist;
}

void		base64(t_ssl *ssl)
{
	get_data(ssl);
	if (ssl->flags & FLAG_D)
		base64_decode(ssl);
	else if (ssl->flags & FLAG_E)
		base64_encode(ssl);
	else
	{
		ft_fatal_error("Wrong options!", 0);
	}
}
