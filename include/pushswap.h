/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablo <pablo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:10:32 by pablo             #+#    #+#             */
/*   Updated: 2025/05/23 13:46:43 by pablo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * TODO: Buscar una forma de limpiar los cost cuando llama a error(). Quizás
 * guardar una referencia a cost en los stacks para poder limpiarlos?
 */

#ifndef PUSHSWAP_H

# define PUSHSWAP_H

# include "libft.h"

/////////////////////////////// STRUCTS ////////////////////////////////////////
typedef struct s_bidirectional_list
{
	int							value;
	struct s_bidirectional_list	*previous;
	struct s_bidirectional_list	*next;
}								t_blist;

typedef struct s_stack
{
	int							size;
	t_blist						*top_element;

}								t_stack;

/**
 * @struct s_cost_info
 * @brief Structure to store movement and cost information for stack operations.
 *
 * This structure is used to calculate and store the number of movements
 * required in both stacks (A and B), the total cost of an operation, and
 * the indices of the elements involved in the operation.
 *
 * @param stack_a_mov Number of movements required in stack A. If it's negative
 *                    the movements are in reverse.
 * @param stack_b_mov Number of movements required in stack B. If it's negative
 *                    the movements are in reverse.
 * @param total_cost Total cost of the operation, typically calculated as the
 *                   sum of movements in both stacks.
 * @param candidate_index Index of the element in stack A involved in the
 *                        operation.
 */
typedef struct s_cost_info
{
	int							stack_a_mov;
	int							stack_b_mov;
	int							total_cost;
	int							candidate_index;
}								t_cost;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////// ALGORITHM ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Applies rotate or reverse rotate operation on stack A based on counter
 *
 * This function applies different rotation operations depending on the counter
 * value:
 * - If counter is negative: performs a reverse rotation and increments counter
 * - If counter is zero or positive: performs a rotation and decrements counter
 *
 * @param stack Pointer to stack A structure
 * @param counter Pointer to counter that tracks rotation operations
 *
 * @note The NULL parameter in rotation calls indicates that output is
 *       suppressed
 */
void							apply_a_rot(t_stack *stack, int *counter);

/**
 * @brief Applies rotate or reverse rotate operation on stack B based on counter
 *
 * This function applies different rotation operations depending on the counter
 * value:
 * - If counter is negative: performs a reverse rotation and increments counter
 * - If counter is zero or positive: performs a rotation and decrements counter
 *
 * @param stack Pointer to stack B structure
 * @param counter Pointer to counter that tracks rotation operations
 *
 * @note The NULL parameter in rotation calls indicates that output is
 *       suppressed
 */
void							apply_b_rot(t_stack *stack, int *counter);

/**
 * @brief Applies rotation to both stacks simultaneously based on movement cost
 *
 * This function optimizes stack operations by performing simultaneous rotations
 * on both stacks when possible. Depending on the sign of stack_a_mov in the
 * cost structure, it either:
 *
 * - Performs reverse rotation on both stacks if movement is negative
 *
 * - Performs forward rotation on both stacks if movement is positive
 *
 * After each operation, it updates the movement counters in the cost structure.
 *
 * @param stack_a Pointer to the first stack
 * @param stack_b Pointer to the second stack
 * @param cost Pointer to cost structure containing movement information
 */
void							apply_double_rot(t_stack *stack_a,
									t_stack *stack_b, t_cost *cost);

/**
 * @brief Calculates the cost of moving elements between two stacks.
 *
 * This function computes the cost associated with moving elements
 * from stack_b to stack_a. It initializes a cost structure, determines
 * the optimal positions for elements in both stacks, and calculates
 * the distances required for the operations.
 *
 * @param stack_a Pointer to the first stack (stack_a).
 * @param stack_b Pointer to the second stack (stack_b).
 * @return A pointer to a t_cost structure containing the calculated costs.
 */
t_cost							*calculate_cost(t_stack *stack_a,
									t_stack *stack_b);

