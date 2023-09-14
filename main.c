/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:08:10 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/14 19:57:15 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_ph	philos;

	if (check_arg(argc, argv) || create_table(argc, argv, &table) || \
	create_philo(&table, &philos))
		return (-1);
	table.now = ft_get_time();
	if (table.num_p == 1)
	{
		if (pthread_create(&philos->thread, NULL, one_philo, &(philos)))
		{
			printf("Aqui\n");
			return (-1);
		}
		if (pthread_create(&table.starvation, NULL, \
			check_one_philo_die, &(philos)))
			return (-1);
	}
	return (0);
}
