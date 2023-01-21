/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:51:52 by arafeeq           #+#    #+#             */
/*   Updated: 2023/01/09 15:39:44 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		slen;
	char	*ptr;

	c = c % 256;
	slen = ft_strlen(s);
	ptr = (char *)s;
	if (!s)
		return (NULL);
	while (slen >= 0)
	{
		if (ptr[slen] == c)
		{
			ptr = ptr + slen;
			return (ptr);
		}
		slen--;
	}
	return (NULL);
}
