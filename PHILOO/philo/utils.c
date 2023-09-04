/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 00:19:42 by antdelga          #+#    #+#             */
/*   Updated: 2023/08/26 15:30:42 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_actual_time(void)
{
	struct timeval	actual_time;

	gettimeofday(&actual_time, NULL);
	return ((actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000));
}

/* Retorna -1 cuando hay un error, 0 si todo OK*/
int	ft_atoi(char *str)
{
	long	number;
	int		i;

	number = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		number = (number * 10) + (str[i++] - '0');
	if (number > INT_MAX)
	{
		ft_exit_error("Values ​​must be in the range of int");
		return (-1);
	}
	return (number);
}

/* Retorna -1 cuando hay un error, 0 si todo OK*/
void	ft_exit_error(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		write (1, &s[i], 1);
}

void	ft_usleep(int ms, t_threads *thread)
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
