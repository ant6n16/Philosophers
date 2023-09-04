/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antdelga <antdelga@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 21:22:22 by antdelga          #+#    #+#             */
/*   Updated: 2023/09/04 19:27:24 by antdelga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h> 

typedef struct table
{
	int				num_p;
	int				msg_die;
	int				msg_eat;
	int				msg_sleep;
	int				n_must_eat;
	long			now;
	short int		advance;
	short int		finish;
	pthread_mutex_t	speak;
	pthread_mutex_t	advance_mtx;
	pthread_t		starvation;
}				t_table;

typedef struct philo
{
	int					philo_dni;
	int					num_eats;
	int					when_last_eat;
	pthread_t			thread;
	pthread_mutex_t		fork_r;
	pthread_mutex_t		*fork_l;
	pthread_mutex_t		mutex_eat;
	t_table				*table;
}				t_ph;

/* CHECK INPUT AND CREATE VARIABLES*/
int	check_arg(int argc, char **argv);
int	create_table(int argc, char **argv, t_table *table);
int	create_philo(int index, t_table *table, t_ph *philos);

/* UTILS */
int	ft_atoi_philo(char *str);
int	get_time(void);

#endif