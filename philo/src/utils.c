/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:06:19 by admin             #+#    #+#             */
/*   Updated: 2026/06/14 18:57:36 by admin            ###   ########.fr       */
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

void	convert_to_int(char **argv, t_philo *philo)
{
	philo->number_of_philosphers = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->repeat = ft_atoi(argv[5]);
}

int	log_start_time(t_philo *philo)
{
	struct timeval	start;

	if (gettimeofday(&start, NULL))
		return (1);
	philo->start_simulation = start.tv_sec * 1000 + start.tv_usec / 1000;
	return (0);
}

long	log_timestamp(t_philo *philo)
{
	struct timeval	end;
	long			timestamp;
	long			end_in_ms;
	
	if (gettimeofday(&end, NULL))
	{
		printf("%s\n", "Error: gettimeofday failed");
		return (-1);		
	}
	end_in_ms = end.tv_sec * 1000 + end.tv_usec / 1000;
	timestamp = end_in_ms - philo->start_simulation;
	return (timestamp);
}

int	clean_setup(t_philo *philo)
{
	if (pthread_join(philo->philo, NULL))
	{
		printf("%s\n", "Error: pthread_join failed");
		return (1);
	}	
	if (pthread_join(philo->monitor, NULL))
	{
		printf("%s\n", "Error: pthread_join failed");
		return (1);
	}	
	if (pthread_mutex_destroy(&(philo->right_fork)))
	{
		printf("%s\n", "Error: pthread_mutex_destroy failed for right fork");
		return (1);
	}	
	if (pthread_mutex_destroy(&(philo->left_fork)))
	{
		printf("%s\n", "Error: pthread_mutex_destroy failed for right fork");
		return (1);
	}
	return (0);
}
