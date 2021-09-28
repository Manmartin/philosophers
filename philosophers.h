/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 01:17:18 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/28 19:52:56 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

/*
** Error messages
*/
# define N_ERROR "Numeric error\n"
# define T_ERROR "Wrong arguments' type\n"
# define N_PHILOS_ERROR "Sorry, we dont have more than 200 forks\n"

/*
** Philosophers messages
*/
# define TFORK  "has taken a fork"
# define EAT	"is eating"
# define SLEEP  "is sleeping"
# define THINK  "is thinking"
# define DIE    "died"

# define NO_EAT -1

typedef struct s_params {
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_number;
	int				on;

	struct timeval	start;
	pthread_mutex_t	*printer;
	pthread_mutex_t	**forks;
}	t_params;

typedef struct s_philosopher {
	int				id;
	int				meals;
	struct timeval	timestamp;
	pthread_t		*thread;
	pthread_mutex_t	timelock;
	t_params		*p;
}	t_philosoper;

int			parser(const int argc, const char **argv, t_params *params);

int			init_simulation(t_params *params);
void		printer(t_philosoper *philo, const char *s);

int			choose_fork(t_philosoper *philo, const int n);
void		free_philosophers(t_philosoper **array, t_params *params);
void		eat(t_philosoper *philo);
int			check_meals(t_params *params, t_philosoper **philos,
				pthread_mutex_t *print, int n);
int			dead(t_params *params, t_philosoper **philos,
				pthread_mutex_t *print, int n);

int			put_error(const char *str);
long int	get_timeval(struct timeval t1, struct timeval t2);
void		my_usleep(t_params *p, long int ms);
int			ft_strcmp(const char *s1, const char *s2);

#endif
