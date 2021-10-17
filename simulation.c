/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 20:23:44 by manmarti          #+#    #+#             */
/*   Updated: 2021/10/10 14:22:37 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	printer(t_philosopher *philo, const char *s)
{
	struct timeval	time;

	pthread_mutex_lock(philo->p->printer);
	gettimeofday(&time, NULL);
	if (philo->p->on || !ft_strcmp(DIE, s))
		printf("%li %i %s\n", get_timeval(time, philo->p->start),
			philo->id, s);
	pthread_mutex_unlock(philo->p->printer);
}

static void	*life(void *args)
{
	t_philosopher	*philo;
	int				f1;
	int				f2;

	philo = (t_philosopher *)args;
	if (is_one(philo))
		return (args);
	f1 = choose_fork(philo, 1);
	f2 = choose_fork(philo, 2);
	if (philo->id % 2 == 0)
		usleep(250);
	while (philo->p->on)
	{
		pthread_mutex_lock(philo->p->forks[f1]);
		printer(philo, TFORK);
		pthread_mutex_lock(philo->p->forks[f2]);
		printer(philo, TFORK);
		eat(philo);
		printer(philo, SLEEP);
		pthread_mutex_unlock(philo->p->forks[f1]);
		pthread_mutex_unlock(philo->p->forks[f2]);
		my_usleep(philo->p, philo->p->time_to_sleep);
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

static t_philosopher	**init_philosophers(t_params *params)
{
	t_philosopher	**array;
	int				i;

	i = 0;
	array = (t_philosopher **)malloc(sizeof(t_philosopher *) * params->n_philo);
	while (i < params->n_philo)
		array[i++] = (t_philosopher *)malloc(sizeof(t_philosopher));
	i = 0;
	gettimeofday(&params->start, NULL);
	while (i < params->n_philo)
	{
		array[i]->id = i + 1;
		array[i]->meals = 0;
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
	t_philosopher	**philos;
	struct timeval	time;
	int				i;

	pthread_mutex_init(&print, NULL);
	params->printer = &print;
	params->on = 1;
	init_forks(params);
	philos = init_philosophers(params);
	while (1)
	{
		i = 0;
		while (i < params->n_philo)
		{
			pthread_mutex_lock(&philos[i]->timelock);
			gettimeofday(&time, NULL);
			if (get_timeval(time, philos[i]->timestamp) >= params->time_to_die)
				return (dead(params, philos, &print, i));
			if (check_meals(params, philos, &print, i))
				return (0);
			pthread_mutex_unlock(&philos[i++]->timelock);
		}
	}
	return (0);
}
