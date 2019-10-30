/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddfront.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 12:05:03 by daron             #+#    #+#             */
/*   Updated: 2019/09/09 12:13:57 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lst_pushback(t_list **alst, t_list *new)
{
	t_list	*current;

	if (!alst || !new)
		return ;
	current = *alst;
	if (!current)
		*alst = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}
