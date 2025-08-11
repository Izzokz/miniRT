# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumugot <lumugot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/19 13:30:38 by lumugot           #+#    #+#              #
#    Updated: 2025/08/10 19:19:35 by lumugot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
NAME_BONUS = miniRT_bonus

BONUSDIR			= 1_BONUS/
OBJDIR_BONUS		= $(BONUSDIR)666_OBJ_BONUS/
PARSEDIR_BONUS		= $(BONUSDIR)001_PARSING/
VECDIR_BONUS		= $(BONUSDIR)101_FT_VEC/
TOBJDIR_BONUS		= $(BONUSDIR)102_FT_OBJ/
PROCESSDIR_BONUS	= $(BONUSDIR)103_FT_PROCESS/
UTILDIR_BONUS		= $(BONUSDIR)200_UTILS/
MLXDIR_BONUS		= $(BONUSDIR)201_FT_MLX/
EDITORDIR_BONUS		= $(BONUSDIR)202_EDITOR/

MANDATORYDIR		= 0_MANDATORY/
OBJDIR				= $(MANDATORYDIR)666_OBJ/
PARSEDIR			= $(MANDATORYDIR)001_PARSING/
VECDIR				= $(MANDATORYDIR)101_FT_VEC/
TOBJDIR				= $(MANDATORYDIR)102_FT_OBJ/
PROCESSDIR			= $(MANDATORYDIR)103_FT_PROCESS/
UTILDIR				= $(MANDATORYDIR)200_UTILS/
MLXDIR				= $(MANDATORYDIR)201_FT_MLX/
EDITORDIR			= $(MANDATORYDIR)202_EDITOR/

LIBFTDIR			= Libft/
GNLDIR				= get_next_line/
INCLUDEDIR			= $(MANDATORYDIR)Includes/
INCLUDEDIR_BONUS	= $(BONUSDIR)Includes/

LIBFT			= $(LIBFTDIR)libft.a

SRCS			= $(MANDATORYDIR)main.c \
				$(MANDATORYDIR)global.c \
				$(GNLDIR)get_next_line.c \
				$(GNLDIR)get_next_line_utils.c \
				$(PARSEDIR)free_utils.c \
				$(PARSEDIR)check_scene.c \
				$(PARSEDIR)parse_arg.c \
				$(PARSEDIR)parse_params.c \
				$(PARSEDIR)parse_ambient.c \
				$(PARSEDIR)parse_camera.c \
				$(PARSEDIR)parse_light.c \
				$(PARSEDIR)parse_sphere.c \
				$(PARSEDIR)parse_plane.c \
				$(PARSEDIR)parse_cylinder.c \
				$(UTILDIR)check_params.c \
				$(UTILDIR)split_utils.c \
				$(UTILDIR)ft_sequals.c \
				$(UTILDIR)ft_rand.c \
                $(VECDIR)ft_vec0.c \
                $(VECDIR)ft_vec1.c \
                $(VECDIR)ft_vec2.c \
                $(VECDIR)ft_ray.c \
                $(TOBJDIR)ft_obj_c.c \
                $(TOBJDIR)ft_obj_p.c \
                $(TOBJDIR)ft_obj_s.c \
				$(PROCESSDIR)ft_color_utils.c \
				$(PROCESSDIR)ft_color_obj_norm.c \
				$(PROCESSDIR)ft_color.c \
				$(PROCESSDIR)ft_color_ads.c \
				$(PROCESSDIR)ft_color_glass.c \
				$(PROCESSDIR)ft_unicorn.c \
				$(PROCESSDIR)ft_color_virus.c \
				$(PROCESSDIR)ft_color_chill.c \
				$(PROCESSDIR)ft_color_error.c \
				$(PROCESSDIR)ft_color_mini.c \
				$(PROCESSDIR)ft_obj_hit.c \
				$(PROCESSDIR)ft_process2.c \
				$(PROCESSDIR)ft_process.c \
				$(PROCESSDIR)ft_rotate2.c \
				$(PROCESSDIR)ft_rotate.c \
				$(PROCESSDIR)ft_move.c \
				$(PROCESSDIR)ft_rules.c \
                $(MLXDIR)ft_mlx_init.c \
                $(MLXDIR)ft_mlx_key_hook.c \
				$(MLXDIR)ft_mlx_key_hook2.c \
                $(MLXDIR)ft_mlx_loop.c \
                $(MLXDIR)ft_mlx_img.c \
				$(EDITORDIR)ft_editor.c \
				$(EDITORDIR)ft_rewrite.c \
				$(EDITORDIR)ft_rewrite2.c \
				$(EDITORDIR)ft_edit_ambient.c \
				$(EDITORDIR)ft_edit_light.c \
				$(EDITORDIR)ft_editor_utils.c \
				$(EDITORDIR)editor_helper.c \
				$(MLXDIR)ft_mlx_menu.c \
				$(MLXDIR)display_menu.c

