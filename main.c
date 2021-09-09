/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 01:15:33 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/09 19:40:48 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	parser(int argc, char **argv, t_params *params)
{
	params->number_of_philosophers = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->eat_number = -1;
	if (argc == 6)
		params->eat_number = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_params	params;

	if (argc < 5)
		put_error("Not enough arguments\n");
	else if (argc < 7)
		parser(argc, argv, &params);
	else
		put_error("To many arguments\n");
	return (0);
}
