/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 20:55:52 by antdelga          #+#    #+#             */
/*   Updated: 2023/08/27 19:29:22 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table		table;
	t_threads	thread[300];
	int			i;

	if (check_input(argc, argv, &table, thread))
		return (1);
	i = -1;
	table.actual_time = get_actual_time();
	if (table.num_phil == 1)
		if (pthread_create(&thread[0].thr, NULL, one_philo, &thread[0]))
			return (ft_exit_error("Problems when creating mutex\n"), 1);
	if (table.num_phil != 1)
		while (++i < table.num_phil)
			if (pthread_create(&thread[i].thr, NULL, mto_philo, &thread[i]))
				return (ft_exit_error("Problems when creating mutex\n"), 1);
	if (pthread_create(&table.starvation, NULL, check_thread, thread))
		return (ft_exit_error("Error creating mutex\n"), 1);
	close_and_clean(thread);
	return (0);
}
