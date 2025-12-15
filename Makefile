# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/30 20:06:02 by gifanell          #+#    #+#              #
#    Updated: 2025/12/15 06:59:54 by gifanell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = CC

CFLAGS = -Wall -Werror -Wextra -g -Ilibft
INCLUDES = -I./includes -I./libft

#/* ───── LIBRERIE ESTERNE ───── */
LIBFT = ./libft
LIBFT_LIB = -L$(LIBFT) 	-lft -lreadline

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m

#/* ───── FILE SORGENTI ───── */
SRCS =		./main.c \
			./signals.c \
			./utils/utils.c \
			./utils/env_utils.c \
			./utils/free.c \
			./utils/errors.c \
			./utils/init_env.c \
			./redirections/redirections.c \
			./parser/parser.c \
			./parser/parser_utils.c \
			./lexer/lexer.c \
			./lexer/token_utils.c \
			./lexer/tokens.c \
			./executor/executor.c \
			./executor/execute_utils.c \
			./builtins/builtins.c \
			./builtins/cd.c \
			./builtins/echo.c \
			./builtins/env.c \
			./builtins/exit.c \
			./builtins/export.c \
			./builtins/pwd.c \
			./builtins/unset.c \
			./executor/exec_utils.c \
			./executor/executor.c \

OBJS = $(SRCS:.c=.o)

$(NAME): libft/libft.a $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) created!$(RESET)"

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

libft/libft.a:
	@echo "$(YELLOW)Making libft...⏳$(RESET)"
	@make -C $(LIBFT)
	@echo "$(GREEN)✓ Libft ready$(RESET)"

all: $(NAME)

clean:
		@echo "$(RED)Pulizia file oggetto...🧽🪣$(RESET)"
		rm -f $(OBJS)
		@make clean -C $(LIBFT)

fclean: clean
		@echo "$(RED)Pulizia totale...🧽🪣$(RESET)"
		rm -f $(NAME)
		@make fclean -C $(LIBFT)

re: fclean all

message:
		@echo	"████████████████████████████████████████████████████████"
		@echo	"█||M ||||I ||||N ||||I ||||S ||||H ||||E ||||L ||||L ||█"
		@echo	"█||__||||__||||__||||__||||__||||__||||__||||__||||__||█"
		@echo 	"█|/__\||/__\||/__\||/__\||/__\||/__\||/__\||/__\||/__\|█"
		@echo	"████████████████████████████████████████████████████████"
		@echo	"╬╬╬╬╬╬╬╬ START TESTING OURS FABULOUS MINISHELL ╬╬╬╬╬╬╬╬╬"

.PHONY: all clean fclean re