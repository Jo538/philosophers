/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:38:59 by admin             #+#    #+#             */
/*   Updated: 2026/06/16 18:23:59 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	grab_right_fork(t_param *param)
{
	long	timestamp;
	t_philo		*philo;
	t_global	*global;

	philo = param->philo;
	global = &param->global;
	if (pthread_mutex_lock(&(philo->right_fork)))
		return (error("Error: pthread_mutex_lock failed for right fork", 1));
	timestamp = log_timestamp(global);
	if (timestamp == -1)
		return (1);
	printf("%ld ms: philo %d has taken a fork\n", timestamp, philo->id);
	return (0);
}

int	grab_left_fork(t_param *param)
{
	long	timestamp;
	t_philo		*philo;
	t_global	*global;

	philo = param->philo;
	global = &param->global;
	if (pthread_mutex_lock(&(philo->left_fork)))
		return (error("Error: pthread_mutex_lock failed for left fork", 1));
	timestamp = log_timestamp(global);
	if (timestamp == -1)
		return (1);
	printf("%ld ms: philo %d has taken a fork\n", timestamp, philo->id);
	return (0);		
}

int	release_right_fork(t_philo *philo)
{
	if (pthread_mutex_unlock(&(philo->right_fork)))
		return (error("Error: pthread_mutex_unlock failed for right fork", 1));
	return (0);
}

int	release_left_fork(t_philo *philo)
{
	if (pthread_mutex_unlock(&(philo->left_fork)))
		return (error("Error: pthread_mutex_unlock failed for left fork", 1));
	return (0);		
}
