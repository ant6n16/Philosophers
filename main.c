/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:08:10 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/16 21:55:22 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_ph	*philos;

	if (check_arg(argc, argv) || create_table(argc, argv, &table))
		return (-1);
	philos = (t_ph *) malloc(sizeof(t_ph) * table.num_p);
	if (create_philo(&table, philos))
		return (-1);
	table.now = ft_get_time();
	if (table.num_p == 1)
	{
		if (pthread_create(&philos[0].thread, NULL, one_philo, &philos[0]))
			return (-1);
	}
	pthread_join(philos[0].thread, NULL);
	return (0);
}
