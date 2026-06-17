/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:08:01 by admin             #+#    #+#             */
/*   Updated: 2026/06/17 11:52:07 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_global	global;
	t_global	*ptr;
	t_philo		*philo;

	ptr = &global;
	if (log_start_time(ptr))
		return (1);
	if (validate_args(argc, argv))
		return (1);
	if (setup(argv, &philo, &ptr))
		return (1);
	if (launch(philo))
		return (1);
	if (clean_setup(philo))
		return (1);
	return (0);
}
