/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 11:52:59 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 17:19:53 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**copy_env(char **src)
{
	int		i;
	int		len;
	char	**copy;

	len = 0;
	while (src[len])
		len++;
	copy = malloc((len + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (src[i])
	{
		copy[i] = ft_strdup_normal(src[i]);
		i++;
	}
	copy[len] = NULL;
	return (copy);
}

char	**extract_strs_env(char **env, t_free **free_nodes)
{
	char	*default_env[5];
	char	**env_strs;
	char	*cwd;
	char	*pwd_env;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		exit(1);
	}
	pwd_env = ft_strjoin("PWD=", cwd, free_nodes);
	free(cwd);
	default_env[0] = "OLDPWD";
	default_env[1] = pwd_env;
	default_env[2] = "SHLVL=1";
	default_env[3] = "_=/usr/bin/env";
	default_env[4] = NULL;
	if (env && *env)
		env_strs = copy_env(env);
	else
		env_strs = copy_env(default_env);
	return (env_strs);
}
