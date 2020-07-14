/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 16:46:08 by rwalder-          #+#    #+#             */
/*   Updated: 2020/02/03 15:14:38 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_lib.h"

int		vector_add(t_vector_lib *vector, TYPE elem)
{
	if (vector == NULL || vector->arr == NULL)
		return (0);
	(vector)->arr[vector->size++] = elem;
	if ((vector->size % STACK_STEP) == 0)
		return (vector_resize(vector, vector->size + STACK_STEP));
	return (1);
}
