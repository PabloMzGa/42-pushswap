/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:10:32 by pablo             #+#    #+#             */
/*   Updated: 2025/06/16 13:06:19 by pabmart2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H

# define PUSHSWAP_H

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

/**
 * @brief Structure to store movement and cost information for stack ops.
 *
 * This structure is used to calculate and store the number of movements
 * required in both source and destination stacks, the total cost of an
 * operation, and the indices of the elements involved in the operation.
 *
 * @param source_mov Number of movements required in source stack. If negative,
 *                   the movements are in reverse.
 * @param dest_mov Number of movements required in destination stack. If
 *                 negative, the movements are in reverse.
 * @param total_cost Total cost of the operation, typically calculated as the
 *                   sum of movements in both stacks.
 * @param candidate_index Index of the element in source stack involved in the
 *                        operation.
 **/
typedef struct s_cost_info
{
	int							source_mov;
	int							dest_mov;
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
 * @param cost Pointer to the cost struct.
 * @param counter Pointer to counter that tracks rotation operations
 *
 * @note The NULL parameter in rotation calls indicates that output is
 *       suppressed
 */
void							apply_a_rot(t_stack *stack, t_cost *cost,
									int *counter);

/**
 * @brief Applies rotate or reverse rotate operation on stack B based on counter
 *
 * This function applies different rotation operations depending on the counter
 * value:
 * - If counter is negative: performs a reverse rotation and increments counter
 * - If counter is zero or positive: performs a rotation and decrements counter
 *
 * @param stack Pointer to stack B structure
 * @param cost Pointer to the cost struct.
 * @param counter Pointer to counter that tracks rotation operations
 *
 * @note The NULL parameter in rotation calls indicates that output is
 *       suppressed
 */
void							apply_b_rot(t_stack *stack, t_cost *cost,
									int *counter);

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
 * @brief Calculates the cost of moving elements between two stacks (universal).
 *
 * This function computes the cost associated with moving elements
 * from source_stack to dest_stack. It initializes a cost structure, determines
 * the optimal positions for elements in both stacks, and calculates
 * the distances required for the operations.
 *
 * @param source_stack Pointer to the source stack (where elements are
 *                     taken from).
 * @param dest_stack Pointer to the destination stack (where elements
 *                   are inserted).
 * @return A pointer to a t_cost structure containing the calculated costs.
 */
t_cost							*calculate_cost(t_stack *source_stack,
									t_stack *dest_stack);

/**
 * @brief Determines the most efficient distance to reach the optimal insertion
 *        point
 *
 * This function finds the closest higher and lower numbers to 'n' in stack_b,
 * calculates the distance to reach each of them, and returns the distance that
 * would result in the most efficient operation when combined with a_distance.
 *
 * @param n The number from stack_a to find an insertion point for
 * @param stack_b The destination stack to insert into
 * @param a_distance The distance/cost to access the number in stack_a
 *
 * @return The optimal distance in stack_b, or INT_MAX if no valid insertion
 *         point
 */
int								get_lowest_distance(int n, t_stack *stack_b,
									int a_distance);

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

/**
 * @brief Moves all elements from stack_b to stack_a using a cost-based
 * algorithm.
 *
 * Repeatedly calculates the optimal cost to move elements from stack_b
 * to stack_a, applies the necessary rotations to both stacks to minimize
 * operations, and pushes the element from stack_b to stack_a. After all
 * elements have been moved, it performs a final sort on stack_a.
 *
 * Uses helpers to:
 *
 * - Calculate move cost.
 *
 * - Apply double/single rotations.
 *
 * - Push from stack_b to stack_a.
 *
 * - Free cost memory.
 *
 * - Final sort on stack_a.
 *
 * @param stack_a Pointer to stack_a (destination).
 * @param stack_b Pointer to stack_b (source).
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

/**
 * @brief Sorts a stack containing exactly two elements in ascending order.
 *
 * This function compares the top two elements of the given stack. If the first
 * (top) element is greater than the second, it swaps them to ensure the stack
 * is sorted in ascending order. Assumes the stack contains at least two
 * elements.
 *
 * @param stack Pointer to the stack to be sorted.
 */
void							sort_2(t_stack *stack);

/**
 * @brief Sorts the top three elements of the given stack in ascending order.
 *
 * This function assumes that the stack contains at least three elements.
 * It compares the values of the top three elements and applies the minimal
 * sequence of stack operations (swap, rotate, reverse rotate) to sort them.
 * If the elements are already sorted, the function does nothing.
 *
 * @param stack Pointer to the stack to be sorted.
 */
void							sort_3(t_stack *stack);

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
/////////////////////////// INITIALIZATION /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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
 * @param cost Pointer to the cost struct.
 * @param dir A character indicating the direction of the push ('a' or 'b').
 *
 * @note If an invalid direction is provided, the function calls the `error`
 *       function.
 */
void							push(t_stack *stack_a, t_stack *stack_b,
									t_cost *cost, char dir);

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
 * @param cost Pointer to the cost struct.
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
void							rotate(t_stack *stack_a, t_stack *stack_b,
									t_cost *cost);

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
 * @param cost Pointer to the cost struct.
 *
 */
void							reverse_rotate(t_stack *stack_a,
									t_stack *stack_b, t_cost *cost);

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
void							error(t_stack *stack_a, t_stack *stack_b,
									t_cost *cost);
#endif
