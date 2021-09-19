/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 01:15:33 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/19 20:11:09 by manmarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
void	test(void)
{
	system("leaks philo");
}
*/

int	main(const int argc, const char **argv)
{
	t_params	params;

	//atexit(test);
	if (argc < 5)
		put_error("Not enough arguments\n");
	else if (argc < 7)
	{
		parser(argc, argv, &params);
		init_simulation(&params);
	}
	else
		put_error("To many arguments\n");
	return (0);
}
