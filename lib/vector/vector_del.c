/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 17:28:48 by rwalder-          #+#    #+#             */
/*   Updated: 2019/05/10 13:26:26 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_lib.h"

int		vector_del(t_vector_lib *vector, unsigned int num)
{
	unsigned int i;

	if (vector == NULL || vector->arr == NULL ||
		num >= vector->size || vector->size == 0)
		return (0);
	i = num;
	while (i < vector->size - 1)
	{
		vector->arr[i] = vector->arr[i + 1];
		i++;
	}
	vector->arr[i] = NULL;
	vector->size--;
	if ((vector->size % STACK_STEP) == 0)
		return (vector_resize(vector, vector->size));
	return (1);
}
