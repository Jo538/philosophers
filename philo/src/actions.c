/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:41:59 by admin             #+#    #+#             */
/*   Updated: 2026/06/10 16:06:37 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grab_right_fork(pthread_mutex_t *right_fork)
{
	if (pthread_mutex_lock(right_fork))
	{
		printf("%s\n", "Error: pthread_mutex_lock failed for right fork");
		return (1);
	}
	printf("%s\n", "Philo grabbed right fork");
	return (0);
}

int	grab_left_fork(pthread_mutex_t *left_fork)
{
	if (pthread_mutex_lock(left_fork))
	{
		printf("%s\n", "Error: pthread_mutex_lock failed for left fork");
		return (1);
	}
	printf("%s\n", "Philo grabbed left fork");
	return (0);		
}

int	release_right_fork(pthread_mutex_t *right_fork)
{
	if (pthread_mutex_unlock(right_fork))
	{
		printf("%s\n", "Error: pthread_mutex_unlock failed for right fork");
		return (1);
	}
	printf("%s\n", "Philo released right fork");
	return (0);
}

int	release_left_fork(pthread_mutex_t *left_fork)
{
	if (pthread_mutex_unlock(left_fork))
	{
		printf("%s\n", "Error: pthread_mutex_unlock failed for left fork");
		return (1);
	}
	printf("%s\n", "Philo released left fork");
	return (0);		
}

int	eat(void)
{
	if (usleep(1000))
	{
		printf("%s\n", "Error: usleep failed for eating");
		return (1);
	}
	printf("%s\n", "Philo geating");
	return (0);
}

int	philo_sleep(void)
{
	if (usleep(1000))
	{
		printf("%s\n", "Error: usleep failed for sleeping");
		return (1);
	}
	printf("%s\n", "Philo sleeping");
	return (0);
}

int	think(void)
{
	if (usleep(1000))
	{
		printf("%s\n", "Error: usleep failed for thinking");
		return (1);
	}
	printf("%s\n", "Philo thinking");
	return (0);
}

