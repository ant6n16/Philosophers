/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:55:06 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/04 19:27:16 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi_philo(char *str)
{
	long	number;
	int		i;

	number = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		number = (number * 10) + (str[i] - '0');
		i++;
	}
	if (number > INT_MAX)
		return (printf("Only INT range values allowed\n"), -1);
	return (number);
}

int	get_time(void)
{
	struct timeval	actual_time;

	gettimeofday(&actual_time, NULL);
	return ((actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000));
}
