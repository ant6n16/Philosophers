/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:09:43 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/16 22:13:01 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_philo(void *arg)
{
	t_ph	*p;
	int		timer;

	timer = ft_get_time();
	printf("%d\n", timer);
	p = (t_ph *) arg;
	printf_think(p);
	pthread_mutex_lock(&p->table->advance_mtx);
	while (p->table->advance == 1)
	{
		pthread_mutex_unlock(&p->table->advance_mtx);
		usleep(1);
		pthread_mutex_lock(&p->table->advance_mtx);
		// printf("%d\n", ft_get_time());
		// printf("%d\n", p->table->msg_die);
		if (ft_get_time() > p->table->msg_die)
		{
			pthread_mutex_lock(&p->table->advance_mtx);
			p->table->advance = 0;
			pthread_mutex_unlock(&p->table->advance_mtx);
			pthread_mutex_lock(&p->table->speak);
			printf("%d %d is dead\n", ft_get_time(), p->philo_dni);
			pthread_mutex_unlock(&p->table->speak);
		}
	}
	pthread_mutex_unlock(&p->table->advance_mtx);
	pthread_exit(NULL);
}
