/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:47:13 by antdelga          #+#    #+#             */
/*   Updated: 2023/08/27 21:15:06 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_th	threads[300];
	int		i;

	if (check_args(argc, argv))
		return (1);
	if (create_structs(argc, argv, &table, threads))
		return (1);
	table.actual_time = get_actual_time();
	i = -1;
	if (table.num_phil == 1)
		if (pthread_create(&threads[0].thr, NULL, one_philo, &threads[0]))
			return (ft_exit_error("Problems when creating the thread\n"), 1);
	if (table.num_phil != 1)
		while (++i < table.num_phil)
			if (pthread_create(&threads[i].thr, NULL, mto_philo, &threads[i]))
				return (ft_exit_error("Problems when creating threads\n"), 1);
	if (pthread_create(&table.starvation, NULL, check_thread, threads))
		return (ft_exit_error("Error creating mutex\n"), 1);
	return (0);
}
