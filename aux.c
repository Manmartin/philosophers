/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:59:19 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/21 19:44:30 by manmarti         ###   ########.fr       */
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

int	choose_fork(t_philosoper *philo, const int n)
{
	if (philo->id_philo % 2 == 1)
	{
		if (n == 1)
		{
			if (philo->id_philo == 1)
				return (philo->p->n_philo - 1);
			return (philo->id_philo - 2);
		}
		else
			return (philo->id_philo - 1);
	}
	else
	{
		if (n == 1)
			return (philo->id_philo - 1);
		else
			return (philo->id_philo - 2);
	}
}

long int	get_timeval(struct timeval t1, struct timeval t2)
{
	return ((t1.tv_sec * 1000 + t1.tv_usec / 1000)
		- (t2.tv_sec * 1000 + t2.tv_usec / 1000));
}

void	my_usleep(long int ms)
{
	struct timeval	init;
	struct timeval	current;

	gettimeofday(&init, NULL);
	gettimeofday(&current, NULL);
	while (get_timeval(current, init) < ms)
		gettimeofday(&current, NULL);
}

void	free_philosophers(t_philosoper **array, t_params *params)
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
