/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:08:01 by admin             #+#    #+#             */
/*   Updated: 2026/06/16 17:48:12 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_param		param;

	if (log_start_time(&param.global))
		return (1);
	if (validate_args(argc, argv))
		return (1);
	if (initialise_setup(argv, &param))
		return (1);
	if (launch(&param))
		return (1);
	if (clean_setup(&param))
		return (1);
	return (0);
}
