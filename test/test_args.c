/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 19:03:14 by admin             #+#    #+#             */
/*   Updated: 2026/06/10 11:44:47 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void assert(int actual, int expected, char *test, int test_nb)
{
	printf("Test %d: %s\n", test_nb, test);
	if (actual != expected)
		printf("%s\n\n", "Failure");
	else
		printf("%s\n\n", "Success");	
}

void test_validate_args(void)
{
	int res;

	// Test 1: 1 2 3
	res = validate_args(4, (char *[]){"test_philo", "1", "2", "3", NULL});
	assert(res, 1, "1 2 3", 1);

	// Test 2: 1 2 3 4
	res = validate_args(5, (char *[]){"test_philo", "1", "2", "3", "4", NULL});
	assert(res, 0, "1 2 3 4", 2);
	
	// Test 3: 1 2 3 4 5 --> too many arguments
	res = validate_args(6, (char *[]){"test_philo", "1", "2", "3", "4", "5", NULL});
	assert(res, 0, "1 2 3 4 5", 3);
	
	// Test 4: 1 2 --> not enough arguments
	res = validate_args(3, (char *[]){"test_philo", "1", "2", NULL});
	assert(res, 1, "1 2", 4);
	
	// Test 5: 1-25 3 4 --> invalid argument
	res = validate_args(4, (char *[]){"test_philo", "1-25", "3", "4", NULL});
	assert(res, 1, "1-25 3 3 4", 5);

	// Test 6: "" --> empty argument
	res = validate_args(2, (char *[]){"test_philo", "", NULL});
	assert(res, 1, "\"\"", 6);

	// Test 7: No argument
	res = validate_args(1, (char *[]){NULL});
	assert(res, 1, "no argument", 7);
}

static void helper(int *actual, int *expected, int size, char *test)
{
	printf("Test: %s\n", test);
	int i = 0;
	while (i < size)
	{
		if (actual[i] != expected[i])
		{
			printf("Failure: %c != %c\n\n", actual[i], expected[i]);
			return ;			
		}
		i++;			
	}
	printf("%s\n\n", "Success");
}


void test_convert_to_int(void)
{
	// Test: 1 2 34
	int *array = convert_to_int(4, (char *[]){"test_philo", "1", "2", "34", NULL});
	helper(array, (int[]){1, 2, 34}, 3, "1 2 34");
	free(array);
}