/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:59:19 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/28 16:33:36 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	put_error(const char *str)
{
	write(2, str, ft_strlen(str));
	return (0);
}

long int	get_timeval(struct timeval t1, struct timeval t2)
{
	return ((t1.tv_sec * 1000 + t1.tv_usec / 1000)
		- (t2.tv_sec * 1000 + t2.tv_usec / 1000));
}

void	my_usleep(t_params *p, long int ms)
{
	struct timeval	init;
	struct timeval	current;

	gettimeofday(&init, NULL);
	gettimeofday(&current, NULL);
	while (p->on && get_timeval(current, init) < ms)
	{
		usleep(50);
		gettimeofday(&current, NULL);
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
