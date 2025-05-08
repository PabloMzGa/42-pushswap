/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:10:32 by pablo             #+#    #+#             */
/*   Updated: 2025/05/08 21:18:07 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H

# define PUSHSWAP_H

# include "libft.h"

typedef struct s_bidirectional_list
{
	int							value;
	struct s_bidirectional_list	*previous;
	struct s_bidirectional_list	*next;
}								t_blist;

typedef struct s_stack
{
	size_t						size;
	t_blist						*top_element;

}								t_stack;

/**
 * @brief Adds a new element to the end of a doubly linked list.
 *
 * @lst: A pointer to the pointer of the first element of the list.
 *       If the list is empty, the new element will become the first element.
 * @new: A pointer to the new element to be added to the list.
 *       The new element's `previous` pointer will be updated to point to the
 *       last element of the list.
 *
 * This function traverses the list to find the last element and appends the
 * new element to it. If the list is empty, the new element becomes the first
 * element. If either `lst` or `new` is NULL, the function does nothing.
 */
void							blstadd_back(t_blist **lst, t_blist *new);

/**
 * @brief Adds a new element to the front of a doubly linked list.
 *
 * This function inserts a new element at the beginning of a doubly linked list.
 * It updates the `next` pointer of the new element to point to the current head
 * of the list and updates the `previous` pointer of the current head to point
 * back to the new element. Finally, it updates the head of the list to the new
 * element.
 *
 * @param lst A pointer to the pointer of the head of the doubly linked list.
 *            If the list is empty, *lst should be NULL.
 * @param new A pointer to the new element to be added to the list. The `new`
 *            element must not be NULL and should be properly initialized.
 */
void							blstadd_front(t_blist **lst, t_blist *new);

/////////////////////////// ARGUMENTS CHECK ////////////////////////////////////

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
int								check_num(char *num);

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
int								check_repeated_number(int argc, char *argv[],
									int i);

/**
 * @brief Validates a command-line argument and converts it to an integer.
 *
 * @param argc The total number of command-line arguments.
 * @param argv The array of command-line argument strings.
 * @param i The index of the current argument to validate.
 * @param stack_a A pointer to the stack structure used for error handling.
 *
 * This function performs the following checks on the argument at index `i`:
 * - Ensures the argument is a valid number using `check_num`.
 * - Ensures the argument is not a duplicate using `check_repeated_number`.
 * - Converts the argument to a long integer using `ft_atol` and ensures it
 *   falls within the range of a 32-bit signed integer (INT_MIN to INT_MAX).
 *
 * If any of these checks fail, the function calls `error` to handle the error
 * and terminates the program. If all checks pass, the function returns the
 * argument as an integer.
 *
 * @return The validated and converted integer value of the argument.
 */
int	is_arg_correct(int argc, char *argv[], int i, t_stack *stack_a);
#endif

///////////////////////////////// ERROR ////////////////////////////////////////

/**
 * @brief Handles errors by cleaning up the provided stacks and exiting the
 *        program.
 *
 * This function is used to handle errors in the program. It ensures that any
 * allocated memory for the provided stacks is properly freed before exiting
 * the program. Additionally, it writes an error message to the standard error
 * output.
 *
 * @param stack_a Pointer to the first stack (can be NULL).
 * @param stack_b Pointer to the second stack (can be NULL).
 *
 * If either stack_a or stack_b is not NULL, the function calls `clean_stack`
 * to free the memory associated with the stack. After cleaning up, it writes
 * "Error\n" to STDERR and terminates the program with an exit status of
 * `EXIT_FAILURE`.
 */
void	error(t_stack *stack_a, t_stack *stack_b);


/////////////////////////// STACK OPERATIONS ///////////////////////////////////

/**
 * @brief Performs a swap operation on one or both stacks and writes the
 *        corresponding operation name to the standard output.
 *
 * @param stack_a Pointer to the first stack (can be NULL).
 * @param stack_b Pointer to the second stack (can be NULL).
 *
 * The function performs the following actions:
 * - If only `stack_a` is provided, it swaps the top two elements of `stack_a`
 *   and writes "sa\n" to the standard output.
 * - If only `stack_b` is provided, it swaps the top two elements of `stack_b`
 *   and writes "sb\n" to the standard output.
 * - If both `stack_a` and `stack_b` are provided, it swaps the top two elements
 *   of both stacks and writes "ss\n" to the standard output.
 */
void	swap(t_stack *stack_a, t_stack *stack_b);
