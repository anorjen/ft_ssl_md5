/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 18:51:09 by anorjen           #+#    #+#             */
/*   Updated: 2020/09/30 18:51:54 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_data	*new_data(char *name, int type)
{
	t_data	*data;

	data = (t_data*)malloc(sizeof(t_data));
	if (data)
	{
		data->name = name;
		data->type = type;
		data->block = NULL;
		data->hash = NULL;
	}
	return (data);
}

void	del_data(t_data *data)
{
	if (!data)
		return ;
	if (data->block)
		free(data->block);
	if (data->hash)
		free(data->hash);
	free(data);
}
