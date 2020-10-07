/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:51:51 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:51:52 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

size_t		ft_dlist_size(t_dlist *lst)
{
	size_t	size;

	while (lst->prev != NULL)
		lst = lst->prev;
	size = 0;
	while (lst)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}
