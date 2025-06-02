/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:45:46 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/10 17:20:07 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	wspc(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_sep(str[i], " \t\n\v\f\r"))
		i++;
	return (i);
}

long	ft_atol(char *str)
{
	t_atol	vars;

	vars.result = 0;
	vars.sign = 1;
	vars.max = (unsigned long long)(LONG_MAX / 10);
	1 && (vars.limit = (unsigned int)(LONG_MAX % 10), vars.i = wspc(str));
	if (str[vars.i] == '-' || str[vars.i] == '+')
	{
		if (str[vars.i] == '-')
			vars.sign = -1;
		vars.i++;
	}
	while (str[vars.i] && str[vars.i] >= '0' && str[vars.i] <= '9')
	{
		if (vars.result > vars.max || (vars.result == vars.max
				&& (unsigned int)(str[vars.i] - '0') > vars.limit))
		{
			if (vars.sign == 1)
				return (LONG_MAX);
			return (LONG_MIN);
		}
		vars.result = vars.result * 10 + (str[vars.i++] - '0');
	}
	return ((long)(vars.result * vars.sign));
}
