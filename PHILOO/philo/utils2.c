/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:14:23 by antdelga          #+#    #+#             */
/*   Updated: 2023/08/27 19:33:59 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_test(int i, t_threads *thread, int *flag)
{
	int		tmp;

	while (++i < thread->table->num_phil)
	{
		pthread_mutex_lock(&thread[i].mutex_eat);
		pthread_mutex_lock(&thread->table->stop_mutex);
		tmp = get_actual_time() - thread[i].last_meal;
		if (tmp > thread[i].table->mseg_die)
		{
			thread->table->stop = 0;
			pthread_mutex_unlock(&thread->table->stop_mutex);
			pthread_mutex_unlock(&thread[i].mutex_eat);
			pthread_mutex_lock(&thread->table->talk);
			printf("%ld %d died\n", get_actual_time() - \
			thread->table->actual_time, thread[i].id);
			pthread_mutex_unlock(&thread->table->talk);
			return (0);
		}
		pthread_mutex_unlock(&thread->table->stop_mutex);
		if (thread->table->ends == 1 && thread[i].n_meals < \
		thread->table->num_must_eat)
			*(flag) = 1;
		pthread_mutex_unlock(&thread[i].mutex_eat);
	}
	return (1);
}

int	food_test(t_threads *thread, int flag)
{
	if (thread->table->ends == 1 && flag == 0)
	{
		pthread_mutex_lock(&thread->table->stop_mutex);
		thread->table->stop = 0;
		pthread_mutex_unlock(&thread->table->stop_mutex);
		pthread_mutex_lock(&thread->table->talk);
		pthread_mutex_unlock(&thread->table->talk);
		return (0);
	}
	return (1);
}

void	close_and_clean(t_threads *thread)
{
	int	i;

	i = -1;
	while (++i < thread->table->num_phil)
		pthread_join(thread[i].thr, NULL);
	printf("Aqui\n");
	pthread_join(thread->table->starvation, NULL);
	i = -1;
	while (++i < thread->table->num_phil)
	{
		pthread_mutex_destroy(&thread[i].right_fork);
		pthread_mutex_destroy(&thread[i].mutex_eat);
	}
	pthread_mutex_destroy(&thread->table->talk);
	pthread_mutex_destroy(&thread->table->stop_mutex);
}
