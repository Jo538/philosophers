/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:06:19 by admin             #+#    #+#             */
/*   Updated: 2026/06/15 22:02:24 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = 10 * num + ((char)str[i] - '0');
		i++;
	}
	return (sign * num);
}

void	convert_to_int(char **argv, t_global *global)
{
	global->number_of_philosphers = ft_atoi(argv[1]);
	global->time_to_die = ft_atoi(argv[2]);
	global->time_to_eat = ft_atoi(argv[3]);
	global->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		global->number_of_times_must_eat = ft_atoi(argv[5]);
	else
		global->number_of_times_must_eat = -1;
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
	long			timestamp;
	long			end_in_ms;
	
	if (gettimeofday(&end, NULL))
		return (error("Error: gettimeofday failed", -1));
	end_in_ms = end.tv_sec * 1000 + end.tv_usec / 1000;
	timestamp = end_in_ms - global->start_simulation;
	return (timestamp);
}

int	clean_setup(t_param *param)
{
	t_philo		*philo;
	t_global	*global;

	philo = &param->philo;
	global = &param->global;
	
	if (pthread_join(philo->philo, NULL))
		return (error("Error: pthread_join failed", 1));
	if (pthread_join(global->monitor, NULL))
		return (error("Error: pthread_join failed", 1));
	if (pthread_mutex_destroy(&(philo->right_fork)))
		return (error("Error: pthread_mutex_destroy failed for right fork", 1));
	if (pthread_mutex_destroy(&(philo->left_fork)))
		return (error("Error: pthread_mutex_destroy failed for right fork", 1));
	if (pthread_mutex_destroy(&(global->lock)))
		return (error( "Error: pthread_mutex_destroy failed for lock", 1));
	if (pthread_mutex_destroy(&(global->lock2)))
		return (error("Error: pthread_mutex_destroy failed for lock", 1));
	return (0);
}
