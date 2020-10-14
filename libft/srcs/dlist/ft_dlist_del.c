/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_del.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anorjen <anorjen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:51:33 by mgorczan          #+#    #+#             */
/*   Updated: 2020/10/14 19:01:10 by anorjen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void	ft_dlist_del(t_dlist **dlst, void (*del)(void *))
{
	t_dlist	*tmp;

	*dlst = ft_dlist_rewind(*dlst);
	while (*dlst)
	{
		tmp = (*dlst)->next;
		del((*dlst)->content);
		free(*dlst);
		*dlst = tmp;
	}
	*dlst = NULL;
}
