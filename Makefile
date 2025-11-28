
NAME    = cub3d
CC      = cc
CFLAGS  = -Wall -Wextra -Werror
RM      = rm -f

SRC_DIR = src
INC_DIR = include
SRC     = $(shell find $(SRC_DIR) -type f -name "*.c")
OBJ     = $(SRC:.c=.o)
INCLUDES = -I$(INC_DIR)

# libft
LIBFT_DIR = libft
LIBFT_A   = $(LIBFT_DIR)/libft.a

# MinilibX
MLX_REPO  = https://github.com/42Paris/minilibx-linux.git
MLX_DIR   = target/minilibx
MLX_A     = $(MLX_DIR)/libmlx.a

LDFLAGS   = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

all: $(NAME)

$(LIBFT_A):
	@git clone https://github.com/42Paris/libft.git $(LIBFT_DIR) || true
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	@mkdir -p $(MLX_DIR)
	@if [ ! -d "$(MLX_DIR)/.git" ]; then \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR) all

%.o: %.c | $(LIBFT_A) $(MLX_A)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT_A) $(MLX_A)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean || true

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean || true

re: fclean all

.PHONY: all clean fclean re
