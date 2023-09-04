/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:04:38 by antdelga          #+#    #+#             */
/*   Updated: 2023/08/27 21:16:34 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	show_action(char *str, t_th *thread)
{
	int	status;

	pthread_mutex_lock(&thread->table->talk);
	status = get_actual_time() - thread->table->actual_time;
	pthread_mutex_lock(&thread->table->stop_mutex);
	if (thread->table->stop == 1)
		printf("%d %d %s\n", status, thread->id, str);
	pthread_mutex_unlock(&thread->table->stop_mutex);
	pthread_mutex_unlock(&thread->table->talk);
}

void	ft_usleep(int ms, t_th *thread)
{
	int	tmp;

	tmp = get_actual_time();
	pthread_mutex_lock(&thread->table->stop_mutex);
	while ((get_actual_time() - tmp < ms) && thread->table->stop)
	{
		pthread_mutex_unlock(&thread->table->stop_mutex);
		usleep(10);
		pthread_mutex_lock(&thread->table->stop_mutex);
	}
	pthread_mutex_unlock(&thread->table->stop_mutex);
}

int	death_test(int i, t_th *thread, int *flag)
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

int	food_test(t_th *thread, int flag)
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
