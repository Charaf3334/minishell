/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 09:43:36 by zguellou          #+#    #+#             */
/*   Updated: 2025/04/12 09:50:23 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *s1, t_free **free_nodes)
{
	size_t	len;
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	str = ft_malloc((len + 1), free_nodes);
	i = 0;
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

char	*ft_strdup_normal(const char *s1)
{
	size_t	len;
	char	*str;
	size_t	i;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	str = malloc((len + 1));
	i = 0;
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}