int								get_lowest_distance(int n, t_stack *stack_a,
									t_stack *stack_b, int a_distance);

/**
 * @brief Calculates the optimized cost of moving elements between stacks.
 *
 * This function determines the cost of moving elements between two stacks
 * based on the number of movements required for stack A (`a_mov`) and stack B
 * (`b_mov`). The cost is calculated differently depending on whether the
 * movements are in the same direction or opposite directions.
 *
 * - If the movements are in opposite directions (one positive, one negative),
 *   the cost is the sum of the absolute values of the movements.
 * - If the movements are in the same direction, the cost is the larger of the
 *   absolute values of the movements.
 *
 * An additional cost of 1 is added to the result to account for the operation
 * itself.
 *
 * @param a_mov The number of movements required for stack A. Positive values
 *              indicate upward movements, and negative values indicate
 *              downward movements.
 * @param b_mov The number of movements required for stack B. Positive values
 *              indicate upward movements, and negative values indicate
 *              downward movements.
 * @return The optimized cost of the movements.
 */
int								get_optimized_cost(int a_mov, int b_mov);

/**
 * @brief Moves all elements from stack_b to stack_a in descending order
 *
 * This function implements the "push A" phase of the algorithm by:
 * 1. Finding the highest value node in stack_b
 * 2. Rotating stack_b until that node is at the top
 * 3. Pushing the top node from stack_b to stack_a
 * 4. Repeating until stack_b is empty
 *
 * After execution, all elements will be in stack_a and stack_b will be empty.
 *
 * @param stack_a Pointer to the destination stack
 * @param stack_b Pointer to the source stack
 */
void							push_a_algo(t_stack *stack_a, t_stack *stack_b);

/**
 * @brief Moves elements from stack A to stack B using an optimized strategy
 *
 * This function implements part of the Push Swap sorting algorithm.
 * It transfers elements from stack A to stack B until only 3 elements
 * remain in stack A. For each element to be moved, it:
 *
 * 1. Calculates the optimal moves needed
 *
 * 2. Performs combined movements when possible (rr, rrr)
 *
 * 3. Performs individual stack movements when necessary
 *
 * 4. Pushes the correctly positioned element to stack B
 *
 * @param stack_a Pointer to the source stack
 * @param stack_b Pointer to the destination stack
 */
void							push_b_algo(t_stack *stack_a, t_stack *stack_b);

/**
 * @brief Searches for the closest higher value than the given number in the
 *        stack.
 *
 * This function iterates through the stack and finds the index of the element
 * whose value is the closest higher value compared to the given number `n`.
 *
 * @param n The reference number to compare against.
 * @param stack A pointer to the stack structure containing the elements.
 *              The stack is assumed to have a `top_element` pointer to the
 *              first node and a `size` indicating the number of elements in
 *              the stack.
 *
 * @return The index of the element in the stack with the closest higher value
 *         compared to `n`. If no such element exists, the function returns -1.
 */
int								search_closest_high(int n, t_stack *stack);

/**
 * @brief Searches for the closest lower value than the given number in the
 *        stack.
 *
 * This function iterates through the stack and finds the index of the element
 * whose value is the closest lower value compared to the given number `n`.
 *
 * @param n The reference number to compare against.
 * @param stack A pointer to the stack structure containing the elements.
 *              The stack is assumed to have a `top_element` pointer to the
 *              first node and a `size` indicating the number of elements in
 *              the stack.
 *
 * @return The index of the element in the stack with the closest lower value
 *         compared to `n`. If no such element exists, the function returns -1.
 */
int								search_closest_low(int n, t_stack *stack);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// ARGUMENTS CHECK ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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
int								is_arg_correct(int argc, char *argv[], int i,
									t_stack *stack_a);

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
void	clean_stack(t_stack *stack);

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
void							error(t_stack *stack_a, t_stack *stack_b);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// INITIALIZATION /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Allocates and initializes an empty stack.
 *
 * This function creates a new stack structure by allocating memory for it.
 * The stack is initialized with no elements (top_element is set to NULL).
 *
 * @return A pointer to the newly created stack, or NULL if memory allocation
 * fails.
 */
