/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 11:38:01 by pablo             #+#    #+#             */
/*   Updated: 2025/06/07 13:42:30 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "libft.h"

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// STRUCTS ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @struct s_bidirectional_list
 * @brief A structure representing a node in a bidirectional linked list.
 *
 * This structure implements a node for a doubly linked list, allowing
 * traversal in both directions through the list. It also includes
 * pre-calculated pointers to the expected previous and next nodes
 * in the sorted order for optimization purposes.
 *
 * @typedef t_blist
 * @param value The integer value stored in this node.
 * @param previous Pointer to the previous node in the list, or NULL if first
 *                 node.
 * @param next Pointer to the next node in the list, or NULL if last node.
 */
typedef struct s_bidirectional_list
{
	int							value;
	struct s_bidirectional_list	*previous;
	struct s_bidirectional_list	*next;
}								t_blist;

/**
 * @struct s_stack
 * @brief Structure representing a stack for the push_swap algorithm.
 *
 * This structure implements a stack data structure used in the push_swap
 * sorting algorithm. It keeps track of the size of the stack and points
 * to the top element.
 *
 * @param size The number of elements currently in the stack.
 * @param top_element Pointer to the top element of the stack, implemented as a
 *                    bidirectional list (t_blist).
 * @param id Character identifier for the stack ('A' or 'B').
 */
typedef struct s_stack
{
	int							size;
	t_blist						*top_element;
	char						id;

}								t_stack;

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// ARGUMENTS CHECK ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Combines and normalizes command line arguments into a single array
 *
 * This function takes the raw argv array and joins all arguments (starting
 * from index 1) into a single string separated by spaces. It then splits this
 * string by spaces to create a new, normalized array of arguments.
 *
 * This is useful for handling cases where arguments might contain spaces or
 * when arguments are provided both as separate elements and as space-separated
 * values within the same element.
 *
 * @param argc The number of arguments in argv
 * @param argv The array of command line arguments
 * @return A newly allocated array of strings containing the normalized
 *         arguments, or NULL if memory allocation fails
 * @note The returned array must be freed by the caller, including each string
 */
char							**clean_argv(int argc, char *argv[]);

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
int								is_arg_correct(int argc, char *argv[], int i,
									t_stack *stack_a);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////// CHECKER ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Checks if a stack is sorted in ascending order (from top to bottom)
 *
 * This function traverses a stack from top to bottom and verifies that each
 * element is less than the next element, ensuring the stack is
 * sorted in ascending order.
 *
 * @param stack Pointer to the stack structure to check
 * @return 1 if the stack is sorted in ascending order, 0 otherwise
 */
int								is_stack_sorted(t_stack *stack);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// INITIALIZATION /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Allocates and initializes an empty stack.
 *
 * This function creates a new stack structure by allocating memory for it.
 * The stack is initialized with no elements (top_element is set to NULL).
 *
 * @param id Character identifier for the stack ('A' or 'B').
 * @return A pointer to the newly created stack, or NULL if memory allocation
 * fails.
 */
t_stack							*initialize_empty_stack(char id);

/**
 * @brief Populates stack A with values from command-line arguments
 *
 * This function takes command-line arguments, validates them as integers,
 * and constructs a stack data structure with these values. The first valid
 * argument initializes the stack, and subsequent arguments are added as nodes
 * to the stack.
 *
 * @param argc The count of command-line arguments
 * @param argv Array of command-line argument strings
 *
 * @return Pointer to the populated stack, or NULL if memory allocation fails
 *
 * @note The function checks if arguments are valid using is_arg_correct()
 * @note Memory error handling is implemented - if allocation fails, the
 *       function calls error() which frees allocated memory and exits the
 *       program.
 * @note The stack size is set to (argc-1) before returning
 */
t_stack							*populate_a_stack(int argc, char *argv[]);
////////////////////////////////////////////////////////////////////////////////
//////////////////////////// LIST HELPERS //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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
 * @brief Creates a new node for a doubly linked list.
 *
 * This function allocates memory for a new node of type `t_blist` and
 * initializes its `value` field with the given integer `n`.
 *
 * @param n The integer value to be stored in the new node.
 *
 * @return A pointer to the newly created node, or NULL if memory allocation
 * fails.
 */
t_blist							*create_node(int n);


/**
 * @brief Retrieves the last node in a linked list.
 *
 * This function traverses a linked list starting from the given node
 * and returns a pointer to the last node in the list.
 *
 * @param lst A pointer to the first node of the linked list.
 *            If the list is empty (NULL), the behavior is undefined.
 *
 * @return A pointer to the last node in the linked list.
 */
