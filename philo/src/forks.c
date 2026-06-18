/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:38:59 by admin             #+#    #+#             */
/*   Updated: 2026/06/18 15:13:05 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	grab_right_fork(t_philo *philo)
{
	t_global	*global;
	int			id;

	id = philo->id;
	global = philo->global;
	if (pthread_mutex_lock(&global->forks[id - 1]))
		return (error("Error: lock", 1));
	print_status(philo, "has taken a fork");
	return (0);
}

int	grab_left_fork(t_philo *philo)
{
	t_global	*global;
	int			id;
	int			left;

	id = philo->id;
	global = philo->global;
	if (id == global->number_of_philosphers)
		left = 0;
	else
		left = id;
	if (pthread_mutex_lock(&global->forks[left]))
		return (error("Error: lock", 1));
	print_status(philo, "has taken a fork");
	return (0);
}

int	release_right_fork(t_philo *philo)
{
	t_global	*global;
	int			id;

	id = philo->id;
	global = philo->global;
	if (pthread_mutex_unlock(&global->forks[id - 1]))
		return (error("Error: unlock", 1));
	return (0);
}

int	release_left_fork(t_philo *philo)
{
	t_global	*global;
	int			id;
	int			left;

	id = philo->id;
	global = philo->global;
	if (id == global->number_of_philosphers)
		left = 0;
	else
		left = id;
	if (pthread_mutex_unlock(&global->forks[left]))
		return (error("Error: unlock", 1));
	return (0);
}
