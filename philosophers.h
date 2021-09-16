/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 01:17:18 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/16 18:09:14 by manmarti         ###   ########.fr       */
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

typedef struct s_philosopher {
	pthread_t		*thread;
	pthread_mutex_t	*printer;
	int				id_philo;
}	t_philosoper;

typedef struct s_params {
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_number;

	t_philosoper	**philos;
}	t_params;

int		ft_atoi(const char *str);
void	put_error(const char *str);

void	init_simulation(t_params *params);

#endif