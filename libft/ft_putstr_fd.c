/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sreinhol <sreinhol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 18:31:29 by sreinhol          #+#    #+#             */
/*   Updated: 2021/07/18 18:45:06 by sreinhol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	c;

	c = 0;
	if (!s)
		return ;
	while (s[c])
	{
		ft_putchar_fd(s[c], fd);
		c++;
	}
}