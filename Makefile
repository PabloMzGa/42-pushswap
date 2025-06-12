# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pabmart2 <pabmart2@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 14:34:30 by pabmart2          #+#    #+#              #
#    Updated: 2025/06/12 21:18:34 by pabmart2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
DEBUG_FLAGS = -g -fno-inline
LDFLAGS = -lm
BUILD_DIR = build

OBJ_DIR = build/obj

NAME = push_swap

HEADERS = \
	include/pushswap.h \

SRC = \
	src/arg_check.c \
	src/error_clean.c \
	src/initialization.c \
	src/main.c \
	src/algorithm/apply_mov.c \
	src/algorithm/sort_check.c \
	src/algorithm/push_a.c \
	src/algorithm/push_b.c \
	src/algorithm/search_closest.c \
	src/algorithm/sort_3.c \
	src/blist_helpers/blstadd_back.c \
	src/blist_helpers/create_node.c \
	src/blist_helpers/get_distance.c \
	src/blist_helpers/get_highest_node.c \
	src/blist_helpers/get_last_node.c \
	src/blist_helpers/get_node_from_index.c \
	src/cost_manager/cost_helpers.c \
	src/cost_manager/cost.c \
	src/operations/push.c \
	src/operations/reverse_rotate.c \
	src/operations/rotate.c \
	src/operations/swap.c \

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

LIBS = \
	lib/libft/include/libft.a

INCLUDES = \
	-Iinclude \
	-Ilib/libft/include

all: $(NAME)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: clean $(NAME)

clean:
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@echo "\033[31mObject files removed\033[0m"

fclean: clean
	@rm -f $(BUILD_DIR)/$(NAME)
	@rm -f $(BONUS_BUILD_DIR)/$(BONUS_NAME)
	@$(MAKE) -C lib/libft fclean
	@echo "\033[31m$(NAME) removed\033[0m"

re: fclean
	$(MAKE) all

libft:
	@echo "\033[33mCompiling libft...\033[0m"
	@$(MAKE) -C lib/libft


$(NAME): libft $(OBJ)
	@mkdir -p $(BUILD_DIR)
	@$(CC) $(OBJ) -o $(BUILD_DIR)/$(NAME) $(LIBS) $(LDFLAGS) $(INCLUDES)
	@echo "\033[32m\n¡$(NAME) compiled! \
	ᕦ(\033[36m⌐■\033[32m_\033[36m■\033[32m)ᕤ\n"

$(OBJ) : $(OBJ_DIR)/%.o : %.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "\033[34mCompiling: \033[0m$<"


#################### BONUS #####################

BONUS_BUILD_DIR = build_bonus
BONUS_OBJ_DIR = build_bonus/obj
BONUS_NAME = checker

BONUS_HEADERS = \
	bonus/include_bonus/checker.h \

BONUS_SRC = \
	bonus/src_bonus/arg_check_bonus.c \
	bonus/src_bonus/error_clean_bonus.c \
	bonus/src_bonus/initialization_bonus.c \
	bonus/src_bonus/main_bonus.c \
	bonus/src_bonus/sort_check_bonus.c \
	bonus/src_bonus/blist_helpers_bonus/blstadd_back_bonus.c \
	bonus/src_bonus/blist_helpers_bonus/create_node_bonus.c \
	bonus/src_bonus/blist_helpers_bonus/get_last_node_bonus.c \
	bonus/src_bonus/operations/operations_execution_bonus.c \
	bonus/src_bonus/operations/push_bonus.c \
	bonus/src_bonus/operations/reverse_rotate_bonus.c \
	bonus/src_bonus/operations/rotate_bonus.c \
	bonus/src_bonus/operations/swap_bonus.c \

BONUS_OBJ = $(addprefix $(BONUS_OBJ_DIR)/, $(BONUS_SRC:.c=.o))

BONUS_INCLUDES = \
	-Ibonus/include_bonus \
	-Ilib/libft/include

bonus: libft $(BONUS_OBJ)
	@mkdir -p $(BONUS_BUILD_DIR)
	@$(CC) $(BONUS_OBJ) -o $(BONUS_BUILD_DIR)/$(BONUS_NAME) $(LIBS) $(LDFLAGS) $(BONUS_INCLUDES)
	@echo "\033[32m\n¡$(BONUS_NAME) compiled! \
	ᕦ(\033[36m⌐■\033[32m_\033[36m■\033[32m)ᕤ\n"

bonus_debug: CFLAGS += $(DEBUG_FLAGS)
bonus_debug: bonus_clean bonus

bonus_clean:
	@rm -rf $(BONUS_OBJ_DIR)
	@echo "\033[31mBonus object files removed\033[0m"

bonus_fclean: bonus_clean
	@rm -f $(BONUS_BUILD_DIR)/$(BONUS_NAME)
	@$(MAKE) -C lib/libft fclean
	@echo "\033[31m$(BONUS_NAME) removed\033[0m"

bonus_re: bonus_fclean
	$(MAKE) bonus

$(BONUS_OBJ): $(BONUS_OBJ_DIR)/%.o : %.c $(BONUS_HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(BONUS_INCLUDES) -c $< -o $@
	@echo "\033[34mCompiling: \033[0m$<"


################################################
.PHONY: all debug clean fclean re bonus bonus_debug bonus_clean bonus_fclean bonus_re
