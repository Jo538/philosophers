/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 15:45:12 by admin             #+#    #+#             */
/*   Updated: 2026/06/10 16:15:42 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// how do I communicate an error happening in the routine back to make_philo_and_call_routine?
static void	*routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	grab_right_fork(&(philo->right_fork));
	grab_left_fork(&(philo->left_fork));
	eat();
	release_right_fork(&(philo->right_fork));
	release_left_fork(&(philo->left_fork));
	philo_sleep();
	think();
	return (NULL);
}

int	make_philo_and_call_routine(t_philo *philo)
{
	int			id;

	id = 1;
	if (pthread_create(&(philo->philo), NULL, routine, philo))
	{
		printf("%s\n", "Error: pthread_create failed");
		return (1);
	}
	printf("%s\n", "philo created");
	return (0);
}