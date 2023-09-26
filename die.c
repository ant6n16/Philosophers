/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:00:19 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/26 18:40:38 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	someone_die(t_ph *p)
{
	int	index;

	index = -1;
	while (++index < p->table->num_p)
	{
		pthread_mutex_lock(&p[index].eat_mtx);
		pthread_mutex_lock(&p->table->advance_mtx);
		if (ft_get_time() - p[index].when_last_eat > p[index].table->msg_die)
		{
			pthread_mutex_unlock(&p->table->advance_mtx);
			printf_die(p);
			pthread_mutex_lock(&p->table->advance_mtx);
			p->table->advance = 0;
			pthread_mutex_unlock(&p->table->advance_mtx);
			pthread_mutex_unlock(&p[index].eat_mtx);
			return (1);
		}
		pthread_mutex_unlock(&p->table->advance_mtx);
		pthread_mutex_unlock(&p[index].eat_mtx);
	}
	return (0);
}

int	check_n_meals(t_ph *p)
{
	int	index;
	int	cont;

	cont = 0;
	index = -1;
	while (++index < p->table->num_p)
	{
		pthread_mutex_lock(&p[index].eat_mtx);
		if (p[index].num_eats != p->table->n_must_eat)
			break ;
		else
			cont++;
	}
	if (cont == p->table->num_p)
	{
		pthread_mutex_lock(&p->table->advance_mtx);
		p->table->advance = 0;
		pthread_mutex_unlock(&p->table->advance_mtx);
		pthread_mutex_unlock(&p[index].eat_mtx);
		return (1);
	}
	pthread_mutex_unlock(&p[index].eat_mtx);
	return (0);
}

void	*check_thread(void *param)
{
	t_ph	*p;

	p = (t_ph *)param;
	pthread_mutex_lock(&p->table->advance_mtx);
	while (p->table->advance)
	{
		pthread_mutex_unlock(&p->table->advance_mtx);
		usleep(10);
		if (someone_die(p))
			return (NULL);
		if (p->table->early_finish)
			if (check_n_meals(p))
				return (NULL);
		pthread_mutex_lock(&p->table->advance_mtx);
	}
	pthread_mutex_unlock(&p->table->advance_mtx);
	return (NULL);
}
