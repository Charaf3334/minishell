/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:21:08 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 17:19:30 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	format_env_vars_helper(char *key, char **env_strs, int i,
		t_free **free_nodes)
{
	char	*eq;
	char	*value;
	char	*ptr;

	eq = ft_strchr(key, '=');
	*eq = '\0';
	value = eq + 1;
	env_strs[i] = ft_malloc((ft_strlen(key) + ft_strlen(value) + 4),
			free_nodes);
	ptr = env_strs[i];
	ft_memcpy(ptr, key, ft_strlen(key));
	ptr += ft_strlen(key);
	*ptr++ = '=';
	*ptr++ = '"';
	ft_memcpy(ptr, value, ft_strlen(value));
	ptr += ft_strlen(value);
	*ptr++ = '"';
	*ptr = '\0';
	*eq = '=';
}

void	sort_env_vars(char **env_vars, int arr_len)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < arr_len - 1)
	{
		j = 0;
		while (j < arr_len - i - 1)
		{
			if (ft_strcmp(env_vars[j], env_vars[j + 1]) > 0)
			{
				temp = env_vars[j];
				env_vars[j] = env_vars[j + 1];
				env_vars[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

char	**format_env_vars(char **env, t_free **free_nodes)
{
	int		count;
	char	**env_strs;
	int		i;
	char	*eq;

	count = 0;
	while (env[count])
		count++;
	env_strs = ft_malloc(sizeof(char *) * (count + 1), free_nodes);
	env_strs[count] = NULL;
	i = 0;
	while (i < count)
	{
		eq = ft_strchr(env[i], '=');
		if (!eq)
			env_strs[i] = ft_strdup(env[i], free_nodes);
		else
			format_env_vars_helper(env[i], env_strs, i, free_nodes);
		i++;
	}
	sort_env_vars(env_strs, count);
	return (env_strs);
}
