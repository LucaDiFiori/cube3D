NAME = cube3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all

all:
	@echo "            _____                   _____                   _____                   _____"        
	@echo "           /\\    \\                 /\\    \\                 /\\    \\                 /\\    \\"        
	@echo "          /::\\    \\               /::\\____\\               /::\\    \\               /::\\    \\"        
	@echo "         /::::\\    \\             /:::/    /              /::::\\    \\             /::::\\    \\"        
	@echo "        /::::::\\    \\           /:::/    /              /::::::\\    \\           /::::::\\    \\"        
	@echo "       /:::/\\:::\\    \\         /:::/    /              /:::/\\:::\\    \\         /:::/\\:::\\    \\     "        
	@echo "      /:::/  \\:::\\    \\       /:::/    /              /:::/__\\:::\\    \\       /:::/__\\:::\\    \\    "        
	@echo "     /:::/    \\:::\\    \\     /:::/    /              /::::\\   \\:::\\    \\     /::::\\   \\:::\\    \\   "        
	@echo "    /:::/    / \\:::\\    \\   /:::/    /      _____   /::::::\\   \\:::\\    \\   /::::::\\   \\:::\\    \\  "        
	@echo "   /:::/    /   \\:::\\    \\ /:::/____/      /\\    \\ /:::/\\:::\\   \\:::\\ ___\\ /:::/\\:::\\   \\:::\\    \\ "        
	@echo "  /:::/____/     \\:::\\____|:::|    /      /::\\____/:::/__\\:::\\   \\:::|    /:::/__\\:::\\   \\:::\\____\\"        
	@echo "  \\:::\\    \\      \\::/    |:::|____\\     /:::/    \\:::\\   \\:::\\  /:::|____\\:::\\   \\:::\\   \\::/    /"        
	@echo "   \\:::\\    \\      \\/____/ \\:::\\    \\   /:::/    / \\:::\\   \\:::\\/:::/    / \\:::\\   \\:::\\   \\/____/ "        
	@echo "    \\:::\\    \\              \\:::\\    \\ /:::/    /   \\:::\\   \\::::::/    /   \\:::\\   \\:::\\    \\     "        
	@echo "     \\:::\\    \\              \\:::\\    /:::/    /     \\:::\\   \\::::/    /     \\:::\\   \\:::\\____\\    "        
	@echo "      \\:::\\    \\              \\:::\\__/:::/    /       \\:::\\  /:::/    /       \\:::\\   \\::/    /    "        
	@echo "       \\:::\\    \\              \\::::::::/    /         \\:::\\/:::/    /         \\:::\\   \\/____/     "        
	@echo "        \\:::\\    \\              \\::::::/    /           \\::::::/    /           \\:::\\    \\         "        
	@echo "         \\:::\\____\\              \\::::/    /             \\::::/    /             \\:::\\____\\        "        
	@echo "          \\::/    /               \\::/____/               \\::/____/               \\::/    /        "        
	@echo "           \\/____/                 ~~                      ~~                      \\/____/         "        
	@echo "            _____                   _____                   _____                   _____          "        
	@echo "           /\\    \\                 /\\    \\                 /\\    \\                 /\\    \\         "        
	@echo "          /::\\    \\               /::\\    \\               /::\\    \\               /::\\    \\        "        
	@echo "          \\:::\\    \\              \\:::\\    \\              \\:::\\    \\             /::::\\    \\       "        
	@echo "           \\:::\\    \\              \\:::\\    \\              \\:::\\    \\           /::::::\\    \\      "        
	@echo "            \\:::\\    \\              \\:::\\    \\              \\:::\\    \\         /:::/\\:::\\    \\     "        
	@echo "             \\:::\\    \\              \\:::\\    \\              \\:::\\    \\       /:::/  \\:::\\    \\    "        
	@echo "             /::::\\    \\             /::::\\    \\             /::::\\    \\     /:::/    \\:::\\    \\   "        
	@echo "    ____    /::::::\\    \\   ____    /::::::\\    \\   ____    /::::::\\    \\   /:::/    / \\:::\\    \\  "        
	@echo "   /\\   \\  /:::/\\:::\\    \\ /\\   \\  /:::/\\:::\\    \\ /\\   \\  /:::/\\:::\\    \\ /:::/    /   \\:::\\ ___\\ "        
	@echo "  /::\\   \\/:::/  \\:::\\____/::\\   \\/:::/  \\:::\\____/::\\   \\/:::/  \\:::\\____/:::/____/     \\:::|    |"        
	@echo "  \\:::\\  /:::/    \\::/    \\:::\\  /:::/    \\::/    \\:::\\  /:::/    \\::/    \\:::\\    \\     /:::|____|"        
	@echo "   \\:::\\/:::/    / \\/____/ \\:::\\/:::/    / \\/____/ \\:::\\/:::/    / \\/____/ \\:::\\    \\   /:::/    / "        
	@echo "    \\::::::/    /           \\::::::/    /           \\::::::/    /           \\:::\\    \\ /:::/    /  "        
	@echo "     \\::::/____/             \\::::/____/             \\::::/____/             \\:::\\    /:::/    /   "        
	@echo "      \\:::\\    \\              \\:::\\    \\              \\:::\\    \\              \\:::\\  /:::/    /    "        
	@echo "       \\:::\\    \\              \\:::\\    \\              \\:::\\    \\              \\:::\\/:::/    /     "        
	@echo "        \\:::\\    \\              \\:::\\    \\              \\:::\\    \\              \\::::::/    /      "        
	@echo "         \\:::\\____\\              \\:::\\____\\              \\:::\\____\\              \\::::/    /       "        
	@echo "          \\::/    /               \\::/    /               \\::/    /               \\::/____/        "        
	@echo "           \\/____/                 \\/____/                 \\/____/                 ~~              "

SRCS = cube3d.c \
	   src/map_checks/checks_utils.c \
	   src/map_checks/map_validation.c \
	   src/gnl/get_next_line.c \
	   src/gnl/get_next_line_utils.c \
	   src/minilib/minilib_1.c \
	   src/minilib/minilib_2.c \
	   src/minilib/ft_atoi.c \
	   src/utils/quit_and_free.c \
	   src/printf/ft_printf.c \
	   src/init/init.c \

OBJS = $(SRCS:%.c=obj/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

obj/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf obj

fclean: clean
	@rm -f $(NAME)

re: fclean all
