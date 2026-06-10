/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:08:01 by admin             #+#    #+#             */
/*   Updated: 2026/06/10 16:00:11 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int	*array_of_ints;
	t_philo	philo;

	if (!validate_args(argc, argv))
		return (1);
	array_of_ints = convert_to_int(argc, argv);
	if (!array_of_ints)
		return (1);
	if (initialise_setup(&philo))
		return (1);
	if (make_philo_and_call_routine(&philo))
		return (1);
	return (0);
}
