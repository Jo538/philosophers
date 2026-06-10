/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 12:41:59 by admin             #+#    #+#             */
/*   Updated: 2026/06/10 12:47:11 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_right_fork(pthread_mutex_t *right_fork)
{
	if (pthread_mutex_lock(right_fork))
	{
		printf("%s\n", "Error: pthread_mutex_lock failed for right fork");
		return (1);
	}
	printf("%s\n", "Philo grabbed right fork");
	return (0);
}

void	grab_left_fork(pthread_mutex_t *left_fork)
{
	if (pthread_mutex_lock(left_fork))
	{
		printf("%s\n", "Error: pthread_mutex_lock failed for left fork");
		return (1);
	}
	printf("%s\n", "Philo grabbed left fork");
	return (0);		
}

