/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manmarti <manmarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 01:15:33 by manmarti          #+#    #+#             */
/*   Updated: 2021/09/21 10:38:46 by manmarti         ###   ########.fr       */
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
		if (!parser(argc, argv, &params))
			return (0);
		init_simulation(&params);
	}
	else
		put_error("To many arguments\n");
	return (0);
}
