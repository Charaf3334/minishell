/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:08:03 by ctoujana          #+#    #+#             */
/*   Updated: 2025/05/14 11:52:06 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char const *set, t_free **free_nodes)
{
	int		start;
	int		end;
	size_t	len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup("", free_nodes));
	len = ft_strlen(s1);
	start = 0;
	while (s1[start] && check(s1[start], set))
		start++;
	end = len - 1;
	while (end >= start && check(s1[end], set))
		end--;
	if (start > end)
		return (ft_strdup("", free_nodes));
	return (ft_substr(s1, start, end - start + 1, free_nodes));
}
