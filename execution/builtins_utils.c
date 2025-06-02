/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:36:58 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 17:19:20 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_option(t_exec *head)
{
	int		i;
	int		j;
	int		flag;
	char	*s;

	1 && (i = 1, flag = 0);
	while (head->cmd[i])
	{
		s = head->cmd[i];
		if (s[0] == '-' && s[1] == 'n')
		{
			j = 2;
			while (s[j] == 'n')
				j++;
			if (s[j] == '\0')
			{
				1 && (flag = 1, i++);
				continue ;
			}
		}
		break ;
	}
	if (flag)
		return (i);
	return (-i);
}