t_stack							*initialize_empty_stack(void);

/**
 * @brief Initializes stack B by creating an empty stack and pushing
 *        two elements from stack A to stack B.
 *
 * @param stack_a Pointer to the source stack (stack A) from which
 *                elements will be pushed to stack B.
 *
 * @return Pointer to the newly initialized stack B.
 */
t_stack							*initialize_b_stack(t_stack *stack_a);

/**
 * @brief Initializes a stack with a single element at the top.
 *
 * This function allocates memory for a new stack and its top element.
 * The top element is initialized with the provided value. If any memory
 * allocation fails, the function ensures proper cleanup and returns NULL.
 *
 * @param top_value The value to initialize the top element of the stack with.
 *
 * @return A pointer to the newly created stack, or NULL if memory allocation
 * fails.
 */
t_stack							*initialize_stack(int top_value);

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
 * @brief Find the index of the node with the highest value in a linked list
 *
 * This function traverses the given linked list and identifies the node
 * containing the highest value. It returns the index (position) of this node
 * in the list, with the first node being at index 0.
 *
 * @param lst Pointer to the first node of the linked list to search
 * @return The index of the node with the highest value, or -1 if the list is
 *         empty
 */
int								get_highest_node(t_blist *lst);

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

/**
 * @brief Retrieves a node from a linked list at a specified index.
 *
 * This function traverses a linked list starting from the given node
 * and returns the node located at the specified index. If the index
 * is out of bounds or the list is empty, the function returns NULL.
 *
 * @param index The zero-based index of the node to retrieve.
 * @param node A pointer to the starting node of the linked list.
 * @return A pointer to the node at the specified index, or NULL if
 *         the index is out of bounds or the list is empty.
 */
t_blist							*get_node_from_index(int index, t_blist *node);

/**
 * @brief Calculate the distance to reach an element in a stack
 *
 * This function calculates the number of moves needed to reach a specific index
 * in the stack. If the index is in the first half of the stack, it returns a
 * positive value representing moves from the top. If it's in the second half,
 * it returns a negative value representing moves from the bottom.
 *
 * @param index The index of the element in the stack
 * @param stack Pointer to the stack structure
 * @return int Distance to the bottom: positive value for up (normal)
 *         operations, negative for bottom (reverse) operations
 */
int								get_bottom_distance(int index, t_stack *stack);

/**
 * @brief Calculates the distance to move an element to the top of the stack.
 *
 * This function determines the number of steps required to bring an element
 * at a given index to the top of the stack. If the index is in the second
 * half of the stack, the function returns a negative value, indicating that
 * the element should be moved in the reverse direction.
 *
 * @param index The index of the element in the stack.
 * @param stack A pointer to the stack structure containing the element.
 * @return The number of steps required to move the element to the top.
 *         A positive value indicates forward movement, while a negative
 *         value indicates reverse movement.
 */
int								get_top_distance(int index, t_stack *stack);

////////////////////////////////////////////////////////////////////////////////
/////////////////////////// STACK OPERATIONS ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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
void							push(t_stack *stack_a, t_stack *stack_b,
									char dir);

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
 *       rotates that stack and writes the corresponding operation ("ra\n"
 *       or "rb\n") to the standard output. If both stacks are provided,
 *       the function rotates both stacks simultaneously and writes "rr\n"
 *       to the standard output.
 *
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
 * - If only stack_a is provided, it rotates stack_a in reverse and writes
 *   "rra\n".
 *
 * - If only stack_b is provided, it rotates stack_b in reverse and writes
 *   "rrb\n".
 *
 * - If both stack_a and stack_b are provided, it rotates both in reverse and
 *   writes "rrr\n".
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
///////////////////////////////// DEBUG ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void							print_stack(t_stack *stack, char stackname);

void							print_cost(t_cost *cost, t_stack *stack_a);
#endif
