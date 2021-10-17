/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 16:33:13 by manmarti          #+#    #+#             */
/*   Updated: 2021/10/10 17:45:51 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_one(t_philosopher *philo)
{
	if (philo->p->n_philo == 1)
	{
		pthread_mutex_lock(philo->p->forks[0]);
		printer(philo, TFORK);
		my_usleep(philo->p, philo->p->time_to_eat);
		pthread_mutex_unlock(philo->p->forks[0]);
		return (1);
	}
	return (0);
}

int	choose_fork(t_philosopher *philo, const int n)
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

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->timelock);
	philo->meals += 1;
	printer(philo, EAT);
	gettimeofday(&philo->timestamp, NULL);
	pthread_mutex_unlock(&philo->timelock);
	my_usleep(philo->p, philo->p->time_to_eat);
}

int	check_meals(t_params *params, t_philosopher **philos,
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

int	dead(t_params *p, t_philosopher **philos, pthread_mutex_t *print, int n)
{
	int	i;

	p->on = 0;
	printer(philos[n], DIE);
	pthread_mutex_unlock(&philos[n]->timelock);
	i = 0;
	while (i < p->n_philo)
		pthread_join(*philos[i++]->thread, NULL);
	free_philosophers(philos, p);
	pthread_mutex_destroy(print);
	return (0);
}
