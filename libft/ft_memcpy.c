/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:19:51 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 17:20:12 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	if (dst == src)
		return (dst);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return ((char *)d);
}

char	*ft_join_strs(char **strs, t_free **free_nodes)
{
	t_join_strs	vars;

	1 && (vars.i = 0, vars.total_len = 0);
	if (!strs || !strs[0])
		return (ft_strdup("", free_nodes));
	while (strs[vars.i])
		vars.total_len += ft_strlen(strs[vars.i++]) + 1;
	vars.count = vars.i;
	vars.result = ft_malloc(vars.total_len + 1, free_nodes);
	vars.ptr = vars.result;
	vars.i = 0;
	while (vars.i < vars.count)
	{
		vars.s = strs[vars.i];
		while (*vars.s)
			*vars.ptr++ = *vars.s++;
		if (vars.i != vars.count - 1)
			*vars.ptr++ = ' ';
		vars.i++;
	}
	*vars.ptr = '\0';
	return (vars.result);
}
