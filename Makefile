S = src/
O = obj/
I = ./
LIBFT_PATH = ./libft/
MLX_PATH = ./minilibx-linux/
LIBFT = $(LIBFT_PATH)libft.a
MLX = $(MLX_PATH)libmlx.a
LIB = -L$(LIBFT_PATH) -L$(MLX_PATH) -lft -lmlx -lXext -lX11 -lm
INC = -I$I -I$(LIBFT_PATH) -I$(MLX_PATH)

SRC = \
	$Sdeal_key.c \
	$Sdraw_map.c \
	$Sfdf.c \
	$Shandle_error.c \
	$Sload_map.c \
	$Ssettings.c \
	$Sutils.c
BSRC = \
	$Sfdf_bonus.c \
	$Sdeal_key_bonus.c \
	$Sdraw_map.c \
	$Shandle_error.c \
	$Sload_map.c \
	$Ssettings.c \
	$Sutils.c

OBJ = $(SRC:$S%.c=$O%.o)
BOBJ = $(BSRC:$S%.c=$O%.o)

NAME = fdf
NAME_B = fdf_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf
RMDIR = rmdir

all:	$(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) all

$(MLX):
	make -C $(MLX_PATH) all

$O:
	mkdir -p $@

$(OBJ): | $O

$(BOBJ): | $O

$O%.o: $S%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIB) $(INC)

bonus:	$(NAME_B)

$(NAME_B): $(LIBFT) $(MLX) $(BOBJ)
	$(CC) $(CFLAGS) $(BOBJ) -o $@ $(LIB) $(INC)

clean:
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean
	$(RM) $(OBJ) $(BOBJ)
	$(RMDIR) $O

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME) $(NAME_B)

re:	fclean all bonus

.PHONY:	all bonus clean fclean re
