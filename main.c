/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:08:10 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/04 19:30:06 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_table	table;
	t_ph	philos;

	if (check_arg(argc, argv) || create_table(argc, argv, &table) || \
	create_philo(-1, &table, &philos))
		return (-1);
	return (0);
}
