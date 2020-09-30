/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_delone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:51:38 by mgorczan          #+#    #+#             */
/*   Updated: 2020/09/30 18:42:12 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlist_delone(t_dlist **lst, void (*del)(void *))
{
	t_dlist	*pv;
	t_dlist	*nx;

	pv = NULL;
	nx = NULL;
	if (lst && *lst)
	{
		nx = (*lst)->next;
		pv = (*lst)->prev;
		if ((*lst)->content)
			del((*lst)->content);
		free(*lst);
		*lst = nx;
		if (nx)
			nx->prev = pv;
		if (pv)
			pv->next = nx;
	}
}
