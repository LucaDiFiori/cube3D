NAME = cube3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror 
LDFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
INCLUDES = -I/usr/include -Imlx_linux -O3

.PHONY: all configure_mlx

all: $(NAME) ascii_art



ascii_art:
	@echo "\033[1;34m ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ \033[0m"
	@echo "\033[1;35m██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗\033[0m"
	@echo "\033[1;36m██║     ██║   ██║██████╔╝ █████╔╝██║  ██║\033[0m"
	@echo "\033[1;34m██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║\033[0m"
	@echo "\033[1;35m╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝\033[0m"
	@echo "\033[1;36m ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ \033[0m"

SRCS = cube3d.c \
	   src/cub_file_parsing/extract_rgb.c \
	   src/cub_file_parsing/extract_info_utils.c \
	   src/cub_file_parsing/extract_info.c \
	   src/cub_file_parsing/extract_map.c \
	   src/cub_file_parsing/check_map.c \
	   src/gnl/get_next_line.c \
	   src/gnl/get_next_line_utils.c \
	   src/minilib/minilib_1.c \
	   src/minilib/minilib_2.c \
	   src/minilib/minilib_3.c \
	   src/minilib/ft_atoi.c \
	   src/utils/quit_and_free.c \
	   src/printf/ft_printf.c \
	   src/init/init_struct.c \
	   src/init/init_engine.c \

OBJS = $(SRCS:%.c=obj/%.o)

$(NAME): $(OBJS)
	@(cd mlx_linux && ./configure)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME) 

obj/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf obj
	@(cd mlx_linux && $(MAKE) clean)

fclean: clean
	@(cd mlx_linux && $(MAKE) clean)
	@rm -f $(NAME)

re: fclean all