SRCS_BONUS		= $(BONUSDIR)main_bonus.c \
				$(BONUSDIR)global_bonus.c \
				$(GNLDIR)get_next_line.c \
				$(GNLDIR)get_next_line_utils.c \
				$(PARSEDIR_BONUS)free_utils_bonus.c \
				$(PARSEDIR_BONUS)check_scene_bonus.c \
				$(PARSEDIR_BONUS)parse_arg_bonus.c \
				$(PARSEDIR_BONUS)parse_params_bonus.c \
				$(PARSEDIR_BONUS)parse_ambient_bonus.c \
				$(PARSEDIR_BONUS)parse_camera_bonus.c \
				$(PARSEDIR_BONUS)parse_light_bonus.c \
				$(PARSEDIR_BONUS)parse_sphere_bonus.c \
				$(PARSEDIR_BONUS)parse_plane_bonus.c \
				$(PARSEDIR_BONUS)parse_cylinder_bonus.c \
				$(PARSEDIR_BONUS)parse_cone_bonus.c \
				$(UTILDIR_BONUS)check_params_bonus.c \
				$(UTILDIR_BONUS)split_utils_bonus.c \
				$(UTILDIR_BONUS)ft_sequals_bonus.c \
				$(UTILDIR_BONUS)ft_rand_bonus.c \
                $(VECDIR_BONUS)ft_vec0_bonus.c \
                $(VECDIR_BONUS)ft_vec1_bonus.c \
                $(VECDIR_BONUS)ft_vec2_bonus.c \
                $(VECDIR_BONUS)ft_ray_bonus.c \
                $(TOBJDIR_BONUS)ft_obj_c_bonus.c \
                $(TOBJDIR_BONUS)ft_obj_p_bonus.c \
                $(TOBJDIR_BONUS)ft_obj_s_bonus.c \
				$(TOBJDIR_BONUS)ft_obj_cone_bonus.c \
				$(PROCESSDIR_BONUS)ft_color_utils_bonus.c \
				$(PROCESSDIR_BONUS)ft_color_obj_norm_bonus.c \
				$(PROCESSDIR_BONUS)ft_color_bonus.c \
				$(PROCESSDIR_BONUS)ft_color_ads_bonus.c \
				$(PROCESSDIR_BONUS)ft_color_glass_bonus.c \
				$(PROCESSDIR_BONUS)ft_unicorn_bonus.c \
				$(PROCESSDIR_BONUS)ft_color_virus_bonus.c \
				$(PROCESSDIR_BONUS)ft_color_chill_bonus.c \
				$(PROCESSDIR_BONUS)ft_color_error_bonus.c \
				$(PROCESSDIR_BONUS)ft_color_mini_bonus.c \
				$(PROCESSDIR_BONUS)ft_obj_hit_bonus.c \
				$(PROCESSDIR_BONUS)ft_process2_bonus.c \
				$(PROCESSDIR_BONUS)ft_process_bonus.c \
				$(PROCESSDIR_BONUS)ft_rotate2_bonus.c \
				$(PROCESSDIR_BONUS)ft_rotate_bonus.c \
				$(PROCESSDIR_BONUS)ft_move_bonus.c \
				$(PROCESSDIR_BONUS)ft_rules_bonus.c \
                $(MLXDIR_BONUS)ft_mlx_init_bonus.c \
                $(MLXDIR_BONUS)ft_mlx_key_hook_bonus.c \
				$(MLXDIR_BONUS)ft_mlx_key_hook2_bonus.c \
                $(MLXDIR_BONUS)ft_mlx_loop_bonus.c \
                $(MLXDIR_BONUS)ft_mlx_img_bonus.c \
				$(EDITORDIR_BONUS)ft_editor_bonus.c \
				$(EDITORDIR_BONUS)ft_rewrite_bonus.c \
				$(EDITORDIR_BONUS)ft_rewrite2_bonus.c \
				$(EDITORDIR_BONUS)ft_rewrite3_bonus.c \
				$(EDITORDIR_BONUS)ft_edit_ambient_bonus.c \
				$(EDITORDIR_BONUS)ft_edit_light_bonus.c \
				$(EDITORDIR_BONUS)ft_editor_utils_bonus.c \
				$(EDITORDIR_BONUS)editor_helper_bonus.c \
				$(MLXDIR_BONUS)ft_mlx_menu_bonus.c \
				$(MLXDIR_BONUS)display_menu_bonus.c

