/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 20:23:44 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/19 15:30:46 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*function(void *args)
{
	t_philosoper	*philo;

	philo = args;
	pthread_mutex_lock(philo->p->printer);
	printf("I'm philosopher number %i\n", philo->id_philo);
	pthread_mutex_unlock(philo->p->printer);
	return (philo);
}

static void	free_philosophers(t_philosoper **array, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		free(array[i]->thread);
		free(array[i]);
		i++;
	}
	free(array);
}

static t_philosoper
	**init_philosophers(t_params *params)
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
		pthread_create(array[i]->thread, NULL, function, array[i]);
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
	philos = init_philosophers(params);
	while (i < params->n_philo)
	{
		pthread_join(*philos[i]->thread, NULL);
		i++;
	}
	free_philosophers(philos, params->n_philo);
	pthread_mutex_destroy(&printer);
}
