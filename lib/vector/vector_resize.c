/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_resize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rwalder- <rwalder-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 22:21:28 by rwalder-          #+#    #+#             */
/*   Updated: 2019/05/10 13:26:26 by rwalder-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector_lib.h"

static void	*cpy(void *dst, const void *src, size_t n)
{
	size_t				count;
	unsigned char		*p1;
	const unsigned char	*p2 = src;

	count = 0;
	p1 = dst;
	while (count < n)
	{
		p1[count] = p2[count];
		count++;
	}
	return (dst);
}

int			vector_resize(t_vector_lib *vector, unsigned int new_size)
{
	TYPE *temp;

	if (vector == NULL || vector->arr == NULL)
		return (0);
	if (vector->size == new_size)
		return (1);
	if ((temp = (TYPE*)malloc(sizeof(TYPE) * new_size)) == NULL)
		return (0);
	cpy(temp, vector->arr, sizeof(TYPE) * ((new_size > vector->size) ?
	(vector->size) : (new_size)));
	free(vector->arr);
	vector->arr = NULL;
	vector->arr = temp;
	return (1);
}
