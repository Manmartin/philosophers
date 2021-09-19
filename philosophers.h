/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 01:17:18 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/19 15:22:56 by manmarti         ###   ########.fr       */
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

typedef struct s_params {
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_number;

	pthread_mutex_t	*printer;
}	t_params;

typedef struct s_philosopher {
	int				id_philo;
	pthread_t		*thread;
	t_params		*p;
}	t_philosoper;

void	put_error(const char *str);

void	parser(const int argc, const char **argv, t_params *params);

void	init_simulation(t_params *params);

#endif