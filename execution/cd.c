/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 10:39:07 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/01 16:29:01 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_handle_dir(t_quotes *c, t_exec *head, char *pwd, int flag)
{
	char	*new_pwd;
	char	*str;

	if (access(head->cmd[1], X_OK) != 0)
	{
		print_error(head->cmd[1], 3, c->free_nodes);
		ft_exit_status(1, 1);
		return (1);
	}
	new_pwd = formated_pwd(pwd, head->cmd[1], c->free_nodes);
	if (head->nodes_num == 1)
		chdir(head->cmd[1]);
	str = getcwd(NULL, 0);
	if (!str)
		ft_putstr_fd("cd: error retrieving current directory\n", 2, 0);
	free(str);
	if (head->nodes_num == 1)
		cd_helper(head, pwd, new_pwd, c->free_nodes);
	ft_exit_status(0, 1);
	if (flag)
		free(pwd);
	return (1);
}

void	cd_with_path_helper(t_exec *head, t_quotes *c, int flag, char *pwd)
{
	print_error(head->cmd[1], 2, c->free_nodes);
	ft_exit_status(1, 1);
	if (flag)
		free(pwd);
}

static int	cd_with_path(t_quotes *c, t_exec *head, char *pwd, int flag)
{
	struct stat	st;

	if (stat(head->cmd[1], &st) != 0)
		return (cd_with_path_helper(head, c, flag, pwd), 1);
	if (S_ISREG(st.st_mode))
	{
		if (flag)
			free(pwd);
		return (cd_handle_file(head->cmd[1], c->free_nodes));
	}
	if (S_ISDIR(st.st_mode))
	{
		if (ft_strcmp(head->cmd[1], ".") == 0)
		{
			if (flag)
				free(pwd);
			ft_exit_status(0, 1);
			return (1);
		}
		return (cd_handle_dir(c, head, pwd, flag));
	}
	if (flag)
		free(pwd);
	return (1);
}

int	pwd_checker(t_quotes *c, char **pwd, int *flag)
{
	*pwd = my_getenv(c, "PWD");
	if (!*pwd)
	{
		*flag = 1;
		*pwd = getcwd(NULL, 0);
	}
	if (!*pwd)
	{
		ft_putstr_fd("cd: error retrieving current directory\n", 2, 0);
		return (chdir("/"), ft_exit_status(0, 1), 1);
	}
	return (0);
}

int	handle_cd(t_exec *node, t_free **free_nodes)
{
	t_quotes	c;
	char		*pwd;
	int			flag;

	1 && (flag = 0, c.free_nodes = free_nodes, c.node = node);
	if (!node->cmd[0] || ft_strcmp(node->cmd[0], "cd") != 0)
		return (0);
	if (pwd_checker(&c, &pwd, &flag))
		return (1);
	if (node->len_cmds == 1)
		return (cd_no_args(&c, node, pwd, flag));
	if (node->len_cmds > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2, 0);
		ft_exit_status(1, 1);
	}
	else
		return (cd_with_path(&c, node, pwd, flag));
	if (flag)
		free(pwd);
	return (1);
}
