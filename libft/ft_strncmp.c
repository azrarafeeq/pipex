/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafeeq <arafeeq@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 14:55:07 by arafeeq           #+#    #+#             */
/*   Updated: 2023/01/11 22:44:45 by arafeeq          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*st1;
	unsigned char	*st2;
	unsigned int	i;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	i = 0;
	if (s1[0] == '\0' && s2[0] == '\n' && n == 0)
		return (0);
	while (i < n - 1 && st1[i] != '\0' && st2[i] != '\0' && st1[i] == st2[i])
		i++;
	return (st1[i] - st2[i]);
}
