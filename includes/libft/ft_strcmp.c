/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidaparicio <davidaparicio@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 19:49:07 by jverdu-r          #+#    #+#             */
/*   Updated: 2023/12/08 04:25:52 by davidaparic      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	a;
	int	res;

	a = 0;
	if (!s1)
	{
		return (0);
	}
	while (s1[a] != 0 && s2[a] != 0 && s1[a] == s2[a])
	{
		a++;
	}
	res = s1[a] - s2[a];
	return (res);
}
