/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 20:23:44 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/09 20:43:42 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*function(void *args)
{
	t_params	*params;

	params = args;
	pthread_mutex_lock(params->printer);
	sleep(1);
	printf("I'm philosopher number %i\n", params->id_philo + 1);
	pthread_mutex_unlock(params->printer);
	return (params);
}

static void	free_philosophers(pthread_t	**philos, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		free(philos[i]);
		i++;
	}
	free(philos);
}

void	init_simulation(t_params *params)
{
	pthread_t		**array;
	pthread_mutex_t	printer;
	int				i;

	pthread_mutex_init(&printer, NULL);
	params->printer = &printer;
	i = 0;
	array = (t_philosoper **)malloc(sizeof(t_philosoper *) * params->n_philo));
	array = (pthread_t **)malloc(sizeof(pthread_t *) * params->n_philo);
	while (i < params->n_philo)
		array[i++] = (pthread_t *)malloc(sizeof(pthread_t *));
	i = 0;
	while (i < params->n_philo)
	{
		params->id_philo = i;
		pthread_create(array[i], NULL, function, params);
		i++;
	}
	i = 0;
	while (i < params->n_philo)
	{
		pthread_join(*array[i], NULL);
		i++;
	}
	free_philosophers(array, params->n_philo);
	pthread_mutex_destroy(&printer);
}
