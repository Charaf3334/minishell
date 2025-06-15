/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:19:38 by ctoujana          #+#    #+#             */
/*   Updated: 2025/06/14 16:16:00 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_execution(char *line, t_free **free_nodes, t_env **my_env)
{
	t_vals	v;
	t_exec	*head;
	t_exec	*current;

	head = NULL;
	current = NULL;
	vals_init(&v, line, free_nodes);
	v.my_env = my_env;
	process_loop(&v, &head, &current, free_nodes);
	execution(head, v.nodes_num, free_nodes);
}

int	process_line(char **line, t_free **free_nodes)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strtrim(*line, " \t\n\v\f\r", free_nodes);
	if (!(*line) || !ft_strlen(*line))
	{
		free(tmp);
		ft_exit_status(0, 0);
		return (1);
	}
	free(tmp);
	if (check_syntax(*line))
		return (1);
	return (0);
}

void	free_env(t_env **my_env)
{
	int				i;
	t_env_ll		*prec;

	i = 0;
	while ((*my_env)->env_strs[i])
		free((*my_env)->env_strs[i++]);
	free((*my_env)->env_strs);
	while ((*my_env)->env_ll)
	{
		prec = (*my_env)->env_ll;
		free((*my_env)->env_ll->key);
		free((*my_env)->env_ll->value);
		(*my_env)->env_ll = (*my_env)->env_ll->next;
		free(prec);
	}
	i = 0;
	while ((*my_env)->default_path[i])
		free((*my_env)->default_path[i++]);
	free((*my_env)->default_path);
	free((*my_env));
}

void	env_and_1byte_alloc(t_env **my_env, t_free **free_nodes)
{
	if (!*free_nodes)
		ft_malloc2(1, my_env, free_nodes);
	(*free_nodes)->my_env = my_env;
}

void	close_all_fds(void)
{
	int	i;

	i = 3;
	while (i < 1024)
		close(i++);
}
