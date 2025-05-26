/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:47:52 by pablo             #+#    #+#             */
/*   Updated: 2025/05/26 21:09:20 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

int	check_num(char *num)
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
				continue ;
		}
		++i;
	}
	return (0);
}

int	check_repeated_number(int argc, char *argv[], int i)
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

int	is_arg_correct(int argc, char *argv[], int i, t_stack *stack_a)
{
	long	tmp;

	if (check_num(argv[i]) || check_repeated_number(argc, argv, i + 1))
		error(stack_a, NULL, NULL);
	tmp = ft_atol(argv[i]);
	if (tmp > INT_MAX || tmp < INT_MIN)
		error(stack_a, NULL, NULL);
	return ((int)tmp);
}
