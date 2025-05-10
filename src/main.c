/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 10:09:50 by pablo             #+#    #+#             */
/*   Updated: 2025/05/10 12:36:16 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

/**
 * TODO: No tengo youy muy claro que el algoritmo esté funcionando.
 * Muchas veces decide pasar al Stack b números muy diferentes al que debería.
 * Genera ciertos grupos medio ordenados, pero no deja 100% listo el stack B.
 * Quizás es una forma de equilibrar entre operaciones de A a B y viceversa,
 * pero es muy posible que esté fallando en la toma de decisión del coste.
 *
 * Debería probar si es relativamente fácil hacer el llenado de B a A en orden
 * perfecto (es decir, no usando heurísticos sino forzando el siguiente
 * número) y hacer pruebas de rendimiento.
 *
 * Si se aleja mucho de lo ótpimo, habría que mirar esto
 *
 * PD: Habia un bug y siempre hacía ra y rra, nunca rb. Ahora el pseudo-orden
 * es mucho más consistente. Sigue sin ordenarlo todo el stack B al completo,
 * pero generar "chunks" de numeros ordenados, lo que puede facilitar el
 * devolverlos a A.
 */

t_stack	*parse_num(int argc, char *argv[])
{
	int		value;
	int		i;
	t_stack	*stack_a;
	t_blist	*node;

	i = 1;
	stack_a = NULL;
	while (i < argc)
	{
		value = is_arg_correct(argc, argv, i++, stack_a);
		if (i == 2)
		{
			stack_a = initialize_stack(value);
			if (!stack_a)
				return (NULL);
		}
		else
		{
			node = create_node(value);
			if (!node)
				error(stack_a, NULL);
			blstadd_back(&(stack_a->top_element), node);
		}
	}
	return (stack_a->size = i - 1, stack_a);
}

int	main(int argc, char *argv[])
{
	t_stack	*stack_a;
	t_stack	*stack_b;

	stack_a = parse_num(argc, argv);
	stack_b = initialize_b_stack(stack_a);
	push_b_algo(stack_a, stack_b);
	push_a_algo(stack_a, stack_b);
}
