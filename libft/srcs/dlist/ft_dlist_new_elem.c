/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_new_elem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 13:05:53 by anorjen           #+#    #+#             */
/*   Updated: 2020/10/14 19:02:25 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

t_dlist	*ft_dlist_new_elem(void *content, size_t content_size, char save_ptrs)
{
	t_dlist	*res;

	if (save_ptrs)
	{
		res = ft_memalloc(sizeof(t_dlist));
		if (res)
		{
			if (content)
			{
				res->content = content;
				res->content_size = content_size;
			}
			else
			{
				res->content = NULL;
				res->content_size = 0;
			}
			res->next = NULL;
			res->prev = NULL;
		}
	}
	else
		res = ft_dlist_new(content, content_size);
	return (res);
}
