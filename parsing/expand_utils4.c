/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zguellou <zguellou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 14:54:23 by zguellou          #+#    #+#             */
/*   Updated: 2025/05/11 16:32:51 by zguellou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_back_exp(t_list **my_lst, t_list *new)
{
	t_list	*last_node;

	if (!my_lst || !new)
		return ;
	if (!*my_lst)
		*my_lst = new;
	else
	{
		last_node = ft_lstlast_exp(*my_lst);
		last_node->next = new;
	}
}

int	ft_lstsize_exp(t_list *my_lst)
{
	t_list	*lst;
	int		len;

	len = 0;
	lst = my_lst;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

t_list	*ft_lstnew_exp(char *content, t_free **free_nodes)
{
	t_list	*lst;

	lst = ft_malloc(sizeof(t_list), free_nodes);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

int	is_quoted(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	if ((str[0] == '"' && str[len - 1] == '"')
		|| (str[0] == '\'' && str[len - 1] == '\''))
		return (1);
	return (0);
}

int	has_quote(char *str)
{
	size_t	len;
	int		i;

	if (!str)
		return (0);
	len = ft_strlen(str);
	if (len < 2)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
			return (1);
		i++;
	}
	return (0);
}
