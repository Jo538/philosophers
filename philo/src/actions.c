/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:41:59 by admin             #+#    #+#             */
/*   Updated: 2026/06/15 21:40:46 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	philo->time_last_meal = log_timestamp(philo);
	if (philo->time_last_meal == -1)
		return (1);
	printf("%ld ms: philo %d is eating\n", philo->time_last_meal, philo->id);
	if (usleep(philo->time_to_eat))
		return (error("Error: usleep failed for eating", 1));
	if (pthread_mutex_lock(&(philo->lock2)))
		return (error("Error: pthread_mutex_lock failed for lock", 1));
	philo->number_of_meals_eaten++;
	if (pthread_mutex_unlock(&(philo->lock2)))
		return (error("Error: pthread_mutex_unlock failed for lock", 1));
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	long	timestamp;

	timestamp = log_timestamp(philo);
	if (timestamp == -1)
		return (1);
	printf("%ld ms: philo %d is sleeping\n", timestamp, philo->id);
	if (usleep(philo->time_to_sleep))
		return (error("Error: usleep failed for sleeping", 1));
	timestamp = log_timestamp(philo);
	if (timestamp == -1)
		return (1);
	printf("%ld ms: philo %d is thinking\n", timestamp, philo->id);
	return (0);
}