t_blist							*get_last_node(t_blist *lst);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// STACK OPERATIONS ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Performs a swap operation on one or both stacks.
 *
 * Swaps the first two elements at the top of the specified stack(s).
 * - If only stack_a is provided, swaps stack_a and writes "sa\n".
 * - If only stack_b is provided, swaps stack_b and writes "sb\n".
 * - If both are provided, swaps both and writes "ss\n".
 * - If neither or if stack(s) have <2 elements, calls error handler.
 *
 * @param stack_a Pointer to the first stack (can be NULL).
 * @param stack_b Pointer to the second stack (can be NULL).
 */
void							swap(t_stack *stack_a, t_stack *stack_b);

/**
 * @brief Pushes the top element from one stack to another based on the
 *        direction.
 *
 * This function transfers the top element from one stack to another.
 * The direction of the push is determined by the `dir` parameter:
 *
 * - 'a': Pushes the top element from stack_b to stack_a.
 *
 * - 'b': Pushes the top element from stack_a to stack_b.
 *
 * If the source stack is empty or its top element is NULL, the function calls
 * the `error` function to handle the error.
 *
 * @param stack_a Pointer to the first stack (stack_a).
 * @param stack_b Pointer to the second stack (stack_b).
 * @param dir A character indicating the direction of the push ('a' or 'b').
 *
 * @note If an invalid direction is provided, the function calls the `error`
 *       function.
 */
void	push(t_stack *stack_a, t_stack *stack_b, char dir);

/**
 * @brief Rotates the elements of one or both stacks upwards.
 *
 * This function performs a rotation operation on the given stack(s). A rotation
 * moves the top element of the stack to the bottom, effectively shifting all
 * other elements up by one position.
 *
 * @param stack_a Pointer to the first stack (t_stack). If NULL, no operation is
 *                performed on stack_a.
 * @param stack_b Pointer to the second stack (t_stack). If NULL, no operation
 *                is performed on stack_b.
 *
 * @note If only one stack is provided (stack_a or stack_b), the function
 *       rotates that stack. If both stacks are provided, the function rotates
 *       both stacks simultaneously.
 * @note If a stack is empty or has only one element, the function calls the
 *       `error` function to handle the error condition.
 */
void							rotate(t_stack *stack_a, t_stack *stack_b);

/**
 * @brief Performs a reverse rotation operation on one or both
 * stacks.
 *
 * This function performs a reverse rotation operation on the given stack(s):
 *
 * - If only stack_a is provided, it rotates stack_a in reverse.
 *
 * - If only stack_b is provided, it rotates stack_b in reverse.
 *
 * - If both stack_a and stack_b are provided, it rotates both in reverse.
 *
 * If any of the stacks are invalid (e.g., NULL top element or size <= 1),
 * the function calls the error handler and terminates.
 *
 * @param stack_a Pointer to the first stack (can be NULL if only stack_b is
 *                used).
 * @param stack_b Pointer to the second stack (can be NULL if only stack_a is
 *                used).
 *
 */
void							reverse_rotate(t_stack *stack_a,
									t_stack *stack_b);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// UTILS /////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Frees all memory associated with a stack and its elements.
 *
 * This function iterates through all the elements in the stack, freeing
 * the memory allocated for each element's content and the element itself.
 * Finally, it frees the memory allocated for the stack structure.
 *
 * @param stack A pointer to the stack to be cleaned. The stack and all
 *              its elements will be deallocated.
 */
void							clean_stack(t_stack *stack);

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
 * @param cost Pointer to a cost struct (can be NULL).
 *
 * If either stack_a or stack_b is not NULL, the function calls `clean_stack`
 * to free the memory associated with the stack. After cleaning up, it writes
 * "Error\n" to STDERR and terminates the program with an exit status of
 * `EXIT_FAILURE`.
 */
void							error(t_stack *stack_a, t_stack *stack_b);

/**
 * @brief Cleans up both stack_a and stack_b, prints "KO" to standard output,
 * and exits the program with failure status.
 *
 * This function is typically called when an error or invalid state is
 * detected. It ensures that any allocated memory for the stacks is properly
 * freed before terminating the program.
 *
 * @param stack_a Pointer to the first stack to be cleaned.
 * @param stack_b Pointer to the second stack to be cleaned.
 */
void	ko(t_stack *stack_a, t_stack *stack_b);

/**
 * @brief Cleans up both stack_a and stack_b, then prints "OK" to stdout.
 *
 * This function checks if the provided stack pointers are not NULL,
 * and if so, calls clean_stack on each to free their resources.
 * After cleaning, it writes "OK\n" to the standard output.
 *
 * @param stack_a Pointer to the first stack to be cleaned.
 * @param stack_b Pointer to the second stack to be cleaned.
 */
void	ok(t_stack *stack_a, t_stack *stack_b);

#endif
