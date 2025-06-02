/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:11:42 by zguellou          #+#    #+#             */
/*   Updated: 2025/04/23 13:21:05 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin3(char *s1, char *s2, char *s3, t_free **free_nodes)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;
	char	*str;

	1 && (s1_len = 0, s2_len = 0, s3_len = 0);
	if (s1)
		s1_len = ft_strlen(s1);
	if (s2)
		s2_len = ft_strlen(s2);
	if (s3)
		s3_len = ft_strlen(s3);
	if (s1_len == 0 && s2_len == 0 && s3_len == 0)
		return (NULL);
	str = ft_malloc((s1_len + s2_len + s3_len + 1), free_nodes);
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len);
	ft_memcpy(str + s1_len + s2_len, s3, s3_len);
	str[s1_len + s2_len + s3_len] = '\0';
	return (str);
}

char	*ft_strjoin3_normal(char *s1, char *s2, char *s3)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;
	char	*str;

	1 && (s1_len = 0, s2_len = 0, s3_len = 0);
	if (s1)
		s1_len = ft_strlen(s1);
	if (s2)
		s2_len = ft_strlen(s2);
	if (s3)
		s3_len = ft_strlen(s3);
	if (s1_len == 0 && s2_len == 0 && s3_len == 0)
		return (NULL);
	str = malloc(s1_len + s2_len + s3_len + 1);
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len);
	ft_memcpy(str + s1_len + s2_len, s3, s3_len);
	str[s1_len + s2_len + s3_len] = '\0';
	return (str);
}
