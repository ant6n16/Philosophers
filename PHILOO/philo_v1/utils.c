/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 19:47:36 by antdelga          #+#    #+#             */
/*   Updated: 2023/08/27 20:47:22 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
		ft_exit_error("Values ​must be in the range of int");
		return (-1);
	}
	return (number);
}

void	ft_exit_error(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		write (1, &s[i], 1);
}

int	get_actual_time(void)
{
	struct timeval	actual_time;

	gettimeofday(&actual_time, NULL);
	return ((actual_time.tv_sec * 1000) + (actual_time.tv_usec / 1000));
}
