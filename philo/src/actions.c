/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:41:59 by admin             #+#    #+#             */
/*   Updated: 2026/06/14 18:41:16 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grab_right_fork(t_philo *philo)
{
	long	timestamp;

	if (pthread_mutex_lock(&(philo->right_fork)))
	{
		printf("%s\n", "Error: pthread_mutex_lock failed for right fork");
		return (1);
	}
	timestamp = log_timestamp(philo);
	if (timestamp == -1)
		return (1);
	printf("%ld ms: philo %d has taken a fork\n", timestamp, philo->id);
	return (0);
}

int	grab_left_fork(t_philo *philo)
{
	long	timestamp;

	if (pthread_mutex_lock(&(philo->left_fork)))
	{
		printf("%s\n", "Error: pthread_mutex_lock failed for left fork");
		return (1);
	}
	timestamp = log_timestamp(philo);
	if (timestamp == -1)
		return (1);
	printf("%ld ms: philo %d has taken a fork\n", timestamp, philo->id);
	return (0);		
}

int	release_right_fork(t_philo *philo)
{
	if (pthread_mutex_unlock(&(philo->right_fork)))
	{
		printf("%s\n", "Error: pthread_mutex_unlock failed for right fork");
		return (1);
	}
	return (0);
}

int	release_left_fork(t_philo *philo)
{
	if (pthread_mutex_unlock(&(philo->left_fork)))
	{
		printf("%s\n", "Error: pthread_mutex_unlock failed for left fork");
		return (1);
	}
	return (0);		
}

int	eat(t_philo *philo)
{
	long	timestamp;

	philo->time_last_meal = log_timestamp(philo);
	if (philo->time_last_meal == -1)
		return (1);
	printf("%ld ms: philo %d is eating\n", timestamp, philo->id);
	if (usleep(philo->time_to_eat))
	{
		printf("%s\n", "Error: usleep failed for eating");
		return (1);
	}
	return (0);
}

int	philo_sleep_and_think(t_philo *philo)
{
	long	timestamp;

	timestamp = log_timestamp(philo);
	if (timestamp == -1)
		return (1);
	printf("%ld ms: philo %d is sleeping\n", timestamp, philo->id);
	if (usleep(philo->time_to_sleep))
	{
		printf("%s\n", "Error: usleep failed for sleeping");
		return (1);
	}
	timestamp = log_timestamp(philo);
	if (timestamp == -1)
		return (1);
	printf("%ld ms: philo %d is thinking\n", timestamp, philo->id);
	return (0);
}
