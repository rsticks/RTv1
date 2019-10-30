/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daron <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 10:19:13 by daron             #+#    #+#             */
/*   Updated: 2019/09/09 12:27:45 by daron            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (len > len + 1)
		return (NULL);
	if (!(ptr = ft_memalloc(len + 1)))
		return (NULL);
	if (!s || !ptr)
		return (NULL);
	ptr = ft_strncpy(ptr, (char*)(s + start), len);
	return (ptr);
}
