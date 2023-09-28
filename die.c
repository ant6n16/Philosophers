/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:17:49 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/27 20:30:59 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	someone_die(t_ph *p, int *flag)
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
		if (p->table->early_finish == 1 \
			&& p[index].num_eats < p->table->n_must_eat)
			*(flag) = 1;
		pthread_mutex_unlock(&p[index].eat_mtx);
	}
	return (0);
}

int	check_n_meals(t_ph *p)
{
	pthread_mutex_lock(&p->table->advance_mtx);
	p->table->advance = 0;
	pthread_mutex_unlock(&p->table->advance_mtx);
	pthread_mutex_lock(&p->table->print_mtx);
	printf("Everyone has eaten %d times\n", p->table->n_must_eat);
	pthread_mutex_unlock(&p->table->print_mtx);
	return (1);
}

void	*check_thread(void *param)
{
	t_ph	*p;
	int		flag;

	p = (t_ph *)param;
	pthread_mutex_lock(&p->table->advance_mtx);
	while (p->table->advance)
	{
		pthread_mutex_unlock(&p->table->advance_mtx);
		flag = 0;
		usleep(10);
		if (someone_die(p, &flag))
			return (NULL);
		if (p->table->early_finish && flag == 0)
			if (check_n_meals(p))
				return (NULL);
		pthread_mutex_lock(&p->table->advance_mtx);
	}
	pthread_mutex_unlock(&p->table->advance_mtx);
	return (NULL);
}
