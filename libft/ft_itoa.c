/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:51:21 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/10 17:20:09 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	getlength(int n)
{
	int	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static char	*convert(char *str, int len, int n)
{
	int	isnegative;

	isnegative = 0;
	if (n < 0)
		isnegative = 1;
	str[len--] = '\0';
	if (isnegative)
		n = -n;
	while (len >= 0)
	{
		str[len--] = (n % 10) + '0';
		n /= 10;
	}
	if (isnegative)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n, t_free **free_nodes)
{
	char	*str;
	int		len;

	len = getlength(n);
	str = ft_malloc(sizeof(char) * (len + 1), free_nodes);
	str = convert(str, len, n);
	return (str);
}
