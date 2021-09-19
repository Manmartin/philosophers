/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 20:23:44 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/19 18:08:30 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	printer(t_philosoper	*philo, const char *s)
{
	pthread_mutex_lock(philo->p->printer);
	printf("%i %s\n", philo->id_philo, s);
	pthread_mutex_unlock(philo->p->printer);
}

static void	*life(void *args)
{
	t_philosoper	*philo;
	int				f1;
	int				f2;

	philo = (t_philosoper *)args;
	f1 = philo->id_philo - 2;
	if (f1 == -1)
		f1 = philo->p->n_philo - 1;
	f2 = philo->id_philo - 1;
	while (1)
	{
		if (philo->id_philo % 2 == 0)
			usleep(500);
		pthread_mutex_lock(philo->p->forks[f1]);
		printer(philo, "has taken a fork");
		pthread_mutex_lock(philo->p->forks[f2]);
		printer(philo, "is eating");
		usleep(philo->p->time_to_eat * 1000);
		pthread_mutex_unlock(philo->p->forks[f1]);
		pthread_mutex_unlock(philo->p->forks[f2]);
		printer(philo, "is sleeping");
		usleep(philo->p->time_to_sleep * 1000);
		printer(philo, "is thinking");
	}
	return (args);
}

static void	free_philosophers(t_philosoper **array, t_params *params)
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
	while (i < params->n_philo)
	{
		array[i]->id_philo = i + 1;
		array[i]->thread = malloc(sizeof(pthread_t *));
		array[i]->p = params;
		pthread_create(array[i]->thread, NULL, life, array[i]);
		i++;
	}
	return (array);
}

void	init_simulation(t_params *params)
{
	pthread_mutex_t	printer;
	t_philosoper	**philos;
	int				i;

	i = 0;
	pthread_mutex_init(&printer, NULL);
	params->printer = &printer;
	init_forks(params);
	philos = init_philosophers(params);
	while (i < params->n_philo)
	{
		pthread_join(*philos[i]->thread, NULL);
		i++;
	}
	free_philosophers(philos, params);
	pthread_mutex_destroy(&printer);
}
