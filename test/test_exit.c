/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 17:02:49 by admin             #+#    #+#             */
/*   Updated: 2026/06/17 18:06:14 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void test_have_eaten_enough(void)
{
	// 2 philosophers, each ate 3 times, supposed to eat 3 times
	t_philo philo[2];
	t_global global;

	global.number_of_philosphers = 2;
	global.number_of_times_must_eat = 3;
	global.have_eaten_enough = 0;
	pthread_mutex_init(&global.lock_number_of_meals_eaten, NULL);
	pthread_mutex_init(&global.lock_have_eaten_enough, NULL);
	
	philo[0].global = &global;
	philo[0].number_of_meals_eaten = 3;
	philo[1].global = &global;
	philo[1].number_of_meals_eaten = 3;

	monitor_eating(philo);
	printf("Have eaten enough: %d\n", global.have_eaten_enough);
	
}