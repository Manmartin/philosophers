/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:33:13 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/28 20:06:59 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	choose_fork(t_philosoper *philo, const int n)
{
	if (n == 1)
	{
		if (philo->id == 1)
			return (philo->p->n_philo - 1);
		return (philo->id - 2);
	}
	else
		return (philo->id - 1);
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

void	eat(t_philosoper *philo)
{
	pthread_mutex_lock(&philo->timelock);
	philo->meals += 1;
	printer(philo, EAT);
	gettimeofday(&philo->timestamp, NULL);
	pthread_mutex_unlock(&philo->timelock);
	my_usleep(philo->p, philo->p->time_to_eat);
}

int	check_meals(t_params *params, t_philosoper **philos,
	pthread_mutex_t *print, int n)
{
	int	i;

	i = 0;
	if (params->eat_number == NO_EAT)
		return (0);
	while (i < params->n_philo)
		if (philos[i++]->meals < params->eat_number)
			return (0);
	params->on = 0;
	pthread_mutex_unlock(&philos[n]->timelock);
	i = 0;
	while (i < params->n_philo)
		pthread_join(*philos[i++]->thread, NULL);
	free_philosophers(philos, params);
	pthread_mutex_destroy(print);
	return (1);
}

int	dead(t_params *params, t_philosoper **philos, pthread_mutex_t *print, int n)
{
	int	i;

	params->on = 0;
	printer(philos[n], DIE);
	pthread_mutex_unlock(&philos[n]->timelock);
	i = 0;
	while (i < params->n_philo)
		pthread_join(*philos[i++]->thread, NULL);
	free_philosophers(philos, params);
	pthread_mutex_destroy(print);
	return (0);
}
