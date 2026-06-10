/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 19:03:14 by admin             #+#    #+#             */
/*   Updated: 2026/06/10 12:16:22 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int main(void)
{
	printf("%s\n\n", "-----VALIDATE COMMAND LINE ARGUMENTS-----");
	test_validate_args();
	printf("\n\n%s\n\n", "-----CONVERT COMMAND LINE ARGUMENTS TO AN ARRAY OF INTS-----");
	test_convert_to_int();
	printf("\n\n%s\n\n", "-----CREATE PHILO VIA THREAD-----");
	test_initialise_setup();
}