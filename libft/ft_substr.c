/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:18:41 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/15 11:40:43 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_substr(char *s, unsigned int start, size_t len, t_free **free_nodes)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s || len <= 0)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup("", free_nodes));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = ft_malloc((sizeof(char) * (len + 1)), free_nodes);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_substr_normal(char *s, unsigned int start, size_t len,
	t_free **free_nodes)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s || len == 0)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup_normal("", free_nodes));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc((sizeof(char) * (len + 1)));
	if (!str)
	{
		ft_putstr_fd("malloc failed!\n", 2, 0);
		cleanup_and_exit(free_nodes, 1);
	}
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
