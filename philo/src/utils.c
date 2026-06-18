/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:06:19 by admin             #+#    #+#             */
/*   Updated: 2026/06/18 14:27:42 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	long	num;
	int		i;

	num = 0;
	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		if (num > INT_MAX)
			return (-1);
		i++;
	}
	return (num);
}

void	convert_to_int(char **argv, t_global **global)
{
	(*global)->number_of_philosphers = (int)ft_atoi(argv[1]);
	(*global)->time_to_die = ft_atoi(argv[2]);
	(*global)->time_to_eat = ft_atoi(argv[3]);
	(*global)->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		(*global)->number_of_times_must_eat = (int)ft_atoi(argv[5]);
	else
		(*global)->number_of_times_must_eat = -1;
}

int	log_start_time(t_global *global)
{
	struct timeval	start;

	if (gettimeofday(&start, NULL))
		return (1);
	global->start_simulation = start.tv_sec * 1000 + start.tv_usec / 1000;
	return (0);
}

long	log_timestamp(t_global *global)
{
	struct timeval	end;
	long			end_in_ms;

	if (gettimeofday(&end, NULL))
		return (error("Error: gettimeofday", -1));
	end_in_ms = end.tv_sec * 1000 + end.tv_usec / 1000;
	return (end_in_ms - global->start_simulation);
}

void	print_status(t_philo *philo, char *msg)
{
	t_global	*g;
	int			dead;
	long		ts;

	g = philo->global;
	pthread_mutex_lock(&g->lock_print);
	pthread_mutex_lock(&g->lock_is_dead);
	dead = g->is_dead;
	pthread_mutex_unlock(&g->lock_is_dead);
	if (!dead)
	{
		ts = log_timestamp(g);
		printf("%ld %d %s\n", ts, philo->id, msg);
	}
	pthread_mutex_unlock(&g->lock_print);
}
