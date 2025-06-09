/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:47:52 by pablo             #+#    #+#             */
/*   Updated: 2025/06/09 21:54:10 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/**
 * @brief Checks if the given string represents a valid numeric value.
 *
 * This function verifies if the input string `num` consists of valid numeric
 * characters. It allows an optional leading '-' sign for negative numbers.
 * If the string contains any invalid characters, the function returns 1.
 *
 * @param num The string to be checked.
 * @return int Returns 0 if the string is a valid numeric value, otherwise 1.
 */
static int	check_num(char *num)
{
	size_t	i;

	i = 0;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
		{
			if (i != 0)
				return (1);
			else if (num[i] == '-')
			{
				++i;
				continue ;
			}
		}
		++i;
	}
	return (0);
}

/**
 * @brief Checks for duplicate numbers in the given arguments.
 *
 * @param argc The total number of arguments passed to the program.
 * @param argv The array of argument strings.
 * @param : The index of the current number to check for duplicates.
 *
 * This function compares the number at index `i - 1` in the `argv` array
 * with all subsequent numbers in the array. If a duplicate is found, it
 * returns 1. Otherwise, it returns 0.
 *
 * @return 1 if a duplicate number is found, 0 otherwise.
 */
static int	check_repeated_number(int argc, char *argv[], int i)
{
	int	current_n;

	current_n = ft_atoi(argv[i - 1]);
	while (i < argc)
	{
		if (current_n == ft_atoi(argv[i]))
			return (1);
		++i;
	}
	return (0);
}

char	**clean_argv(int argc, char *argv[])
{
	char	*tmp;
	char	*clean;
	char	**splitted;
	int		i;

	if (argc < 2)
		return (NULL);
	i = 2;
	clean = ft_strjoin(argv[1], " ");
	if (!clean)
		return (NULL);
	while (i < argc)
	{
		tmp = ft_strjoin(clean, argv[i++]);
		ft_free((void **)&clean);
		if (!tmp)
			return (NULL);
		clean = ft_strjoin(tmp, " ");
		ft_free((void **)&tmp);
		if (!clean)
			return (NULL);
	}
	splitted = ft_split(clean, ' ');
	return (ft_free((void **)&clean), splitted);
}

int	is_arg_correct(int argc, char *argv[], int i, t_stack *stack_a)
{
	long	tmp;

	if (check_num(argv[i]) || check_repeated_number(argc, argv, i + 1))
	{
		ft_matrix_free((void ***)&argv, 0);
		error(stack_a, NULL);
	}
	tmp = ft_atol(argv[i]);
	if (tmp > INT_MAX || tmp < INT_MIN)
	{
		ft_matrix_free((void ***)&argv, 0);
		error(stack_a, NULL);
	}
	return ((int)tmp);
}
