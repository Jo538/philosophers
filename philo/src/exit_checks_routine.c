/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_checks_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:42:26 by admin             #+#    #+#             */
/*   Updated: 2026/06/17 18:07:31 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead_routine(t_philo *philo)
{
	t_global	*global;
	int			dead;

	global = philo->global;
	pthread_mutex_lock(&global->lock_is_dead);
	dead = global->is_dead;
	pthread_mutex_unlock(&global->lock_is_dead);
	return (dead);
}

int	have_eaten_enough_routine(t_philo *philo)
{
	t_global	*global;
	int			done;

	global = philo->global;
	pthread_mutex_lock(&global->lock_have_eaten_enough);
	done = global->have_eaten_enough;
	pthread_mutex_unlock(&global->lock_have_eaten_enough);
	return (done);
}
