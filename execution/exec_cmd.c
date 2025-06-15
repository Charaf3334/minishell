/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:43:44 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/15 11:41:37 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**prepare_paths(t_exec *head, t_free **free_nodes, int *flag)
{
	char	*path_str;
	char	**paths;

	path_str = extract_path((*head->my_env)->env_strs);
	if (!path_str)
		path_str = (*head->my_env)->default_path[0];
	paths = ft_split_normal(path_str, ":", free_nodes);
	*flag = 0;
	if (!paths[0])
	{
		path_str = getcwd(NULL, 0);
		paths = ft_split_normal(path_str, "", free_nodes);
		free(path_str);
		*flag = 1;
	}
	return (paths);
}

static void	get_command_helper(char *cmd, t_exec *head, t_free **free_nodes)
{
	struct stat	st;

	if (!stat(cmd, &st))
	{
		if (S_ISDIR(st.st_mode))
		{
			print_error(cmd, 4, free_nodes);
			cleanup_and_exit(free_nodes, 126);
		}
		else if (S_ISREG(st.st_mode))
		{
			if (access(cmd, X_OK) != 0)
			{
				print_error(cmd, 3, free_nodes);
				cleanup_and_exit(free_nodes, 126);
			}
		}
	}
	else
	{
		not_a_dir(cmd, head, free_nodes);
		print_error(cmd, 2, free_nodes);
		cleanup_and_exit(free_nodes, 127);
	}
}

static char	*get_command_path(t_exec *head, char **paths, int flag,
		t_free **free_nodes)
{
	char	**args;
	char	*valid_path;

	args = head->cmd;
	valid_path = check_valid_path(paths, args, free_nodes);
	if (!valid_path)
	{
		if (access(args[0], F_OK) == 0 && args[0][0] == '.'
			&& args[0][1] == '/')
			valid_path = args[0];
		else
		{
			if (flag || check_dots_slash(args[0], 2))
				get_command_helper(args[0], head, free_nodes);
			else
			{
				print_error(args[0], 1, free_nodes);
				cleanup_and_exit(free_nodes, 127);
			}
			return (NULL);
		}
	}
	return (valid_path);
}

static void	exec_command(char *path, char **args, t_exec *head,
		t_free **free_nodes)
{
	struct stat	st;

	if (execve(path, args, (*head->my_env)->env_strs) == -1)
	{
		if (stat(path, &st) == 0)
		{
			if (S_ISREG(st.st_mode) && access(args[0], F_OK | X_OK) == 0)
				cleanup_and_exit(free_nodes, 0);
			if (S_ISREG(st.st_mode))
			{
				print_error(args[0], 3, free_nodes);
				cleanup_and_exit(free_nodes, 126);
			}
			else
			{
				print_error(args[0], 4, free_nodes);
				cleanup_and_exit(free_nodes, 126);
			}
		}
		else
		{
			print_error(args[0], 1, free_nodes);
			cleanup_and_exit(free_nodes, 127);
		}
	}
}

void	execute_cmd(t_exec *node, t_free **free_nodes)
{
	t_exec	*head;
	char	**paths;
	char	**args;
	char	*valid_path;
	int		flag;

	head = node;
	if (node->len_cmds == 0 || !head->cmd || !head->cmd[0])
		return ;
	args = head->cmd;
	if (handle_builtins(head, free_nodes))
		return ;
	if (check_dots_slash(args[0], 1) || !args[0][0])
	{
		print_error(args[0], 1, free_nodes);
		cleanup_and_exit(free_nodes, 127);
	}
	paths = prepare_paths(head, free_nodes, &flag);
	valid_path = get_command_path(head, paths, flag, free_nodes);
	if (!valid_path)
		return ;
	exec_command(valid_path, args, head, free_nodes);
}
