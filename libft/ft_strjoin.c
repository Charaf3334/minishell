/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:11:42 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/15 11:40:34 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *s1, char *s2, t_free **free_nodes)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2, free_nodes));
	else if (!s2)
		return (ft_strdup(s1, free_nodes));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = ft_malloc((s1_len + s2_len + 1), free_nodes);
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len);
	str[s1_len + s2_len] = '\0';
	return (str);
}

char	*ft_strjoin_normal(char *s1, char *s2, t_free **free_nodes)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (!s1 && !s2)
		return (ft_strdup_normal("", free_nodes));
	else if (!s1)
		return (ft_strdup_normal(s2, free_nodes));
	else if (!s2)
		return (ft_strdup_normal(s1, free_nodes));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc((s1_len + s2_len + 1));
	if (!str)
	{
		ft_putstr_fd("malloc failed!\n", 2, 0);
		cleanup_and_exit(free_nodes, 1);
	}
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len);
	str[s1_len + s2_len] = '\0';
	return (str);
}
