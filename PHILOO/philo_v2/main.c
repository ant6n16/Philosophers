/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:36:19 by antdelga          #+#    #+#             */
/*   Updated: 2023/08/27 21:41:04 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int narg, char **argv)
{
	t_data			data;
	t_philos		philo[242];
	int				i;

	if (check_args(narg, argv))
		return (1);
	if (check_input(narg, argv, &data, philo) != 0)
		return (1);
	i = -1;
	data.time_start = timer();
	if (data.n_philos == 1)
		if (pthread_create(&philo[0].thread, NULL, exception, &philo[0]))
			return (ft_exit_error("MSG\n"), 1);
	if (data.n_philos != 1)
		while (++i < data.n_philos)
			if (pthread_create(&philo[i].thread, NULL, philo_thread, &philo[i]))
				return (ft_exit_error("MSG\n"), 1);
	if (pthread_create(&data.starvation, NULL, check_thread, philo))
		return (ft_exit_error("MSG\n"), 1);
	close_and_clean(philo);
	return (0);
}
