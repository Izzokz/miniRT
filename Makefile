# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 13:30:38 by lumugot           #+#    #+#              #
#    Updated: 2025/06/19 14:30:16 by lumugot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

OBJDIR			= 666_OBJ/
PARSEDIR		= 001_PARSING/
VECDIR			= 101_FT_VEC/
TOBJDIR			= 102_FT_OBJ/
PROCESSDIR		= 103_FT_PROCESS/
UTILDIR			= 200_FT_UTILS/
LIBFTDIR		= Libft/
GNLDIR			= get_next_line/
INCLUDEDIR		= Includes/


LIBFT			= $(LIBFTDIR)libft.a

SRCS			= main.c \
                  $(VECDIR)ft_vec0.c \
                  $(VECDIR)ft_vec1.c \
                  $(VECDIR)ft_vec2.c \
                  $(VECDIR)ft_ray.c \
                  $(TOBJDIR)ft_init_obj.c \
                  $(TOBJDIR)ft_obj_c.c \
                  $(TOBJDIR)ft_obj_f.c \
                  $(TOBJDIR)ft_obj_spl.c \
                #   $(PROCESSDIR)ft_process.c \
                #   $(PROCESSDIR)ft_color.c \

OBJ	= $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(SRCS)))
DEP	= $(patsubst %.c,$(OBJDIR)%.d,$(notdir $(SRCS)))

CC	= cc
CFLAGS	= -Wall -Werror -Wextra -g3
CFLAGS	+= -MP -MMD
INCLUDES = -I. -I$(INCLUDEDIR) -I$(LIBFTDIR) -I$(GNLDIR) -Imlx-linux
LDFLAGS	= -L$(LIBFTDIR) -Lmlx-linux
LDLIBS	= -lft -lmlx_Linux -lXext -lX11 -lm -lz

TOTAL_FILES = $(words $(OBJ))
PROGRESS = 0
TERM_WIDTH = $(shell tput cols)
BAR_WIDTH = $(shell echo $$(( ($(TERM_WIDTH) - 32) > 60 ? 50 : ($(TERM_WIDTH) - 21) - 10 )))
COLORS = "\033[4;37m\033[4;31m\033[4;32m\033[4;33m\033[4;34m\033[4;35m\033[4;36m\033[1;37m\033[1;31m\033[1;32m\033[1;33m\033[1;34m\033[1;35m\033[1;36m\033[1;90m\033[1;91m\033[1;92m\033[1;93m\033[1;94m\033[1;95m\033[1;96m\033[1;97m"
CHARACTERS = "!?@0&:.%=+"
RESET_COLOR = "\033[0m"

PRINT_PROGRESS:=
define PRINT_PROGRESS
    $(eval PROGRESS := $(shell echo $$(( $(PROGRESS) + 1 ))))
    @BARS=$$(($(PROGRESS) * $(BAR_WIDTH) / $(TOTAL_FILES))); \
    EMPTY=$$(( $(BAR_WIDTH) - $$BARS )); \
    PERCENT=$$(($(PROGRESS) * 100 / $(TOTAL_FILES))); \
    printf "\033[1;32m\033[1mminiRT: \033[37mCompiling: \033[1;32m[+ "; \
    for i in $$(seq 1 $$BARS); do \
        COLOR=$$(echo $(COLORS) | fold -w 7 | shuf -n 1); \
        CHAR=$$(echo $(CHARACTERS) | fold -w 1 | shuf -n 1); \
        echo -n "\033[0;40m"$$COLOR$$CHAR$(RESET_COLOR); \
    done; \
    for i in $$(seq 1 $$EMPTY); do \
        echo -n " "; \
    done; \
    printf "\033[1;32m +] \033[34m$$PERCENT%%\033[0m\r"
endef

MAKEFLAGS += --no-print-directory

all: $(NAME)

$(NAME): libs $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@printf "\n\033[32m\033[1mminiRT: \033[1;97mBuild Complete !\033[0m\n"

dep:
	@sudo apt-get install gcc make xorg libxext-dev libbsd-dev

libs:
	@if [ ! -d mlx-linux ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git mlx-linux && \
		chmod 0777 mlx-linux/configure && \
		cd mlx-linux && ./configure && cd .. && \
		clear && \
		printf "\033[32m\033[1mminiRT: \033[1;37mmlx_linux Set Up !\033[0m\n"; \
	fi

$(LIBFT):
	@$(MAKE) -C $(LIBFTDIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@printf "\033[32m\033[1mminiRT: \033[1;37m$(OBJDIR) Generated !\033[0m\n"

vpath %.c $(VECDIR) $(TOBJDIR) $(PROCESSDIR) $(UTILDIR) $(GNLDIR) .

$(OBJDIR)%.o: %.c | $(OBJDIR)
	@$(PRINT_PROGRESS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@rm -f $(OBJ) $(DEP)
	@printf "\033[32m\033[1mminiRT: \033[1;37mObject files Cleaned !\033[0m\n"

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR)
	@rm -f $(NAME)
	@rm -rf $(OBJDIR)
	@printf "\033[32m\033[1mminiRT: \033[1;37mFull Clean Complete !\033[0m\n"

re: fclean all

.PHONY: all clean fclean re libs dep

-include $(DEP)
