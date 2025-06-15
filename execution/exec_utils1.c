/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:29:20 by zguellou          #+#    #+#             */
/*   Updated: 2025/06/15 11:45:52 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dots_slash(const char *str, int mode)
{
	if (mode == 1)
	{
		if (ft_strchr(str, '.') && !ft_strchr(str, '/'))
			return (1);
	}
	else if (mode == 2)
	{
		if (ft_strchr(str, '/'))
			return (1);
	}
	return (0);
}

void	ft_dup2(int old_fd, int new_fd, t_env **my_env, t_free **free_nodes)
{
	(void)my_env;
	if (dup2(old_fd, new_fd) == -1)
	{
		perror("dup2");
		cleanup_and_exit(free_nodes, 1);
	}
	close(old_fd);
}

void	open_infile(t_exec *node, t_free **free_nodes)
{
	t_exec	*head;
	int		i;
	int		fd_input;

	head = node;
	if (!head->infiles || head->len_infiles == 0)
		return ;
	i = 0;
	while (head->infiles[i])
	{
		fd_input = open(head->infiles[i++], O_RDONLY);
		if (fd_input == -1)
		{
			perror(head->infiles[i]);
			ft_exit_status(1, 1);
			return ;
		}
		ft_dup2(fd_input, STDIN_FILENO, node->my_env, free_nodes);
	}
}

int	open_outfile(t_exec *node, t_free **free_nodes)
{
	t_exec	*head;
	t_files	*files;
	int		fd_out;

	head = node;
	if (!head->outfiles || head->len_outfiles == 0)
		return (1);
	files = head->files;
	while (files)
	{
		if (!files->type)
		{
			files = files->next;
			continue ;
		}
		fd_out = fd_return(files);
		if (fd_out == -1)
			return (perror(files->file_name), ft_exit_status(1, 1), 1);
		ft_dup2(fd_out, STDOUT_FILENO, node->my_env, free_nodes);
		files = files->next;
	}
	return (0);
}

void	cleanup_and_exit(t_free **free_nodes, int status)
{
	int	fd;

	if (free_nodes)
	{
		if (*free_nodes)
		{
			if ((*free_nodes)->my_env)
				free_env((*free_nodes)->my_env);
			ft_lstclear(free_nodes);
		}
	}
	ft_exit_status(status, 1);
	fd = 3;
	while (fd < 1024)
		close(fd++);
	exit(status);
}
