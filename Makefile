# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin@42.fr <marvin>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/30 20:06:02 by gifanell          #+#    #+#              #
#    Updated: 2025/12/28 15:32:55 by marvin@42.f      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -Ilibft -I.

#/* ───── LIBRERIE ESTERNE ───── */
LIBFT = ./libft
LIBFT_LIB = ./libft/libft.a
LIBFT_LIB_LINK = -L$(LIBFT) -lft

LIBS_LINK = $(LIBFT_LIB_LINK) -lreadline

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
RESET = \033[0m

#/* ───── FILE SORGENTI ───── */
#SRCS = $(shell find srcs -name "*.c")#

SRCS = ./builtins/builtins.c \
	./builtins/cd.c \
	./builtins/echo.c \
	./builtins/env.c \
	./builtins/exit.c \
	./builtins/export.c \
	./builtins/pwd.c \
	./builtins/unset.c \
	./executor/exec_utils.c \
	./executor/executor.c \
	./expander/expander.c \
	./lexer/lexer.c \
	./lexer/lexer_utils.c \
	./lexer/tokens.c \
	./main.c \
	./parser/parser.c \
	./parser/parser_utils.c \
	./redirection/redirections.c \
	./signals.c \
	./utils/env_utils.c \
	./utils/errors.c \
	./utils/free.c \
	./utils/init_env.c \
	./utils/utils.c


all: $(NAME)

$(NAME): $(LIBFT_LIB) $(SRCS)
	echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	$(CC) $(CFLAGS) $(SRCS) $(LIBS_LINK) -o $(NAME)
	echo "$(GREEN)✓ $(NAME) created!$(RESET)"

$(LIBFT_LIB):
	echo "$(YELLOW)Making libft...⏳$(RESET)"
	make -C $(LIBFT)
	echo "$(GREEN)✓ Libft ready$(RESET)"

clean:
	make clean -C $(LIBFT)

fclean: clean
	echo "$(RED)Pulizia totale...🧽🪣$(RESET)"
	rm -f $(NAME)
	make fclean -C $(LIBFT)

re: fclean all

message:
	echo	"████████████████████████████████████████████████████████"
	echo	"█||M ||||I ||||N ||||I ||||S ||||H ||||E ||||L ||||L ||█"
	echo	"█||__||||__||||__||||__||||__||||__||||__||||__||||__||█"
	echo 	"█|/__\||/__\||/__\||/__\||/__\||/__\||/__\||/__\||/__\|█"
	echo	"████████████████████████████████████████████████████████"
	echo	"╬╬╬╬╬╬╬╬ START TESTING OURS FABULOUS MINISHELL ╬╬╬╬╬╬╬╬╬"

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=$(PWD)/good.supp --quiet ./minishell

.PHONY: all clean fclean re
.SILENT:
