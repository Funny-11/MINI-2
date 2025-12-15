# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/30 20:06:02 by gifanell          #+#    #+#              #
#    Updated: 2025/12/15 18:27:29 by gifanell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = CC

CFLAGS = -Wall -Werror -Wextra -g -Ilibft
INCLUDES = -I. -I./libft

#/* ───── LIBRERIE ESTERNE ───── */
LIBFT = ./libft
LIBFT_LIB = -L$(LIBFT) 	-lft -lreadline

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m

#/* ───── FILE SORGENTI ───── */
#SRCS = $(shell find srcs -name "*.c")#

SRCS =		./main.c \
			./signals.c \
			./utils/utils.c \
			./utils/env_utils.c \
			./utils/free.c \
			./utils/errors.c \
			./utils/init_env.c \
			./redirection/redirections.c \
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

OBJS = $(SRCS:.c=.o)

all: $(NAME)

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