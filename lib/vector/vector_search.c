/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 16:00:28 by rwalder-          #+#    #+#             */
/*   Updated: 2019/05/10 13:26:26 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_lib.h"

long	vector_search(t_vector_lib *vector, TYPE elem, unsigned int begin,
		unsigned int end)
{
	unsigned int i;

	if (vector == NULL || vector->arr == NULL || begin >= vector->size
		|| end > vector->size || begin >= end)
		return (-1);
	i = begin;
	while (i < end)
	{
		if (vector->arr[i] == elem)
			return (i);
		i++;
	}
	return (-1);
}