OBJ	= $(patsubst %.c,$(OBJDIR)%.o,$(notdir $(SRCS)))
DEP	= $(patsubst %.c,$(OBJDIR)%.d,$(notdir $(SRCS)))
OBJ_BONUS = $(patsubst %.c,$(OBJDIR_BONUS)%.o,$(notdir $(SRCS_BONUS)))
DEP_BONUS = $(patsubst %.c,$(OBJDIR_BONUS)%.d,$(notdir $(SRCS_BONUS)))

CC	= cc
CFLAGS	= -Wall -Wextra -Werror -g3
CFLAGS	+= -MP -MMD
INCLUDES = -I$(INCLUDEDIR) -I$(LIBFTDIR) -I$(GNLDIR) -Imlx-linux
INCLUDES_BONUS = -I$(INCLUDEDIR_BONUS) -I$(LIBFTDIR) -I$(GNLDIR) -Imlx-linux
LDFLAGS	= -L$(LIBFTDIR) -Lmlx-linux
LDLIBS	= -lft -lmlx_Linux -lXext -lX11 -lm -lz

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

all: TOTAL_FILES := $(words $(OBJ))
all: $(NAME)

bonus: TOTAL_FILES := $(words $(OBJ_BONUS))
bonus: $(NAME_BONUS)

$(NAME): libs $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	@printf "\n\033[32m\033[1mminiRT: \033[1;97mBuild Complete !\033[0m\n"

$(NAME_BONUS): libs $(LIBFT) $(OBJ_BONUS)
	@$(CC) $(OBJ_BONUS) $(LDFLAGS) $(LDLIBS) -o $(NAME_BONUS)
	@printf "\n\033[32m\033[1mminiRT: \033[1;97mBonus Build Complete !\033[0m\n"

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

$(OBJDIR_BONUS):
	@mkdir -p $(OBJDIR_BONUS)
	@printf "\033[32m\033[1mminiRT: \033[1;37m$(OBJDIR_BONUS) Generated !\033[0m\n"

vpath %.c $(VECDIR) $(VECDIR_BONUS) $(TOBJDIR) $(TOBJDIR_BONUS) $(PROCESSDIR) $(PROCESSDIR_BONUS) $(UTILDIR) $(UTILDIR_BONUS) $(GNLDIR) $(PARSEDIR) $(PARSEDIR_BONUS) $(MLXDIR) $(MLXDIR_BONUS) $(EDITORDIR) $(EDITORDIR_BONUS) $(MANDATORYDIR) $(BONUSDIR)

$(OBJDIR)%.o: %.c | $(OBJDIR)
	@$(PRINT_PROGRESS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR_BONUS)%.o: %.c | $(OBJDIR_BONUS)
	@$(PRINT_PROGRESS)
	@$(CC) $(CFLAGS) $(INCLUDES_BONUS) -c $< -o $@

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@rm -rf $(OBJDIR) $(OBJDIR_BONUS)
	@printf "\033[32m\033[1mminiRT: \033[1;37mObject files Cleaned !\033[0m\n"

fclean:
	@$(MAKE) fclean -C $(LIBFTDIR)
	@rm -f $(NAME) $(NAME_BONUS)
	@rm -rf $(OBJDIR) $(OBJDIR_BONUS)
	@printf "\033[32m\033[1mminiRT: \033[1;37mFull Clean Complete !\033[0m\n"

re: fclean all

.PHONY: all clean fclean re libs dep bonus

-include $(DEP) $(DEP_BONUS)
