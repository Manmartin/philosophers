/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 20:23:44 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/21 19:37:51 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	printer(t_philosoper *philo, const char *s)
{
	struct timeval	time;

	pthread_mutex_lock(philo->p->printer);
	gettimeofday(&time, NULL);
	printf("%li %i %s\n", get_timeval(time, philo->p->start),
		philo->id_philo, s);
	pthread_mutex_unlock(philo->p->printer);
}

static void	*life(void *args)
{
	t_philosoper	*philo;
	int				f1;
	int				f2;

	philo = (t_philosoper *)args;
	f1 = choose_fork(philo, 1);
	f2 = choose_fork(philo, 2);
	while (1)
	{
		pthread_mutex_lock(philo->p->forks[f1]);
		printer(philo, TFORK);
		pthread_mutex_lock(philo->p->forks[f2]);
		pthread_mutex_lock(&philo->timelock);
		printer(philo, EAT);
		gettimeofday(&philo->timestamp, NULL);
		pthread_mutex_unlock(&philo->timelock);
		my_usleep(philo->p->time_to_eat);
		pthread_mutex_unlock(philo->p->forks[f1]);
		pthread_mutex_unlock(philo->p->forks[f2]);
		printer(philo, SLEEP);
		my_usleep(philo->p->time_to_sleep);
		printer(philo, THINK);
	}
	return (args);
}

static void	init_forks(t_params *params)
{
	int	i;

	i = 0;
	params->forks = malloc(sizeof(pthread_mutex_t *) * params->n_philo);
	while (i < params->n_philo)
		params->forks[i++] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	i = 0;
	while (i < params->n_philo)
		pthread_mutex_init(params->forks[i++], NULL);
}

static t_philosoper	**init_philosophers(t_params *params)
{
	t_philosoper	**array;
	int				i;

	i = 0;
	array = (t_philosoper **)malloc(sizeof(t_philosoper *) * params->n_philo);
	while (i < params->n_philo)
		array[i++] = (t_philosoper *)malloc(sizeof(t_philosoper));
	i = 0;
	gettimeofday(&params->start, NULL);
	while (i < params->n_philo)
	{
		array[i]->id_philo = i + 1;
		array[i]->thread = malloc(sizeof(pthread_t *));
		array[i]->p = params;
		array[i]->timestamp = params->start;
		pthread_mutex_init(&array[i]->timelock, NULL);
		pthread_create(array[i]->thread, NULL, life, array[i]);
		i++;
	}
	return (array);
}

int	init_simulation(t_params *params)
{
	pthread_mutex_t	print;
	t_philosoper	**philos;
	struct timeval	time;
	int				i;

	i = 0;
	pthread_mutex_init(&print, NULL);
	params->printer = &print;
	init_forks(params);
	philos = init_philosophers(params);
	while (1)
	{
		while (i < params->n_philo)
		{
			pthread_mutex_lock(&philos[i]->timelock);
			gettimeofday(&time, NULL);
			if (get_timeval(time, philos[i]->timestamp) >= params->time_to_die)
			{
				printer(philos[i], DIE);
				return (0);
				while (i < params->n_philo)
				{
					pthread_join(*philos[i]->thread, NULL);
					i++;
				}
				free_philosophers(philos, params);
				pthread_mutex_destroy(&print);
			}
			pthread_mutex_unlock(&philos[i]->timelock);
			i++;
		}
		i = 0;
	}
	return (0);
}
