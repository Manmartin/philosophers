/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:59:19 by manmarti          #+#    #+#             */
/*   Updated: 2021/10/10 14:22:00 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philosophers(t_philosopher **array, t_params *params)
{
	int	i;

	i = 0;
	while (i < params->n_philo)
	{
		free(array[i]->thread);
		free(array[i]);
		pthread_mutex_destroy(params->forks[i]);
		free(params->forks[i]);
		i++;
	}
	free(params->forks);
	free(array);
}

int	put_error(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
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
