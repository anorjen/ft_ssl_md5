/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:51:09 by anorjen           #+#    #+#             */
/*   Updated: 2020/11/24 12:58:16 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"

t_ssl	*init_ssl(void)
{
	t_ssl	*ssl;

	if ((ssl = (t_ssl*)malloc(sizeof(t_ssl))) == NULL)
		return (NULL);
	ssl->datalist = NULL;
	ssl->hash_type = NULL;
	ssl->p_flag = 0;
	ssl->q_flag = 0;
	ssl->r_flag = 0;
	ssl->s_flag = 0;
	return (ssl);
}

t_data	*new_data(char *name, int type)
{
	t_data	*data;

	if ((data = (t_data*)malloc(sizeof(t_data))) == NULL)
		ft_fatal_error("Malloc ERROR!", 0);
	if (data)
	{
		data->name = name;
		data->type = type;
		data->error = NULL;
		data->state = 0;
		data->length = 0;
		data->fd = -1;
		data->hash = NULL;
	}
	return (data);
}

void	del_data(void *data)
{
	t_data	*d;

	if (!data)
		return ;
	d = (t_data*)data;
	if (d->hash)
		free(d->hash);
	free(d);
}
