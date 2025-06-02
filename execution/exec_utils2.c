/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:48:09 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/10 17:19:36 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_error(char *str, int mode, t_free **free_nodes)
{
	char	*mess;

	mess = NULL;
	if (mode == 1)
		mess = ": command not found\n";
	else if (mode == 2)
		mess = ": No such file or directory\n";
	else if (mode == 3)
		mess = ": Permission denied\n";
	else if (mode == 4)
		mess = ": Is a directory\n";
	else if (mode == 5)
		mess = ": numeric argument required\n";
	else if (mode == 6)
		mess = ": not a valid identifier\n";
	else if (mode == 7)
		mess = ": Not a directory\n";
	else if (mode == 8)
		mess = ": ambiguous redirect\n";
	else if (mode == 9)
	{
		perror(str);
		return ;
	}
	ft_putstr_fd(ft_strjoin(str, mess, free_nodes), 2, 0);
}

t_env_ll	*create_new_env(void)
{
	t_env_ll	*new_env;

	new_env = malloc(sizeof(t_env_ll));
	new_env->key = NULL;
	new_env->value = NULL;
	new_env->next = NULL;
	return (new_env);
}

char	*check_valid_path(char **paths, char **args, t_free **free_nodes)
{
	int		i;
	char	*path;
	char	*exec;

	if (ft_strchr(args[0], '/') != NULL)
	{
		if (access(args[0], F_OK | X_OK) == 0)
			return (ft_strdup(args[0], free_nodes));
		return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/", free_nodes);
		exec = ft_strjoin(path, args[0], free_nodes);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		i++;
	}
	return (NULL);
}

char	*extract_path(char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] == "PATH"[j] && env[i][j] && "PATH"[j])
			j++;
		if (env[i][j] == '=' && j == 4)
			return (&env[i][5]);
		i++;
	}
	return (NULL);
}
