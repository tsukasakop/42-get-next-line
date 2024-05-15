/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkondo <tkondo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:36:07 by tkondo            #+#    #+#             */
/*   Updated: 2024/05/16 06:58:38 by tkondo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stddef.h>
#include <stdlib.h>

static void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*c_dst;
	const unsigned char	*c_src;
	char				sign;
	size_t				cur;

	c_src = (const unsigned char *)src;
	c_dst = (unsigned char *)dst;
	sign = (dst < src) * 2 - 1;
	cur = (sign == -1) * len;
	while (cur != (sign == 1) * len && (dst || src))
	{
		c_dst[cur - (sign == -1)] = c_src[cur - (sign == -1)];
		cur += sign;
	}
	return (dst);
}

size_t	ft_strlen(const char *s)
{
	const char	*t;

	t = s;
	while (*t)
		t++;
	return (t - s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	n_s1;
	size_t	n_s2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	n_s1 = ft_strlen(s1);
	n_s2 = ft_strlen(s2);
	if (n_s1 >= SIZE_MAX - n_s2 - 1)
		return (NULL);
	p = malloc(n_s1 + n_s2 + 1);
	if (p == NULL)
		return (NULL);
	ft_memmove(p, s1, n_s1);
	ft_memmove(p + n_s1, s2, n_s2);
	p[n_s1 + n_s2] = '\0';
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	n;
	char	*p;

	if (s == NULL)
		return (NULL);
	n = ft_strlen(s);
	if (start)
	{
		if (n > start)
			n = start;
		return (ft_substr(s + n, 0, len));
	}
	if (len < n)
		n = len;
	p = malloc(n + 1);
	if (p == NULL)
		return (NULL);
	ft_memmove(p, s, n);
	p[n] = '\0';
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	if (!((*s ^ c) & 255))
		return ((char *)s);
	if (*s)
		return (ft_strchr(s + 1, c));
	return (NULL);
}
