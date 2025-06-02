/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_libft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctoujana <ctoujana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:31:03 by ctoujana          #+#    #+#             */
/*   Updated: 2025/06/01 17:42:48 by ctoujana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	ft_count_words(char *str, char *c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_sep(str[i], c))
			i++;
		if (str[i] == '\0')
			break ;
		count++;
		while (str[i] && !is_sep(str[i], c))
			i++;
	}
	return (count);
}

static	char	*ft_word_maker(char *str, int *index, char *c)
{
	char	*word;
	int		i;
	int		len;
	int		j;

	i = *index;
	len = 0;
	j = 0;
	while (str[i] && is_sep(str[i], c))
		i++;
	while (str[i + len] && !is_sep(str[i + len], c))
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	while (j < len)
		word[j++] = str[i++];
	word[j] = '\0';
	*index = i;
	return (word);
}

static	void	free_split(char **split, int index)
{
	int	i;

	i = 0;
	while (i < index)
		free(split[i++]);
	free (split);
}

char	**ft_split_libft(char const *str, char *c)
{
	char	**split;
	int		i;
	int		index;
	int		len;

	if (str == NULL)
		return (NULL);
	i = 0;
	index = 0;
	len = ft_count_words((char *)str, c);
	split = malloc(sizeof(char *) * (len + 1));
	if (split == NULL)
		return (NULL);
	while (i < len)
	{
		split[i] = ft_word_maker((char *)str, &index, c);
		if (!split[i])
		{
			free_split(split, i);
			return (NULL);
		}
		i++;
	}
	split[i] = NULL;
	return (split);
}
