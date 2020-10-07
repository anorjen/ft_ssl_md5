/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlist_addback.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgorczan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 21:51:23 by mgorczan          #+#    #+#             */
/*   Updated: 2019/10/27 21:51:23 by mgorczan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dlist.h"

void		ft_dlist_addback(t_dlist **alst, t_dlist *new)
{
	t_dlist	*first;

	if (alst == NULL || new == NULL)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	first = *alst;
	while ((*alst)->next)
		*alst = (*alst)->next;
	(*alst)->next = new;
	new->prev = *alst;
	*alst = first;
}
