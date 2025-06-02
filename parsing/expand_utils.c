/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:20:35 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/10 17:19:13 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_di(char c)
{
	if ((c >= '0' && c <= '9') || c == '_')
		return (1);
	return (0);
}

int	is_al(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	count_dollar(t_exec *node)
{
	int		i;
	int		count;
	char	*str;
	int		j;

	i = 0;
	count = 0;
	while (i < node->len_cmds)
	{
		j = 0;
		str = node->cmd[i];
		while (str[j])
		{
			if (str[j] == '$' && (is_al(str[j + 1]) || is_di(str[j + 1])))
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_charjoin(char *str, char c, t_free **free_nodes)
{
	int		i;
	char	*join;
	char	*joined;

	i = 0;
	if (!str)
	{
		join = ft_malloc(sizeof(char) * 2, free_nodes);
		join[0] = c;
		join[1] = '\0';
		return (join);
	}
	joined = ft_malloc(sizeof(char) * (ft_strlen(str) + 2), free_nodes);
	while (str[i])
	{
		joined[i] = str[i];
		i++;
	}
	joined[i++] = c;
	joined[i] = '\0';
	return (joined);
}
