/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 01:17:18 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/30 13:19:17 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
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

/*
** Main struct
**	Program's args
**		-n_philo: Number of philosophers and forks
**		-time_to_die: Number of ms they can go without food before dying
**		-time_to_eat: Number of ms they takes to eat
**		-time_to_sleep: Number of ms they takes to sleep
**		-eat_number: Number of times all philosophers have to eat for the program to end (optional)
**
**	Program's internal parameters
**		-on: State of simulation, if turn 0, simulation stop
**		-start: Timestamp of the beginning of the program
**		-printer: Mutex which control messages's prints
**		-forks: Array of pointers to forks, every fork is a mutex
*/
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

/*
** Philosophers' structure
**	-id: Philosopher's identifier
**	-meals: Number of times the philosopher ate
**	-timestamp: Timestamp od the last time the philosopher ate
** 	-thread: Pointer to philosopher's thread
** 	-timelock: Mutex which control access to philosopher's timestamp
**	-p: Pointer to program's main struct
*/
typedef struct s_philosopher {
	int				id;
	int				meals;
	struct timeval	timestamp;
	pthread_t		*thread;
	pthread_mutex_t	timelock;
	t_params		*p;
}	t_philosoper;


/*
** parser.c
*/
int			parser(const int argc, const char **argv, t_params *params);

/*
** simulation.c
*/
int			init_simulation(t_params *params);
void		printer(t_philosoper *philo, const char *s);

/*
** simulation_aux.c
*/
int			choose_fork(t_philosoper *philo, const int n);
void		free_philosophers(t_philosoper **array, t_params *params);
void		eat(t_philosoper *philo);
int			check_meals(t_params *params, t_philosoper **philos,
				pthread_mutex_t *print, int n);
int			dead(t_params *params, t_philosoper **philos,
				pthread_mutex_t *print, int n);

/*
** aux.c
*/
int			put_error(const char *str);
long int	get_timeval(struct timeval t1, struct timeval t2);
void		my_usleep(t_params *p, long int ms);
int			ft_strcmp(const char *s1, const char *s2);

#endif
