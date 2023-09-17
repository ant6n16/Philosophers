/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 19:09:43 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/17 15:11:24 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*one_philo(void *arg)
{
	t_ph	*p;

	p = (t_ph *) arg;	
	printf_think(p);
	pthread_mutex_lock(&p->table->advance_mtx);
	while (p->table->advance == 1)
	{
		pthread_mutex_unlock(&p->table->advance_mtx);
		// usleep(1);
		pthread_mutex_lock(&p->eat_mtx);
		if ((ft_get_time() - p[0].when_last_eat) > p->table->msg_die)
			printf_die(p);
		pthread_mutex_unlock(&p->eat_mtx);
	}
	pthread_mutex_unlock(&p->table->advance_mtx);
	pthread_exit(NULL);
}
