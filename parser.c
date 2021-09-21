/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 19:24:18 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/21 16:43:24 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static const char	*recursive_parser(const char *s)
{
	while (((*s >= 9 && *s <= 13) || *s == 32 ) && *s)
		s++;
	if (*s == '+' || *s == '-')
	{
		s++;
		if (*s < '0' || *s > '9')
			return (0);
	}
	if (*s && *s >= '0' && *s <= '9')
		while (*s && *s >= '0' && *s <= '9')
			s++;
	else
		return (0);
	if (*s && !((*s >= 9 && *s <= 13) || *s == 32 ))
		return (0);
	return (s);
}

static int	n_parser(const char *s)
{
	int	n;

	n = 0;
	while (*s)
	{
		s = recursive_parser(s);
		if (!s)
			return (-1);
		n++;
	}
	return (n);
}

static int	parser_atoi(const char *str)
{
	long double	sign;
	long double	number;

	number = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while (*str >= 48 && *str <= 57)
		number = number * 10 + (*str++ - '0');
	if (number * sign > INT_MAX)
		return (-1);
	if (number * sign < INT_MIN)
		return (-1);
	return (number * sign);
}

static int	check_values(const t_params p)
{
	if (p.n_philo <= 0 || p.time_to_die <= 0
		|| p.time_to_eat <= 0 || p.time_to_sleep <= 0)
		return (put_error(N_ERROR));
	if (p.n_philo > 200)
		return (put_error(N_PHILOS_ERROR));
	if (p.n_philo == 1)
		printf(EVIL_ERROR);
	return (1);
}

int	parser(const int argc, const char **argv, t_params *params)
{
	int	n;

	n = 1;
	while (n < argc)
	{
		if (n_parser(argv[n]) != 1)
			return (put_error(T_ERROR));
		n++;
	}
	params->n_philo = parser_atoi(argv[1]);
	params->time_to_die = parser_atoi(argv[2]);
	params->time_to_eat = parser_atoi(argv[3]);
	params->time_to_sleep = parser_atoi(argv[4]);
	params->eat_number = -1;
	if (argc == 6)
	{
		params->eat_number = parser_atoi(argv[5]);
		if (params->eat_number <= 0)
			return (put_error(N_ERROR));
	}
	if (!check_values(*params))
		return (0);
	return (1);
}
