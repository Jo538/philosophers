/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:17:29 by admin             #+#    #+#             */
/*   Updated: 2026/06/10 11:42:49 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	is_positive_int(char *str)
{
	int	i;
	
	i = 0;

	if (str[0] == '+')
		i++;	
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	are_positive_ints(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!is_positive_int(argv[i]))
			return (0);
		i++;
	}
	return (1);
}

int	validate_args(int argc, char **argv)
{
	if ((argc != 5) && (argc != 6))
	{
		printf("%s\n", "Error: Incorrect number of philosophers");
		return (1);	
	}
	if (!are_positive_ints(argv))
	{
		printf("%s\n", "Error: Invalid argv format");
		return (1);	
	}
	return (0);
}