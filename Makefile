NAME = miniRT

PRINTF = 010_FT_PRINTF/libftprintf.a
OBJDIR = 666_OBJ/

VECSRC = ft_vec0.c ft_vec1.c ft_vec2.c ft_ray.c main.c
VECDIR = 101_FT_VEC/

OBJ = $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(VECSRC)))
DEP = $(patsubst %.c,$(OBJDIR)%.d,$(notdir $(VECSRC)))

CCA = cc -Wall -Werror -Wextra -g3 -MP -MMD

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

$(NAME): libs $(PRINTF) $(OBJ)
	@$(CCA) $(OBJ) -lmlx_Linux -Lmlx-linux -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(PRINTF)
	@printf "\n\033[32m\033[1mminiRT: \033[1;97mBuild Complete !\033[0m\n"

dep:
	@sudo apt-get install gcc
	@sudo apt-get install make
	@sudo apt-get install xorg
	@sudo apt-get install libxext-dev
	@sudo apt-get install libbsd-dev

libs:
	@if [ ! -d mlx-linux ]; then \
		git clone https://github.com/42Paris/minilibx-linux.git mlx-linux && \
		chmod 0777 mlx-linux/configure && \
		cd mlx-linux && ./configure && cd .. && \
		printf "\033[32m\033[1mminiRT: \033[1;37mmlx_linux Set Up !\033[0m\n"; \
	fi

	@if [ ! -d 010_FT_PRINTF ]; then \
		git clone https://github.com/Izzokz/42-ft_printf.git 010_FT_PRINTF/ && \
		printf "\033[32m\033[1mminiRT: \033[1;37mft_printf Cloned !\033[0m\n"; \
	fi

$(PRINTF):
	@$(MAKE) -C 010_FT_PRINTF/

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@printf "\033[32m\033[1mminiRT: \033[1;37m666_OBJ/ Generated !\033[0m\n"

$(OBJDIR)%.o: $(VECDIR)%.c | $(OBJDIR)
	@cc -Wall -Werror -Wextra -MP -MMD -g3 -o $@ -c $< -I.

clean:
	@$(MAKE) clean -C 010_FT_PRINTF/
	@rm -f $(OBJ) $(DEP)
	@printf "\033[32m\033[1mminiRT: \033[1;37m666_OBJ/ Cleaned !\033[0m\n"

fclean:
	@$(MAKE) fclean -C 010_FT_PRINTF/
	@rm -f $(NAME) $(OBJ) $(DEP)
	@printf "\033[32m\033[1mminiRT: \033[1;37mCleaned !\033[0m\n"

re: fclean all

.PHONY: all clean fclean re libs

-include $(DEP)
