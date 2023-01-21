/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:33:27 by arafeeq           #+#    #+#             */
/*   Updated: 2023/01/12 14:05:53 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
	{
		return (ft_strdup(""));
	}
	else
		i = ft_strlen(s) - start;
	if (i > len)
		i = len;
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[start] != '\0' && i < len)
	{
		str[i] = s[start++];
		i++;
	}
	str[i] = '\0';
	return (str);
}
