/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qraymaek <qraymaek@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:24:23 by qraymaek          #+#    #+#             */
/*   Updated: 2023/11/21 20:05:04 by qraymaek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/libft.h"
#include <stddef.h>
#include <stdlib.h>

static int	count_words(char const *s, char c)
{
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static void	ft_free_tab(char **tab)
{
	char	**pos;

	if (tab == NULL)
		return ;
	pos = tab;
	while (*pos != NULL)
		free(*(pos++));
	free(tab);
}

static char	*ft_str(char const *s, char c)
{
	int		i;
	char	*ptr;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (!(ptr))
	{
		free(ptr);
		return (NULL);
	}
	ft_strlcpy(ptr, s, i + 1);
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		strs_len;
	char	**ptr;

	if (!s)
		return (0);
	strs_len = count_words(s, c);
	ptr = ft_calloc(sizeof(char *), (strs_len + 1));
	if (!(ptr))
		return (NULL);
	i = -1;
	while (++i < strs_len)
	{
		while (s[0] == c)
			s++;
		ptr[i] = ft_str(s, c);
		if (!(ptr[i]))
		{
			ft_free_tab(ptr);
			return (NULL);
		}
		s += ft_strlen(ptr[i]);
	}
	ptr[i] = 0;
	return (ptr);
}
